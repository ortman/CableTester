#ifndef _CABLE_TESTER_HPP_
#define _CABLE_TESTER_HPP_

#include <CtrlLib/CtrlLib.h>
#include "Viewer.hpp"

using namespace Upp;

#define LAYOUTFILE <CableTesterDesktop/CableTesterDesktop.lay>
#include <CtrlCore/lay.h>

class CableTester : public WithCableTesterLayout<TopWindow> {
private:
	void LoadFile(String filePath, String name = "");
	MainCable* currentCable = NULL;
public:
	CableTester();
};

#endif
