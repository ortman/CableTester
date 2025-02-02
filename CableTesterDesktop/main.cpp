#include "CableTesterDesktop.h"
#include "Parser.hpp"

CableTester::CableTester() {
	CtrlLayout(*this, t_("Cable tester"));
	Sizeable().Zoomable();
	
	list.ItemHeight(25);
	
	Vector<String> cableFiles = FindAllPaths(GetExeDirFile("Cables"), "*.cbl");
	String name;
	for (String cableFile : cableFiles) {
		name = "  " + GetFileName(cableFile);
		name.TrimLast(4);
		list.Add(cableFile, name, true);
	}
	list.WhenSel = [=] {
		int i = list.GetCursor();
		if (i>=0) {
			LoadFile(list[i], list.GetValue(i));
		}
	};
	
	bCancel.Disable();
	//bSave.Disable();
	bSave.WhenPush = [=] {
		if (currentCable != NULL) {
		  viewer.SaveImage(GetExeDirFile(list.GetValue(list.GetCursor()).ToString().Mid(2) + ".png"));
		}
	};
	
	cWireColor.SetData(viewer.GetCreateWireColor());
	cWireColor.WhenAction = [=] {
		viewer.SetCreateWireColor(cWireColor.GetData());
	};
}

CableTester::~CableTester() {
	ViewerSelector::Clear();
	if (currentCable) delete currentCable;
}

void CableTester::LoadFile(String filePath, String name) {
	ViewerSelector::Clear();
	if (currentCable) delete currentCable;
	currentCable = Parser::LoadFromFile(filePath, name);
	currentCable->Sort();
	//RLOG(*currentCable);
	viewer.DrawCable(currentCable);
}

GUI_APP_MAIN {
	StdLogSetup(LOG_COUT|LOG_FILE);
	int lang = GetSystemLNG();
	lang = SetLNGCharset(lang, CHARSET_UTF8);
	SetLanguage(lang);
	CableTester().Run();
}
