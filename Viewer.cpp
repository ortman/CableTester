#include "Viewer.h"


//////////////////////////////////////////////////////////////
Viewer::Viewer(){
}

void Viewer::Show(Cable *cable) {
	Size sz(500,480);
	ImageDraw imgDraw(sz);
	imgDraw.DrawRect(0, 0, sz.cx, sz.cy, White);
	cable->CalculateConnectorsPosition(sz);
	cable->Draw(imgDraw);
	img = imgDraw;
}

void Viewer::Paint(Draw& w) {
	Size sz = GetSize();
	w.DrawImage(0, 0, sz.cx, sz.cy, img);
	//w.DrawImage(0, 0, img);
}