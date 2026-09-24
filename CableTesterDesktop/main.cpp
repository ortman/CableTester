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
			String fileName = CurrentFileBase();
			//viewer.SaveImage(fileName + ".png");
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

	issuesWindow.WhenNode = [=](CableNode* node) {
		if (node) viewer.Select(node);
	};

	bAutoPins.WhenPush = [=] {
		if (currentCable == NULL) return;
		if (TesterPackage::HasAssignedPins(*currentCable) &&
		    !PromptYesNo(t_("Replace the assigned slot pins?"))) return;
		if (!TesterPackage::AutoAssign(*currentCable)) {
			Exclamation(t_("Not enough slot pins, some connector pins are left unassigned."));
		}
		viewer.WhenSelect();
	};

	bCheck.WhenPush = [=] {
		CheckPins(false);
	};

	bExport.WhenPush = [=] {
		if (currentCable == NULL || list.GetCursor() < 0) return;
		if (!CheckPins(true)) return;
		if (!DirectoryExists(cableDir)) DirectoryCreate(cableDir);
		String base = CurrentFileBase();
		if (viewer.ExportPackage(base + ".ctp", base + ".jpg", GetFileTitle(base))) {
			PromptOK(Format(t_("Exported:&[* \1%s\1]&[* \1%s\1]"), base + ".ctp", base + ".jpg"));
		} else {
			Exclamation(t_("Can not write the export files."));
		}
	};
}

String CableTester::CurrentFileBase() {
	return cableDir + "/" + list.GetValue(list.GetCursor()).ToString().Mid(2);
}

// Shows the pin map problems. For export returns true when the export can be continued.
bool CableTester::CheckPins(bool forExport) {
	if (currentCable == NULL) return false;
	Vector<TesterPackage::Issue> issues = TesterPackage::Validate(*currentCable);
	if (issues.GetCount() == 0) {
		if (!forExport) PromptOK(t_("The slot pin map is correct."));
		return true;
	}
	bool hasErrors = TesterPackage::HasErrors(issues);
	String info;
	if (forExport) {
		info = hasErrors ? t_("Fix the errors before the export.") : t_("Press OK to continue the export.");
	} else {
		info = hasErrors ? t_("The slot pin map has errors.") : t_("The slot pin map has warnings.");
	}
	bool ok = issuesWindow.Run(issues, info, forExport && !hasErrors);
	return forExport && !hasErrors && ok;
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
		try {
			currentCable = MainCable::FromData(::LoadFile(filePath));
		} catch (const CableNode::FileError& e) {
			ErrorOK(DeQtf(e));
			currentCable = new MainCable(name);
		}
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
