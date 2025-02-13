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
		Wire* w;
		Cable* c;
		const Index<CableNode*>& sels = viewer.GetSels();
		if (sels.GetCount() == 1) {
			if ((w = dynamic_cast<Wire*>(sels[0]))) {
				w->SetColor(cWireColor.GetData());
				viewer.DrawCable();
			} else if ((c = dynamic_cast<Cable*>(sels[0]))) {
				c->SetColor(cWireColor.GetData());
				viewer.DrawCable();
			}
		}
	};
	
	viewer.WhenSelect = [=] {
		Wire* w;
		Cable* c, *cc;
		const Index<CableNode*>& sels = viewer.GetSels();
		int selCount = sels.GetCount();
		if (selCount) {
			if (selCount == 1 && (w = dynamic_cast<Wire*>(sels[0]))) {
				const Color& color = w->GetColor();
				cWireColor.SetData(color);
				viewer.SetCreateWireColor(color);
				cWireColor.Show();
				if (currentCable && (cc = currentCable->GetWireCable(w))) {
					dlWireCable.SetData(cc->GetName());
				}
			} else if (selCount == 1 && (c = dynamic_cast<Cable*>(sels[0]))) {
				const Color& color = c->GetColor();
				cWireColor.SetData(color);
				viewer.SetCreateWireColor(color);
				cWireColor.Show();
				if (currentCable && (cc = currentCable->GetParentCable(c))) {
					dlWireCable.SetData(cc->GetName());
				}
			} else {
				cWireColor.Hide();
			}
			dlWireCable.Show();
		} else {
			dlWireCable.Hide();
			cWireColor.Show();
		}
	};
}

CableTester::~CableTester() {
	ViewerSelector::Clear();
	if (currentCable) delete currentCable;
}

void CableTester::AddCableNameToList(Cable* cable) {
	dlWireCable.Add(cable->GetName());
	for (Cable* c : cable->GetCables()) {
		AddCableNameToList(c);
	}
}

void CableTester::LoadFile(String filePath, String name) {
	dlWireCable.Hide();
	dlWireCable.Clear();
	ViewerSelector::Clear();
	if (currentCable) delete currentCable;
	currentCable = Parser::LoadFromFile(filePath, name);
	currentCable->Sort();
	//RLOG(*currentCable);
	viewer.DrawCable(currentCable);
	AddCableNameToList(currentCable);
}

GUI_APP_MAIN {
	StdLogSetup(LOG_COUT|LOG_FILE);
	int lang = GetSystemLNG();
	lang = SetLNGCharset(lang, CHARSET_UTF8);
	SetLanguage(lang);
	CableTester().Run();
}
