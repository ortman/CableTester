#ifndef _TESTER_DEVICE_HPP_
#define _TESTER_DEVICE_HPP_

#include <Core/Core.h>
#include "winusbcross/winusbcross.h"
#include "../Common/ct_protocol.h"

using namespace Upp;

// The tester on USB (WinUSB), see Common/ct_protocol.h
class TesterDevice {
private:
	wuc_t* wuc = NULL;
	wuc_device_t* dev = NULL;
	uint8_t seq = 0;
	String error;

	static constexpr uint32_t CMD_TIMEOUT_MS = 2000;
	static constexpr uint32_t END_TIMEOUT_MS = 20000;  // the picture goes to the display at 250 kbit/s

	bool Fail(const String& text) {
		error = text;
		return false;
	}

public:
	// Called while a file goes to the tester, returns false to cancel
	Function<bool(int done, int total)> WhenProgress;

	~TesterDevice() {
		Close();
	}

	const String& GetError() const {
		return error;
	}

	static String StatusText(uint8_t status) {
		switch (status) {
			case CT_ST_OK:      return t_("OK");
			case CT_ST_BAD_CMD: return t_("unknown command");
			case CT_ST_BAD_ARG: return t_("wrong argument");
			case CT_ST_BUSY:    return t_("the tester is busy");
			case CT_ST_BAD_CRC: return t_("the package is damaged");
			case CT_ST_FLASH:   return t_("flash write error");
			case CT_ST_DISPLAY: return t_("the display does not answer");
			case CT_ST_NO_DATA: return t_("not all the data received");
			case CT_ST_TOO_BIG: return t_("the file is too big");
			case CT_ST_NO_SLOT: return t_("no such slot");
		}
		return Format(t_("status %d"), status);
	}

	bool IsOpen() const {
		return dev != NULL;
	}

	// Connects to the first tester found
	bool Open() {
		Close();
		static char16_t guid[39];
		const char* src = CT_USB_GUID;
		for (int i = 0; i < 39; ++i) guid[i] = (char16_t)src[i];
		int32_t count = 0;
		wuc = wuc_init(guid, &count);
		if (wuc == NULL || wuc->err) return Fail(t_("WinUSB is not available"));
		if (count <= 0) return Fail(t_("The tester is not connected"));
		dev = wuc_connect_device(wuc, 0);
		if (dev == NULL) return Fail(Format(t_("Can not open the tester (error %d)"), (int)wuc->err));
		return true;
	}

	void Close() {
		if (dev) {
			wuc_disconnect_device(dev);
			dev = NULL;
		}
		if (wuc) {
			wuc_deInit(wuc);
			wuc = NULL;
		}
	}

	// Sends a command and waits for its answer. Returns false on a transfer error,
	// the status of the device is in rsp.status
	bool Command(uint8_t cmd, const void* arg, int len, CtRsp& rsp, uint32_t timeout = CMD_TIMEOUT_MS) {
		if (!dev) return Fail(t_("The tester is not connected"));
		CtCmd c;
		memset(&c, 0, sizeof(c));
		c.cmd = cmd;
		c.seq = ++seq;
		c.len = (uint8_t)min(len, CT_CMD_ARG_SIZE);
		if (c.len) memcpy(c.arg, arg, c.len);
		if (wuc_interrupt_write(dev, CT_EP_CMD, (uint8_t*)&c, sizeof(c), timeout) != (int32_t)sizeof(c)) {
			return Fail(t_("USB write error"));
		}
		for (int tries = 0; tries < 8; ++tries) {
			memset(&rsp, 0, sizeof(rsp));
			int32_t n = wuc_interrupt_read(dev, CT_EP_RSP, (uint8_t*)&rsp, sizeof(rsp), timeout);
			if (n < 4) return Fail(t_("The tester does not answer"));
			if (rsp.seq == c.seq && rsp.cmd == (cmd | 0x80)) return true;  // older answers are skipped
		}
		return Fail(t_("Wrong answer of the tester"));
	}

	bool Command(uint8_t cmd, const void* arg, int len, uint32_t timeout = CMD_TIMEOUT_MS) {
		CtRsp rsp;
		if (!Command(cmd, arg, len, rsp, timeout)) return false;
		if (rsp.status != CT_ST_OK) return Fail(StatusText(rsp.status));
		return true;
	}

