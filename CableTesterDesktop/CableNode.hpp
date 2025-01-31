#ifndef _CABLE_NODE_HPP_
#define _CABLE_NODE_HPP_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

class CableNode {
public:
	virtual String GetTip() {return "";}
	static Color DarkColor(const Color &c, double darked = 0.6) {
		return Color(
			(int)round(c.GetR() * darked),
			(int)round(c.GetG() * darked),
			(int)round(c.GetB() * darked));
	}
};

#endif