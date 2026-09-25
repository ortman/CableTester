#ifndef _TESTER_WINDOW_HPP_
#define _TESTER_WINDOW_HPP_

#include <CtrlLib/CtrlLib.h>
#include "PropertiesCtrl.hpp"  // the layouts of SubCtrls.lay
#include "TesterDevice.hpp"

using namespace Upp;

// The cables in the tester: upload, select, delete, test
class TesterWindow : public WithTesterLayout<TopWindow> {
private:
	TesterDevice device;
	CtRspInfo info;
	Vector<String> names;       // the cables in the slots 0..N-1

	// The name as the tester keeps it in CtRspSlot: UTF-8, cut on a character
	static String SlotName(const String& name) {
		int len = min(name.GetCount(), (int)sizeof(((CtRspSlot*)0)->name) - 1);
		while (len > 0 && len < name.GetCount() && (name[len] & 0xC0) == 0x80) --len;
		return name.Left(len);
	}

	int GetSlot() const {
		return slots.IsCursor() ? slots.GetCursor() : -1;
	}

	void UpdateButtons() {
		bool open = device.IsOpen();
		bUpload.Enable(open && (bool)WhenBuild);
		bSelect.Enable(open && GetSlot() >= 0);
		bDelete.Enable(open && GetSlot() >= 0);
		bTest.Enable(open && info.currentSlot < names.GetCount());
	}

	void Error(const String& text) {
		Exclamation(DeQtf(text));
	}

public:
	// Gives the current cable of the editor: its name, package and picture.
	// Returns false when there is nothing to upload
	Function<bool(String& name, String& package, String& jpeg)> WhenBuild;

	// Slot pin labels ("Connector:pin", index 0 = slot pin 1) of the cable with
	// this name, empty when the cable is unknown
	Function<Vector<String>(const String& name)> WhenLabels;

	TesterWindow() {
		CtrlLayout(*this, t_("Tester"));
		Sizeable().Zoomable();

		slots.AddColumn(t_("Slot"), 6);
		slots.AddColumn(t_("Cable"), 30);
		slots.AddColumn(t_("Wires"), 6);
		slots.AddColumn(t_("Nets"), 6);
		slots.WhenSel = [=] { UpdateButtons(); };

		errors.AddColumn(t_("Error"), 10);
		errors.AddColumn(t_("Slot pins"), 10);
		errors.AddColumn(t_("Connectors"), 40);

		bRefresh << [=] {
			device.Close();
			Refresh();
		};
		bUpload << [=] { Upload(); };
		bSelect << [=] {
			int slot = GetSlot();
			if (slot < 0) return;
			if (!device.Select((uint8_t)slot)) Error(device.GetError());
			Refresh();
		};
		bDelete << [=] {
			int slot = GetSlot();
			if (slot < 0) return;
			if (!PromptYesNo(Format(t_("Delete the cable [* \1%s\1] from the tester?&"
			                           "The next cables move one slot up."), names[slot]))) return;
			if (!device.Erase((uint8_t)slot)) Error(device.GetError());
			Refresh();
		};
		bTest << [=] { Test(); };
		bClose << [=] { Break(IDOK); };
		WhenClose = [=] { Break(IDOK); };
	}

	// Connects to the tester and reads its cables. Returns false on error
	bool Refresh() {
		int cursor = GetSlot();
		slots.Clear();
		names.Clear();
		memset(&info, 0, sizeof(info));
		info.currentSlot = 0xFF;
		bool ok = (device.IsOpen() || device.Open()) && device.GetInfo(info);
		if (!ok && device.IsOpen()) {
			/* the tester may have been reconnected: open it again */
			device.Close();
			ok = device.Open() && device.GetInfo(info);
		}
		if (ok) {
			for (int i = 0; i < info.slotCount; ++i) {
				CtRspSlot slot;
				if (!device.GetSlot((uint8_t)i, slot)) {
					ok = false;
					break;
				}
				if (!slot.used) break;              // the cables have no gaps
				String name = String(slot.name, strnlen(slot.name, sizeof(slot.name)));
				names.Add(name);
				slots.Add((i == info.currentSlot ? "► " : "  ") + IntStr(i), name,
				          (int)slot.wireCount, (int)slot.netCount);
			}
		}
		if (ok) {
			lStatus = Format(t_("Connected: %d cable(s), %d free slot(s)"),
			                 names.GetCount(), info.slotCount - names.GetCount());
			if (cursor >= 0 && cursor < slots.GetCount()) slots.SetCursor(cursor);
		} else {
			lStatus = device.GetError();
			device.Close();
		}
		UpdateButtons();
		return ok;
	}

	void Upload() {
		String name, package, jpeg;
		if (!WhenBuild || !WhenBuild(name, package, jpeg)) return;
		if (!Refresh()) {
			Error(device.GetError());
			return;
		}
		int slot = FindIndex(names, SlotName(name));
		if (slot >= 0) {
			if (!PromptYesNo(Format(t_("Replace the cable [* \1%s\1] in the slot %d?"), name, slot))) return;
		} else {
			slot = names.GetCount();
			if (slot >= info.slotCount) {
				Exclamation(t_("The tester has no free slots."));
				return;
			}
		}

		Progress progress(this, t_("Uploading the cable"), 1);
		device.WhenProgress = [&](int done, int total) {
			progress.SetTotal(total);
			progress.SetPos(done);
			return !progress.Canceled();
		};
		progress.SetText(t_("Package"));
		bool ok = device.UploadPackage((uint8_t)slot, package);
		if (ok) {
			progress.SetText(Format(t_("Picture to the display, %d KB"), jpeg.GetCount() / 1024));
			ok = device.UploadImage((uint8_t)slot, jpeg);
		}
		device.WhenProgress.Clear();
		progress.Close();

		String error = device.GetError();
		Refresh();
		if (slot < slots.GetCount()) slots.SetCursor(slot);
		if (!ok) Error(Format(t_("Upload failed: %s"), error));
	}

	void Test() {
		errors.Clear();
		CtRspTest test;
		if (!device.RunTest(test)) {
			Error(device.GetError());
			Refresh();
			return;
		}
		String name = info.currentSlot < names.GetCount() ? names[info.currentSlot] : String();
		Vector<String> labels;
		if (WhenLabels) labels = WhenLabels(name);
		auto Label = [&](int pin) {
			return (pin >= 1 && pin <= labels.GetCount() && labels[pin - 1].GetCount())
			       ? labels[pin - 1] : String("?");
		};
		for (int i = 0; i < test.errorCount; ++i) {
			CtRspError e;
			if (!device.GetError((uint8_t)i, e)) {
				Error(device.GetError());
				break;
			}
			errors.Add(e.type ? t_("Short") : t_("Open"),
			           Format("D%d - D%d", (int)e.pinA, (int)e.pinB),
			           Label(e.pinA) + " - " + Label(e.pinB));
		}
		String result = test.errorCount ? Format(t_("%s: %d error(s)"), name, (int)test.errorCount)
		                                : Format(t_("%s: OK"), name);
		if (test.overflow) result << t_(", not all are shown");
		lResult = result;
	}

	void Run() {
		errors.Clear();
		lResult = t_("Test result");
		Refresh();
		Execute();
		device.Close();
	}
};

#endif
