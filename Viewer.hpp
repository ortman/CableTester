#ifndef _VIEWER_HPP_
#define _VIEWER_HPP_

#include <CtrlLib/CtrlLib.h>
#include "MainCable.hpp"

using namespace Upp;

class Viewer : public ParentCtrl {
private:
	ImageDraw *dImg = NULL;
	Image objImg;
	Size dSize;
	MainCable *cable = NULL;
	
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
		this->cable = cable;
		if (cable != NULL) {
			Size sz = GetSize();
			dSize = {sz.cx*2, sz.cy*2};
			dImg = new ImageDraw(dSize);
			dImg->DrawRect(dSize, White);
			ImageDraw objID(dSize);
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
		Size sz = GetSize();
		Color id = objImg[(int)(p.y * dSize.cy / sz.cy)][(int)(p.x * dSize.cx / sz.cx)];
		CableNode* obj = ViewerSelector::Get(id);
		if (obj) {
			Tip(obj->GetTip());
		} else {
			Tip("");
		}
	}
	
	virtual Image CursorImage (Point p, dword) {
		Size sz = GetSize();
		Color id = objImg[(int)(p.y * dSize.cy / sz.cy)][(int)(p.x * dSize.cx / sz.cx)];
		return id.GetRaw()? Image::Hand(): Image::Arrow();
	}
};

#endif
