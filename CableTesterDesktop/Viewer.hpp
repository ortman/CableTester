#ifndef _VIEWER_HPP_
#define _VIEWER_HPP_

#define CTD_REMOVE_ALL		1
#define CTD_REMOVE_WIRES	0
#define CTD_REMOVE_CANCEL	-1

#include <CtrlLib/CtrlLib.h>
#include "MainCable.hpp"

using namespace Upp;

class Viewer : public Ctrl {
private:
	ImageDraw *dImg = NULL;
	Image objImg;
	Size dSize;
	MainCable *cable = NULL;
	Index<CableNode*> sels;
	
	Wire* createWire = NULL;
	Color createWireColor = LtGreen;
	Point createPoint;
	
	Color GetId(const Point &p) {
		Size sz = GetSize();
		int x = (int)(p.x * dSize.cx / sz.cx);
		int y = (int)(p.y * dSize.cy / sz.cy);
		if (x < dSize.cx && y < dSize.cy) return objImg[y][x];
		return Black;
	}
	
public:
	Event<> WhenSelect;
	
	Viewer() {
	}
	
	~Viewer() {
		if (dImg) delete dImg;
	}
	
	double GetScale() {
		if (dImg) {
			Size sz = GetSize();
			return max((double)dSize.cx / sz.cx, (double)dSize.cy / sz.cy);
		}
		return NAN;
	}
	
	void SetCreateWireColor(const Color& c) {
		createWireColor = c;
	}
	
	Color& GetCreateWireColor() {
		return createWireColor;
	}
	
	const Index<CableNode*>& GetSels() {
		return sels;
	}
	
	virtual void Paint(Draw& w) {
		Size sz = GetSize();
		//w.DrawRect(sz, White);
		if (dImg) w.DrawImage(GetSize(), *dImg);
		//if (objImg) w.DrawImage(GetSize(), objImg);
		
		double sX = (double)dSize.cx / (double)sz.cx;
		double sY = (double)dSize.cy / (double)sz.cy;
		
		int cowerWith = sz.cx / 5;
		int pinWidth = sz.cx / 6;
		if (createWire) {
			createWire->Draw(w, {sX, sY}, createPoint, sz.cx - pinWidth - 10 - cowerWith);
		}
		if (sX < 1.6 || sX > 2.4 || sY < 1.6 || sY > 2.4) {
			DrawCable();
		}
	}
	
	void DrawSelected() {
		Wire* w;
		Connector* con;
		Cable* cbl;
		for (CableNode* node : sels) {
			if ((cbl = dynamic_cast<Cable*>(node))) {
				Rect r = cbl->GetCableRect();
				r.Inflate(5);
				dImg->DrawRect(r, Black);
			} else if ((con = dynamic_cast<Connector*>(node))) {
				Size sz = con->PinSize();
				Point p = con->Position();
				dImg->DrawRect(p.x - 5, p.y - 5, sz.cx + 10, sz.cy * (con->GetPinCount()+1) + 10, LtGray);
			} else if ((w = dynamic_cast<Wire*>(node))) {
				w->Draw(*dImg, dSize.cx / 5, (int)round(Wire::pen * 1.5), Black);
			}
		}
	}
	
	void DrawCable() {
		if (dImg) delete dImg;
		Size sz = GetSize();
		dSize = {sz.cx * 2, sz.cy * 2};
		dImg = new ImageDraw(dSize);
		dImg->DrawRect(dSize, White);
		ImageDraw objID(dSize);
		if (cable != NULL) {
			cable->CalculateConnectorsPosition(dSize);
			DrawSelected();
			cable->Draw(*dImg, &objID, dSize);
		}
		objImg = objID;
		Refresh();
	}
	
	void DrawCable(MainCable *cable) {
		sels.Clear();
		this->cable = cable;
		DrawCable();
	}
	
	void SaveImage(const String& str) {
		PNGEncoder png;
		Size nextionImageSize = {480*2, 760*2};
		ImageDraw nextionImg(nextionImageSize);
		nextionImg.DrawRect(nextionImageSize, White);
		cable->CalculateConnectorsPosition(nextionImageSize);
		cable->Draw(nextionImg, NULL, nextionImageSize);
		png.SaveFile(str, nextionImg);
		DrawCable();
	}
	
