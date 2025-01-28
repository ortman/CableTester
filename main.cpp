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
			PNGEncoder png;
			DrawingDraw dd(500, 480);
			Size sz = dd.GetSize();
			dd.DrawRect(0, 0, sz.cx, sz.cy, White);
			currentCable->Draw(dd);
			ImageDraw iw(sz);
			iw.DrawDrawing(0, 0, dd);
			Image m = iw;
		  png.SaveFile(GetExeDirFile(list.GetValue(list.GetCursor()).ToString() + ".png"), m);
		}
	};
}

void CableTester::LoadFile(String filePath, String name) {
	
	currentCable = Parser::LoadFromFile(filePath, name);
	currentCable->SortLeft();
	//RLOG(*currentCable);
	viewer.Show(currentCable);
	return;
}

GUI_APP_MAIN {
	StdLogSetup(LOG_FILE, "log.log");
	CableTester().Run();
}
