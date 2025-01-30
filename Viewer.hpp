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
	Index<Wire*> selectedWire;
	
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
	
	bool isSelectCable(Cable *c) {
		for (Wire *w : c->GetWires()) {
			if (selectedWire.Find(w) < 0) return false;
		}
		for (Cable *cc : c->GetCables()) {
			if (!isSelectCable(cc)) return false;
		}
		return c->GetCables().GetCount() || c->GetWires().GetCount();
	}
	
	void SelectCable(Cable *c, bool isSelect) {
		for (Wire *w : c->GetWires()) {
			if (isSelect) {
				selectedWire.FindAdd(w);
			} else {
				int idx = selectedWire.Find(w);
				if (idx >= 0) selectedWire.Remove(idx);
			}
		}
		for (Cable *cc : c->GetCables()) {
			SelectCable(cc, isSelect);
		}
	}
	
	bool isSelectConnector(Connector *cr, Cable *c) {
		for (Wire *w : c->GetWires()) {
			if (w->GetLeftConnector() == cr || w->GetRightConnector() == cr) {
				if (selectedWire.Find(w) < 0) return false;
			}
		}
		for (Cable *cc : c->GetCables()) {
			if (!isSelectConnector(cr, cc)) return false;
		}
		return c->GetCables().GetCount() || c->GetWires().GetCount();
	}
	
	void SelectConnector(Connector *cr, Cable *c, bool isSelect) {
		for (Wire *w : c->GetWires()) {
			if ((w->GetLeftConnector() == cr || w->GetRightConnector() == cr)) {
				if (isSelect) {
					selectedWire.FindAdd(w);
				} else {
					int idx = selectedWire.Find(w);
					if (idx >= 0) selectedWire.Remove(idx);
				}
			}
		}
		for (Cable *cc : c->GetCables()) {
			SelectConnector(cr, cc, isSelect);
		}
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
	
	void Show(MainCable *cable) {
		if (dImg) delete dImg;
		if (this->cable != cable) {
			selectedWire.Clear();
			this->cable = cable;
		}
		if (cable != NULL) {
			Size sz = GetSize();
			dSize = {sz.cx*2, sz.cy*2};
			dImg = new ImageDraw(dSize);
			dImg->DrawRect(dSize, White);
			ImageDraw objID(dSize);
			cable->CalculateConnectorsPosition(dSize);
			for (Wire* w : selectedWire) {
				w->Draw(*dImg, NULL, dSize.cx / 5, (int)round(Wire::pen * 1.5), Black);
			}
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
		Wire* w;
		Cable* c;
		Connector* cr;
		if (!(keyflags & K_CTRL)) selectedWire.Clear();
		Color id = GetId(p);
		CableNode* obj = ViewerSelector::Get(id);
		if (obj) {
			if ((w = dynamic_cast<Wire*>(obj)) != NULL) {
				int idx = selectedWire.Find(w);
				if (idx < 0) {
					selectedWire.Add(w);
				} else {
					selectedWire.Remove(idx);
				}
			} else if ((c = dynamic_cast<Cable*>(obj)) != NULL) {
				SelectCable(c, !isSelectCable(c));
			} else if ((cr = dynamic_cast<Connector*>(obj)) != NULL) {
				int pin = id.GetRaw() >> 16;
				if (pin) {
					createPoint = p;
					if (cr->IsLeft()) {
						createWire = new Wire(createWireColor, cr, pin, NULL, 0);
					} else {
						createWire = new Wire(createWireColor, NULL, 0, cr, pin);
					}
				} else {
					SelectConnector(cr, cable->GetCable(), !isSelectConnector(cr, cable->GetCable()));
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
	
	void RemoveSelectedWires(Cable* c) {
		Vector<Wire*>& wires = c->GetWires();
		for (int i = wires.GetCount() - 1; i >= 0; --i) {
			if (selectedWire.Find(wires[i]) >= 0) {
				wires.Remove(i);
			}
		}
		for (Cable *cc : c->GetCables()) {
			RemoveSelectedWires(cc);
		}
	}
	
	virtual bool HotKey(dword key) {
		switch (key) {
			case K_DELETE:
				RemoveSelectedWires(cable->GetCable());
				selectedWire.Clear();
				Show(cable);
				return true;
		}
		return false;
	}
};

#endif
