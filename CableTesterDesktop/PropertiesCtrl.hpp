#ifndef _PROPERTIES_CTRL_HPP_
#define _PROPERTIES_CTRL_HPP_

#include <CtrlLib/CtrlLib.h>
#include "PropertiesCtrl.hpp"

using namespace Upp;

#define LAYOUTFILE <CableTesterDesktop/SubCtrls.lay>
#include <CtrlCore/lay.h>

class PropertiesCtrl : public WithPropertiesLayout<ParentCtrl> {
private:
	MainCable* mainCable = NULL;
	CableNode* node = NULL;
	
	void AddCableNameToList(Cable* cable) {
		dlParentCable.Add((int64_t)cable, cable->GetName());
		for (Cable* c : cable->GetCables()) {
			AddCableNameToList(c);
		}
	}
	
public:
	Event<> WhenUpdate;
	Event<> WhenSortUpdate;
	
	PropertiesCtrl() {
		CtrlLayout(*this);
		
		dlLeftRight.Add(t_("Left"));
		dlLeftRight.Add(t_("Right"));
		
		bPosUp.SetImage(CtrlImg::SmallUp());
		bPosDown.SetImage(CtrlImg::SmallDown());
	
		cColor.WhenAction = [=] {
			Wire* w;
			Cable* c;
			if (node != NULL) {
				if ((w = dynamic_cast<Wire*>(node))) {
					w->SetColor(cColor.GetData());
				} else if ((c = dynamic_cast<Cable*>(node))) {
					c->SetColor(cColor.GetData());
				}
				WhenUpdate();
			}
		};
		ePinCount.WhenAction = [=] {
			Connector* cn;
			if (node != NULL && (cn = dynamic_cast<Connector*>(node))) {
				cn->SetPinCount(ePinCount);
				WhenSortUpdate();
			}
		};
		dlLeftRight.WhenAction = [=] {
			Connector* cn;
			if (node != NULL && (cn = dynamic_cast<Connector*>(node))) {
				cn->SetIsLeft(dlLeftRight.GetIndex() == 0);
				WhenSortUpdate();
			}
		};
		dlParentCable.WhenAction = [=] {
			Wire* w;
			Cable* c;
			if (node != NULL && mainCable != NULL) {
				if ((w = dynamic_cast<Wire*>(node))) {
					mainCable->RemoveWire(w, true);
					Cable* pCable = (Cable*)(int64_t)dlParentCable.GetData();
					pCable->Add(w);
				} else if ((c = dynamic_cast<Cable*>(node))) {
					mainCable->RemoveCable(c, true, false);
					Cable* pCable = (Cable*)(int64_t)dlParentCable.GetData();
					pCable->Add(c);
				}
				WhenSortUpdate();
			}
		};
		eName.WhenEnter = [=] {
			Cable* c;
			Connector* cn;
			if (node != NULL) {
				String name = ~eName;
				name.Replace("\\n", "\n");
				if ((c = dynamic_cast<Cable*>(node))) {
					c->SetName(name);
				} else if ((cn = dynamic_cast<Connector*>(node))) {
					cn->SetName(name);
				}
				WhenUpdate();
			}
		};
	}
	
	void Clear() {
		mainCable = NULL;
		node = NULL;
		Hide();
		//dlCables.Clear();
	}
	
	void Set(MainCable* mainCable, CableNode* node) {
		this->mainCable = mainCable;
		this->node = node;
		dlParentCable.Clear();
		dlParentCable.Add((int64_t)mainCable, t_("No"));
		for (Cable* c : mainCable->GetCables()) {
			AddCableNameToList(c);
		}
		Wire* w;
		Cable* c, *cc;
		Connector* cn;
		if ((w = dynamic_cast<Wire*>(node))) {
			lPinCount.Hide();
			ePinCount.Hide();
			lLeftRight.Hide();
			dlLeftRight.Hide();
			lPosition.Hide();
			bPosUp.Hide();
			bPosDown.Hide();
			lName.Hide();
			eName.Hide();
			const Color& color = w->GetColor();
			cColor.SetData(color);
			if (mainCable && (cc = mainCable->GetWireCable(w))) {
				dlParentCable.SetData((int64_t)cc);
			}
			lColor.Show();
			cColor.Show();
			lParentCable.Show();
			dlParentCable.Show();
		} else if ((c = dynamic_cast<Cable*>(node))) {
			lPinCount.Hide();
			ePinCount.Hide();
			lLeftRight.Hide();
			dlLeftRight.Hide();
			lPosition.Hide();
			bPosUp.Hide();
			bPosDown.Hide();
			const Color& color = c->GetColor();
			cColor.SetData(color);
			if (mainCable && (cc = mainCable->GetParentCable(c))) {
				dlParentCable.SetData((int64_t)cc);
			}
			String name = c->GetName();
			name.Replace("\n", "\\n");
			eName <<= name;
			lColor.Show();
			cColor.Show();
			lName.Show();
			eName.Show();
			lParentCable.Show();
			dlParentCable.Show();
		} else if ((cn = dynamic_cast<Connector*>(node))) {
			lColor.Hide();
			cColor.Hide();
			lParentCable.Hide();
			dlParentCable.Hide();
			String name = cn->GetName();
			name.Replace("\n", "\\n");
			eName <<= name;
			ePinCount <<= cn->GetPinCount();
			dlLeftRight.SetIndex(cn->IsLeft() ? 0 : 1);
			lName.Show();
			eName.Show();
			lPinCount.Show();
			ePinCount.Show();
			lLeftRight.Show();
			dlLeftRight.Show();
			lPosition.Show();
			bPosUp.Show();
			bPosDown.Show();
		}
		Show();
	}
};

class CreateCableWindow : public WithCreateCableLayout<TopWindow> {
public:
	CreateCableWindow() {
		CtrlLayout(*this, t_("Input caption"));
		bOk.WhenAction = Breaker(1);
		WhenClose = bCancel.WhenAction = Breaker(0);
		eName <<= "";
	}
	String GetName() {
		return ~eName;
	}
};

#endif
