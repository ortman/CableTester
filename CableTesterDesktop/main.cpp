#include "CableTesterDesktop.h"
#include "Parser.hpp"

CableTester::CableTester() {
	CtrlLayout(*this, t_("Cable tester"));
	Sizeable().Zoomable();
	
	pProperties.Hide();
	list.ItemHeight(25);
	bAddCable.SetImage(CtrlImg::Add());
	bAddConnector.SetImage(CtrlImg::Add());
	bCreateCable.SetImage(CtrlImg::Add());
	
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
	
	viewer.WhenSelect = [=] {
		const Index<CableNode*>& sels = viewer.GetSels();
		if (sels.GetCount() == 1) {
			pProperties.Set(currentCable, sels[0]);
		} else {
			pProperties.Clear();
		}
	};
	
	pProperties.WhenUpdate = [=] {
		viewer.DrawCable();
	};
	
	pProperties.WhenSortUpdate = [=] {
		currentCable->Sort();
		viewer.DrawCable();
	};
	
	bAddCable.WhenPush = [=] {
		if (currentCable) {
			addCableWindow.Open();
			if (addCableWindow.RunAppModal() != 0) {
				currentCable->Add(addCableWindow.GetCable());
			}
			addCableWindow.Close();
			viewer.DrawCable();
		}
	};
	
	bAddConnector.WhenPush = [=] {
		if (currentCable) {
			addConnectorWindow.Open();
			if (addConnectorWindow.RunAppModal() != 0) {
				currentCable->AddConnector(addConnectorWindow.GetConnector());
			}
			addConnectorWindow.Close();
			viewer.DrawCable();
		}
	};
	
	bCreateCable.WhenPush = [=] {
		createCableWindow.Open();
		if (createCableWindow.RunAppModal() != 0) {
			String name = createCableWindow.GetName();
			//list.Add(cableFile, name, true);
		}
		createCableWindow.Close();
	};
}

CableTester::~CableTester() {
	ViewerSelector::Clear();
	if (currentCable) delete currentCable;
}

void CableTester::LoadFile(String filePath, String name) {
	pProperties.Clear();
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
