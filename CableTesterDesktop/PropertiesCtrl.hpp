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
		dlParentCable.Add(cable->GetName());
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
		AddCableNameToList(mainCable);
		Wire* w;
		Cable* c, *cc;
		Connector* cn;
		if ((w = dynamic_cast<Wire*>(node))) {
			lPinCount.Hide();
			ePinCount.Hide();
			lLeftRight.Hide();
			dlLeftRight.Hide();
			lName.Hide();
			eName.Hide();
			const Color& color = w->GetColor();
			cColor.SetData(color);
			if (mainCable && (cc = mainCable->GetWireCable(w))) {
				dlParentCable.SetData(cc->GetName());
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
			const Color& color = c->GetColor();
			cColor.SetData(color);
			if (mainCable && (cc = mainCable->GetParentCable(c))) {
				dlParentCable.SetData(cc->GetName());
			}
			eName <<= c->GetName();
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
			eName <<= cn->GetName();
			ePinCount <<= cn->GetPinCount();
			dlLeftRight.SetIndex(cn->IsLeft() ? 0 : 1);
			lName.Show();
			eName.Show();
			lPinCount.Show();
			ePinCount.Show();
			lLeftRight.Show();
			dlLeftRight.Show();
		}
		Show();
	}
};

#endif
