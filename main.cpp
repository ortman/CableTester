#include "CableTesterDesktop.h"
#include "Parser.hpp"

CableTester::CableTester() {
	CtrlLayout(*this, "CableManager");
	Sizeable().Zoomable();
	
	list.ItemHeight(25);
	
	Vector<String> cableFiles = FindAllPaths("C:/PROJECTS/UPP/MyApps/CableTesterDesktop/Cabels", "*.cbl");
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
	
	bSave.WhenPush = [=] {
		if (currentCable != NULL) {
		  viewer.SaveImage(GetExeDirFile(list.GetValue(list.GetCursor()).ToString() + ".png"));
		}
	};
}

void CableTester::LoadFile(String filePath, String name) {
	ViewerSelector::Clear();
	currentCable = Parser::LoadFromFile(filePath, name);
	currentCable->Sort();
	//RLOG(*currentCable);
	viewer.Show(currentCable);
}

GUI_APP_MAIN {
	StdLogSetup(LOG_FILE, "log.log");
	CableTester().Run();
}