	virtual void LeftDown(Point p, dword keyflags) {
		if (cable == NULL) return;
		Connector* cr;
		bool whenSel = false;
		if (!(keyflags & K_CTRL) && sels.GetCount()) {
			whenSel = true;
			sels.Clear();
		}
		Color id = GetId(p);
		CableNode* obj = ViewerSelector::Get(id);
		if (obj) {
			int pin = id.GetRaw() >> 16;
			if ((cr = dynamic_cast<Connector*>(obj)) != NULL && pin) {
				sels.Clear();
				createPoint = p;
				if (cr->IsLeft()) {
					createWire = new Wire(createWireColor, cr, pin, NULL, 0);
				} else {
					createWire = new Wire(createWireColor, NULL, 0, cr, pin);
				}
			} else {
				int idx = sels.Find(obj);
				if (idx < 0) {
					sels.Add(obj);
				} else {
					sels.Remove(idx);
				}
				whenSel = true;
			}
		}
		DrawCable();
		if (whenSel) WhenSelect();
	}
	
	virtual void LeftUp(Point p, dword keyflags) {
		if (createWire) {
			Color id = GetId(p);
			CableNode* obj = ViewerSelector::Get(id);
			if (obj) {
				Connector* cr;
				if ((cr = dynamic_cast<Connector*>(obj)) != NULL) {
					int pin = id.GetRaw() >> 16;
					if (pin) {
						if (createWire->GetLeftConnector()) {
							createWire->SetRightConnector(cr, pin);
						} else {
							createWire->SetLeftConnector(cr, pin);
						}
						if (cable) {
							cable->Add(createWire);
							ViewerSelector::Add(createWire);
							sels.Add(createWire);
							createWire = NULL;
							WhenSelect();
						}
					}
				}
			}
			if (createWire) {
				delete createWire;
				createWire = NULL;
			}
			DrawCable();
		}
	}
	
	void MouseMove(Point p, dword keyflags) {
		if (createWire) {
			createPoint = p;
			Tip("");
			Refresh();
		} else {
			CableNode* obj = ViewerSelector::Get(GetId(p));
			Tip(obj ? obj->GetTip() : "");
		}
	}
	
	virtual Image CursorImage (Point p, dword) {
		Color id = GetId(p);
		if (id.GetRaw() == 0) return Image::Arrow();
		Connector* cr;
		CableNode* obj = ViewerSelector::Get(id);
		if ((cr = dynamic_cast<Connector*>(obj)) != NULL) {
			int pin = id.GetRaw() >> 16;
			if (pin) return Image::Cross();
		}
		return Image::Hand();
	}
	
	void RemoveSels() {
		Wire *w;
		Cable *c;
		Connector *cr;
		int answCables = -10;
		int answConnectors = -10;
		for (CableNode* node : sels) {
			if ((w = dynamic_cast<Wire*>(node))) {
				cable->RemoveWire(w, true);
				delete w;
			}	else if ((c = dynamic_cast<Cable*>(node))) {
				if (answCables == -10 && c->GetWires().GetCount() == 0 && c->GetCables().GetCount() == 0) {
					cable->RemoveCable(c, true, true);
					delete c;
				} else {
					if (answCables == -10) {
						answCables = Prompt(BEEP_NONE, Ctrl::GetAppName(), CtrlImg::question(),
								t_("What objects to remove from selected cables?"),
								t_("Cables and wires"), t_("Only wires"), t_("Cancel"));
					}
					if (answCables != CTD_REMOVE_CANCEL) cable->RemoveCable(c, answCables == CTD_REMOVE_ALL, true);
					if (answCables == CTD_REMOVE_ALL) delete c;
				}
			} else if ((cr = dynamic_cast<Connector*>(node))) {
				if (answConnectors == -10) {
					answConnectors = Prompt(BEEP_NONE, Ctrl::GetAppName(), CtrlImg::question(),
							t_("What objects to remove from selected connectors?"),
							t_("Connectors and wires"), t_("Only wires"), t_("Cancel"));
				}
				cable->RemoveConnector(cr, answConnectors == CTD_REMOVE_ALL);
				if (answConnectors == CTD_REMOVE_ALL) delete cr;
			}
		}
		sels.Clear();
		DrawCable();
		WhenSelect();
	}
	
	virtual bool HotKey(dword key) {
		switch (key) {
			case K_DELETE:
				RemoveSels();
				return true;
		}
		return false;
	}
};

#endif
