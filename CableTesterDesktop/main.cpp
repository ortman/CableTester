#include "CableTesterDesktop.h"

CableTester::CableTester() {
	cableDir = GetExeDirFile("Cables");
	//SetDarkThemeEnabled(!IsDarkThemeEnabled());
	Connector::borderColor = SGreen;
	Connector::textColor = SBlue;
	CtrlLayout(*this, t_("Cable tester"));
	Sizeable().Zoomable();
	
	pProperties.Hide();
	list.ItemHeight(25);
	bAddCable.SetImage(CtrlImg::Add());
	bAddConnector.SetImage(CtrlImg::Add());
	bCreateCable.SetImage(CtrlImg::Add());
	
	Vector<String> cableFiles = FindAllPaths(cableDir, "*.cbl");
	for (String cableFile : cableFiles) {
		AddFileToList(cableFile);
	}
	list.WhenSel = [=] {
		int i = list.GetCursor();
		if (i>=0) {
			LoadFile(list[i], list.GetValue(i));
		}
	};
	
	bCancel.Disable();
	bSave.WhenPush = [=] {
		if (currentCable != NULL) {
			if (!DirectoryExists(cableDir)) DirectoryCreate(cableDir);
			String fileName = cableDir + "/" + list.GetValue(list.GetCursor()).ToString().Mid(2);
			viewer.SaveImage(fileName + ".png");
			SaveFile(fileName + ".cbl");
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
				WString name = addCableWindow.GetName();
				name.Replace("\\n", "\n");
				Cable* c = new Cable(name, LtGray);
				currentCable->Add(c);
				ViewerSelector::Add(c);
				viewer.Select(c);
			}
			addCableWindow.Close();
			viewer.DrawCable();
		}
	};
	
	bAddConnector.WhenPush = [=] {
		if (currentCable) {
			addConnectorWindow.Open();
			if (addConnectorWindow.RunAppModal() != 0) {
				WString name = addConnectorWindow.GetName();
				name.Replace("\\n", "\n");
				Connector* cn = new Connector(name, 3, true);
				currentCable->AddConnector(cn);
				ViewerSelector::Add(cn);
				viewer.Select(cn);
			}
			addConnectorWindow.Close();
			viewer.DrawCable();
		}
	};
	
	bCreateCable.WhenPush = [=] {
		createCableWindow.Open();
		if (createCableWindow.RunAppModal() != 0) {
			String name = createCableWindow.GetName().ToString();
			AddFileToList(cableDir + "/" + name + ".cbl");
		}
		createCableWindow.Close();
	};
	
	bSort.WhenPush = [=] {
		if (currentCable) {
			currentCable->Sort();
			viewer.DrawCable();
		}
	};
}

CableTester::~CableTester() {
	ViewerSelector::Clear();
	if (currentCable) delete currentCable;
}

void CableTester::AddFileToList(String filePath) {
	String name = "  " + GetFileName(filePath);
	name.TrimLast(4);
	list.Add(filePath, name, true);
}

void CableTester::LoadFile(String filePath, WString name) {
	pProperties.Clear();
	if (currentCable) delete currentCable;
	if (FileExists(filePath)) {
		FileIn f(filePath);
		try {
			currentCable = MainCable::FromData(f);
		} catch (const CableNode::FileError& e) {
			ErrorOK(e);
			currentCable = new MainCable(name);
		}
		f.Close();
	} else {
		currentCable = new MainCable(name);
	}
	if (currentCable) currentCable->Sort();
	//RLOG(*currentCable);
	viewer.DrawCable(currentCable);
}

void CableTester::SaveFile(String filePath) {
	if (currentCable) {
		FileOut out(filePath);
		currentCable->ToData(out);
	}
}

GUI_APP_MAIN {
	StdLogSetup(LOG_COUT|LOG_FILE);
	int lang = GetSystemLNG();
	lang = SetLNGCharset(lang, CHARSET_UTF8);
	SetLanguage(lang);
	//SetLanguage(LNG_('E', 'N', 'U', 'S'));
	CableTester().Run();
}
