#ifndef _VIEWER_HPP_
#define _VIEWER_HPP_

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
			Show(cable);
		}
	}
	
	void DrawSelected() {
		Wire* w;
		Connector* con;
		Cable* cbl;
		for (CableNode* node : sels) {
			if ((cbl = dynamic_cast<Cable*>(node))) {
				Rect r = cbl->GetCoverRect();
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
	
	void Show(MainCable *cable) {
		if (dImg) delete dImg;
		if (this->cable != cable) {
			sels.Clear();
			this->cable = cable;
		}
		if (cable != NULL) {
			Size sz = GetSize();
			dSize = {sz.cx*2, sz.cy*2};
			dImg = new ImageDraw(dSize);
			dImg->DrawRect(dSize, White);
			ImageDraw objID(dSize);
			cable->CalculateConnectorsPosition(dSize);
			DrawSelected();
			cable->Draw(*dImg, &objID, dSize);
			objImg = objID;
		}
		Refresh();
	}
	
	void SaveImage(const String& str) {
		PNGEncoder png;
		Size nextionImageSize = {480*2, 760*2};
		ImageDraw nextionImg(nextionImageSize);
		nextionImg.DrawRect(nextionImageSize, White);
		cable->CalculateConnectorsPosition(nextionImageSize);
		cable->Draw(nextionImg, NULL, nextionImageSize);
		png.SaveFile(str, nextionImg);
		Show(cable);
	}
	
	virtual void LeftDown(Point p, dword keyflags) {
		if (cable == NULL) return;
		Connector* cr;
		if (!(keyflags & K_CTRL)) sels.Clear();
		Color id = GetId(p);
		CableNode* obj = ViewerSelector::Get(id);
		if (obj) {
			int pin = id.GetRaw() >> 16;
			if ((cr = dynamic_cast<Connector*>(obj)) != NULL && pin) {
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
			}
		}
		Show(cable);
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
							cable->GetCable()->Add(createWire);
							ViewerSelector::Add(createWire);
							createWire = NULL;
						}
					}
				}
			}
			if (createWire) {
				delete createWire;
				createWire = NULL;
			}
			Show(cable);
		}
	}
	
	void MouseMove(Point p, dword keyflags) {
		if (createWire) {
			createPoint = p;
			Tip("");
			Refresh();
		} else {
			Color id = GetId(p);
			CableNode* obj = ViewerSelector::Get(id);
			if (obj) {
				Tip(obj->GetTip());
			} else {
				Tip("");
			}
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
	
	void RemoveCable(Cable* c) {
//		Vector<Wire*>& wires = c->GetWires();
//		for (int i = wires.GetCount() - 1; i >= 0; --i) {
//			if (selectedWire.Find(wires[i]) >= 0) {
//				wires.Remove(i);
//			}
//		}
		for (Cable *cc : c->GetCables()) {
			RemoveCable(cc);
		}
	}
	
	void RemoveSels() {
		for (CableNode* node : sels) {
			
		}
	}
	
	virtual bool HotKey(dword key) {
		switch (key) {
			case K_DELETE:
				RemoveSels();
				sels.Clear();
				Show(cable);
				return true;
		}
		return false;
	}
};

#endif
