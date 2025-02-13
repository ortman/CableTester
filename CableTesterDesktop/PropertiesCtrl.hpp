#ifndef _PROPERTIES_CTRL_HPP_
#define _PROPERTIES_CTRL_HPP_

#include <CtrlLib/CtrlLib.h>
#include "PropertiesCtrl.hpp"

using namespace Upp;

#define LAYOUTFILE <CableTesterDesktop/SubCtrls.lay>
#include <CtrlCore/lay.h>

class PropertiesCtrl : public WithPropertiesLayout<ParentCtrl> {
private:
	void AddCableNameToList(Cable* cable) {
		dlCables.Add(cable->GetName());
		for (Cable* c : cable->GetCables()) {
			AddCableNameToList(c);
		}
	}
	
public:
	PropertiesCtrl() {
		CtrlLayout(*this);
	
		/*
		cColor.WhenAction = [=] {
			Wire* w;
			Cable* c;
			const Index<CableNode*>& sels = viewer.GetSels();
			if (sels.GetCount() == 1) {
				if ((w = dynamic_cast<Wire*>(sels[0]))) {
					w->SetColor(cColor.GetData());
					viewer.DrawCable();
				} else if ((c = dynamic_cast<Cable*>(sels[0]))) {
					c->SetColor(cColor.GetData());
					viewer.DrawCable();
				}
			}
		};
		*/
	}
	
	void Clear() {
		Hide();
		dlCables.Clear();
		
	}
	
	void Set(MainCable* mainCable, const Index<CableNode*>& sels) {
		if (sels.GetCount() != 1) {
			Clear();
			return;
		}
		dlCables.Clear();
		AddCableNameToList(mainCable);
		Wire* w;
		Cable* c, *cc;
		Connector* cn;
		if ((w = dynamic_cast<Wire*>(sels[0]))) {
			lPinCount.Hide();
			ePinCount.Hide();
			lName.Hide();
			eName.Hide();
			const Color& color = w->GetColor();
			cColor.SetData(color);
			if (mainCable && (cc = mainCable->GetWireCable(w))) {
				dlCables.SetData(cc->GetName());
			}
			lColor.Show();
			cColor.Show();
		} else if ((c = dynamic_cast<Cable*>(sels[0]))) {
			lPinCount.Hide();
			ePinCount.Hide();
			const Color& color = c->GetColor();
			cColor.SetData(color);
			if (mainCable && (cc = mainCable->GetParentCable(c))) {
				dlCables.SetData(cc->GetName());
			}
			eName <<= c->GetName();
			dlCables.Show();
			lColor.Show();
			cColor.Show();
			lName.Show();
			eName.Show();
		} else if ((cn = dynamic_cast<Connector*>(sels[0]))) {
			lColor.Hide();
			cColor.Hide();
			eName <<= cn->GetName();
			ePinCount <<= cn->GetPinCount();
			lName.Show();
			eName.Show();
			lPinCount.Show();
			ePinCount.Show();
		}
		Show();
	}
};

#endif
