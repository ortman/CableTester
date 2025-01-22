#ifndef _CableTester_Viewer_h_
#define _CableTester_Viewer_h_

#include <CtrlLib/CtrlLib.h>
#include "MainCable.hpp"

using namespace Upp;

class Viewer : public ParentCtrl {
private:
	DrawingDraw dd;
	
public:
	Viewer(): dd(500, 480) {}
	
	virtual void Paint(Draw& w) {
		w.DrawDrawing(GetSize(), dd);
	}
	
	void Show(MainCable *cable) {
		Size sz = dd.GetSize();
		cable->CalculateConnectorsPosition(sz);
		dd.DrawRect(0, 0, sz.cx, sz.cy, White);
		cable->Draw(dd);
		Refresh();
	}
};

#endif