	bool GetInfo(CtRspInfo& info) {
		CtRsp rsp;
		if (!Command(CT_CMD_INFO, NULL, 0, rsp)) return false;
		if (rsp.status != CT_ST_OK) return Fail(StatusText(rsp.status));
		memcpy(&info, rsp.data, sizeof(info));
		return true;
	}

	bool GetSlot(uint8_t slot, CtRspSlot& info) {
		CtRsp rsp;
		if (!Command(CT_CMD_SLOT_INFO, &slot, 1, rsp)) return false;
		if (rsp.status != CT_ST_OK) return Fail(StatusText(rsp.status));
		memcpy(&info, rsp.data, sizeof(info));
		return true;
	}

private:
	bool SendData(const String& data) {
		int done = 0;
		while (done < data.GetCount()) {
			int part = min(data.GetCount() - done, 4096);
			int32_t n = wuc_bulk_write(dev, CT_EP_DATA, (uint8_t*)~data + done, part, END_TIMEOUT_MS);
			if (n <= 0) return Fail(t_("USB write error"));
			done += n;
			if (WhenProgress && !WhenProgress(done, data.GetCount())) return Fail(t_("Canceled"));
		}
		return true;
	}

	bool FinishTransfer(uint8_t cmd, int size) {
		CtRsp rsp;
		if (!Command(cmd, NULL, 0, rsp, END_TIMEOUT_MS)) return false;
		if (rsp.status != CT_ST_OK) {
			CtRspSize got;
			memcpy(&got, rsp.data, sizeof(got));
			return Fail(Format(t_("%s (received %d of %d bytes)"), StatusText(rsp.status), (int)got.size, size));
		}
		return true;
	}

public:
	// Writes the test package (.ctp) to the slot of the tester
	bool UploadPackage(uint8_t slot, const String& package) {
		CtCmdPkgBegin arg;
		arg.slot = slot;
		arg.size = (uint16_t)package.GetCount();
		if (!Command(CT_CMD_PKG_BEGIN, &arg, sizeof(arg))) return false;
		if (!SendData(package)) {
			Command(CT_CMD_ABORT, NULL, 0);
			return false;
		}
		return FinishTransfer(CT_CMD_PKG_END, package.GetCount());
	}

	// Writes the picture (.jpg) to the microSD of the display as sd0/c<slot>.jpg
	bool UploadImage(uint8_t slot, const String& jpeg) {
		CtCmdImgBegin arg;
		arg.slot = slot;
		arg.size = (uint32_t)jpeg.GetCount();
		if (!Command(CT_CMD_IMG_BEGIN, &arg, sizeof(arg))) return false;
		if (!SendData(jpeg)) {
			Command(CT_CMD_ABORT, NULL, 0);
			return false;
		}
		return FinishTransfer(CT_CMD_IMG_END, jpeg.GetCount());
	}

	bool Erase(uint8_t slot) {
		return Command(CT_CMD_PKG_ERASE, &slot, 1);
	}

	bool Select(uint8_t slot) {
		return Command(CT_CMD_SELECT, &slot, 1);
	}

	// Runs the test on the tester (debugging, the tester works without the PC)
	bool RunTest(CtRspTest& test) {
		CtRsp rsp;
		if (!Command(CT_CMD_RUN_TEST, NULL, 0, rsp)) return false;
		if (rsp.status != CT_ST_OK) return Fail(StatusText(rsp.status));
		memcpy(&test, rsp.data, sizeof(test));
		return true;
	}

	bool GetError(uint8_t index, CtRspError& e) {
		CtRsp rsp;
		if (!Command(CT_CMD_GET_ERROR, &index, 1, rsp)) return false;
		if (rsp.status != CT_ST_OK) return Fail(StatusText(rsp.status));
		memcpy(&e, rsp.data, sizeof(e));
		return true;
	}

	// The measured connections of the pin (bit n-1: the pin n)
	bool GetRow(uint8_t pin, uint64_t& mask) {
		CtRsp rsp;
		if (!Command(CT_CMD_GET_ROW, &pin, 1, rsp)) return false;
		if (rsp.status != CT_ST_OK) return Fail(StatusText(rsp.status));
		CtRspRow row;
		memcpy(&row, rsp.data, sizeof(row));
		mask = 0;
		for (int i = 0; i < 8; ++i) mask |= (uint64_t)row.mask[i] << (8 * i);
		return true;
	}

	// Sends an instruction to the display through the tester (debugging)
	bool DisplayCommand(const String& text) {
		return Command(CT_CMD_NX_CMD, ~text, text.GetCount());
	}
};

#endif
