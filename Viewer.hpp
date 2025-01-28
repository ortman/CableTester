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
	Wire *selectedWire = NULL;
	
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
	
	virtual void Paint(Draw& w) {
		Size sz = GetSize();
		//w.DrawRect(sz, White);
		if (dImg) w.DrawImage(GetSize(), *dImg);
		//if (objImg) w.DrawImage(GetSize(), objImg);
		
		double sX = (double)dSize.cx / (double)sz.cx;
		double sY = (double)dSize.cy / (double)sz.cy;
		if (sX < 1.6 || sX > 2.4 || sY < 1.6 || sY > 2.4) {
			Show(cable);
		}
	}
	
	void Show(MainCable *cable) {
		if (dImg) delete dImg;
		if (this->cable != cable) {
			selectedWire = NULL;
			this->cable = cable;
		}
		if (cable != NULL) {
			Size sz = GetSize();
			dSize = {sz.cx*2, sz.cy*2};
			dImg = new ImageDraw(dSize);
			dImg->DrawRect(dSize, White);
			ImageDraw objID(dSize);
			cable->CalculateConnectorsPosition(dSize);
			if (selectedWire) {
				selectedWire->Draw(*dImg, dSize.cx / 5, (int)round(Wire::pen * 1.5), Black);
			}
			cable->Draw(*dImg, objID, dSize);
			objImg = objID;
		}
		Refresh();
	}
	
	void SaveImage(const String& str) {
		PNGEncoder png;
	  png.SaveFile(str, *dImg);
	}
	
	void MouseMove(Point p, dword keyflags) {
		Color id = GetId(p);
		CableNode* obj = ViewerSelector::Get(id);
		if (obj) {
			Tip(obj->GetTip());
		} else {
			Tip("");
		}
	}
	
	virtual void LeftDown(Point p, dword keyflags) {
		Color id = GetId(p);
		CableNode* obj = ViewerSelector::Get(id);
		if (obj) {
			Wire* w = dynamic_cast<Wire*>(obj);
			if (w) {
				selectedWire = w;
				Show(cable);
			}
		} else if (selectedWire) {
				selectedWire = NULL;
				Show(cable);
		}
	}
	
	virtual Image CursorImage (Point p, dword) {
		return GetId(p).GetRaw()? Image::Hand(): Image::Arrow();
	}
};

#endif
