#ifndef _CABLE_NODE_HPP_
#define _CABLE_NODE_HPP_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

class CableNode {
public:
	class FileError : public Exc {
	public:
	    FileError(const String& s) : Exc(s) {}
	};
	
	static void GetStreamThrow(Stream& s, void* data, int size) {
		if (s.Get(data, size) != size) throw FileError("Read file EOF");
	}

	// File format version (see CableFormatFile.md)
	enum {
		FORMAT_V2 = 2,
		FORMAT_CURRENT = FORMAT_V2
	};
	
	static WString ReadName(Stream& in) {
		uint16_t len;
		GetStreamThrow(in, &len, sizeof(len));
		StringBuffer sb(len);
		if (len) GetStreamThrow(in, ~sb, len);
		return ToUtf32(String(sb));
	}
	
	static void WriteName(Stream& out, const WString& name) {
		String utf8 = ToUtf8(name);
		uint16_t len = (uint16_t)min(utf8.GetLength(), 0xffff);
		out.Put(&len, sizeof(len));
		out.Put(utf8, len);
	}
	
	virtual String GetTip() {return "";}
	static Color DarkColor(const Color &c, double darked = 0.6) {
		return Color(
			(int)round(c.GetR() * darked),
			(int)round(c.GetG() * darked),
			(int)round(c.GetB() * darked));
	}
};

#endif