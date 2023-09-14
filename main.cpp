#include "CableTester.h"

CableTester::CableTester() {
	CtrlLayout(*this, "CableManager");
	Sizeable().Zoomable();
	
	list.ItemHeight(30);
	
	Add(viewer.TopPos(0,300).VSizePos(2,2).HSizePos(200, 2));
	Refresh();
	viewer.Refresh();
	
	Vector<String> cableFiles = FindAllPaths("D:/UPP/out/MyApps/CLANGx64.Blitz.Gui", "*.cbl");
	String name;
	for (String cableFile : cableFiles) {
		name = GetFileName(cableFile);
		name.TrimLast(4);
		list.Add(cableFile, name, true);
	}
	Add(list.LeftPos(2, 200).VSizePos(2,2));
	list.WhenSel = [=] {
		int i = list.GetCursor();
		if (i>=0) {
			LoadFile(list[i]);
		}
	};
}

void CableTester::LoadFile(String fileName) {
	Connector dsub25m("DSUB25M", 25, true);
	
	Connector mf3_4mX("MF3.0 1x04M обж (дигатель X)", 4, false);
	Connector mf3_4mY("MF3.0 1x04M обж (дигатель Y)", 4, false);
	Connector mf3_3mX("MF3.0 1x03M обж (концевик X)", 3, false);
	Connector mf3_3mY("MF3.0 1x03M обж (концевик Y)", 3, false);
	Connector ph_7fcZ("PH-7FC (двигатель и концевик Z)", 7, false);
	
	Cable *cover, *wisp, *cable = new Cable("XYZ");
	
	cover = new Cable("Оплётка 8мм");
		wisp = new Cable("Провод 9-пиновый");
			wisp->Add(new Wire(0x6495ed, &dsub25m, 24, &mf3_4mX, 1));
			wisp->Add(new Wire(0x483d8b, &dsub25m, 12, &mf3_4mX, 2));
			wisp->Add(new Wire(0x808080, &dsub25m, 11, &mf3_4mX, 3));
			wisp->Add(new Wire(0x8b4513, &dsub25m, 25, &mf3_4mX, 4));
			wisp->Add(new Wire(0xffd700, &dsub25m, 21, &mf3_4mY, 1));
			wisp->Add(new Wire(0xb22222, &dsub25m,  9, &mf3_4mY, 2));
			wisp->Add(new Wire(0xdaa520, &dsub25m,  8, &mf3_4mY, 3));
			wisp->Add(new Wire(0x006400, &dsub25m, 22, &mf3_4mY, 4));
			wisp->Add(new Wire(0x222222, &dsub25m, 22, NULL, 0));
			wisp->Add(new Wire(0xA0A0A0, &dsub25m, 22, NULL, 0));
		cover->Add(wisp);
		wisp = new Cable("Провод 6-пиновый");
			wisp->Add(new Wire(0xb22222, &dsub25m, 15, &mf3_3mX, 1));
			wisp->Add(new Wire(0x222222, &dsub25m,  3, &mf3_3mX, 2));
			wisp->Add(new Wire(0x006400, &dsub25m,  2, &mf3_3mX, 3));
			wisp->Add(new Wire(0xdaa520, &dsub25m, 15, &mf3_3mY, 1));
			wisp->Add(new Wire(0x8b4513, &dsub25m, 14, &mf3_3mY, 2));
			wisp->Add(new Wire(0x6495ed, &dsub25m,  1, &mf3_3mY, 3));
			wisp->Add(new Wire(0xA0A0A0, &dsub25m, 16, NULL, 0));
		cover->Add(wisp);
	cable->Add(cover);
	cover = new Cable("Оплётка 8мм");
		wisp = new Cable("Провод 4-пиновый");
			wisp->Add(new Wire(0x8b4513, &dsub25m, 17, &ph_7fcZ, 1));
			wisp->Add(new Wire(0xb22222, &dsub25m,  5, &ph_7fcZ, 2));
			wisp->Add(new Wire(0xdaa520, &dsub25m,  4, &ph_7fcZ, 3));
			wisp->Add(new Wire(0x222222, &dsub25m, 18, &ph_7fcZ, 4));
			wisp->Add(new Wire(0xA0A0A0, &dsub25m, 19, NULL, 0));
		cover->Add(wisp);
		wisp = new Cable("Провод 3-пиновый");
			wisp->Add(new Wire(0xb22222, &dsub25m, 15, &ph_7fcZ, 5));
			wisp->Add(new Wire(0x8b4513, &dsub25m,  7, &ph_7fcZ, 6));
			wisp->Add(new Wire(0x006400, &dsub25m,  6, &ph_7fcZ, 7));
			wisp->Add(new Wire(0xA0A0A0, &dsub25m, 20, NULL, 0));
		cover->Add(wisp);
	cable->Add(cover);
	viewer.Show(cable);
}

GUI_APP_MAIN {
	CableTester().Run();
}
