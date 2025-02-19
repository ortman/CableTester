#ifndef _CABLE_TESTER_HPP_
#define _CABLE_TESTER_HPP_

#include <CtrlLib/CtrlLib.h>
#include "Viewer.hpp"
#include "PropertiesCtrl.hpp"

using namespace Upp;

#define LAYOUTFILE <CableTesterDesktop/CableTesterDesktop.lay>
#include <CtrlCore/lay.h>

#define TFILE <CableTesterDesktop/CableTesterDesktop.t>
#include <Core/t.h>

class CableTester : public WithCableTesterLayout<TopWindow> {
private:
	String cableDir;
	void AddFileToList(String filePath);
	void LoadFile(String filePath, String name = "");
	void SaveFile(String filePath);
	MainCable* currentCable = NULL;
	CreateCableWindow createCableWindow;
	CreateCableWindow addCableWindow;
	CreateCableWindow addConnectorWindow;
public:
	CableTester();
	~CableTester();
};

#endif
