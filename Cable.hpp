#ifndef _CABLE_HPP_
#define _CABLE_HPP_

#include "Wire.hpp"
#include "CableNode.hpp"
#include <CtrlLib/CtrlLib.h>
using namespace Upp;

class Cable : public CableNode {
private:
	String name;
	Vector<Cable*> cables;
	Vector<Wire*> wires;
	Rect coverRect;
	Color color;
	
public:
	Cable(String name, Color color) : name(name), color(color) {}
	
	void Add(Cable *cable) {cables.Add(cable);}
	
	void Add(Wire *wire) {wires.Add(wire);}
	
	Vector<Cable*>&GetCables() {return cables;};
	
	Vector<Wire*>&GetWires() {return wires;};
	
	void SortRight(Connector* connector) {
		for (Cable *cable : cables) {
			cable->SortRight(connector);
		}
		int min, minIdx, cnt = wires.GetCount();
		Wire *w;
		for (int i=0; i<cnt; ++i) {
			w = wires[i];
			if (w->rightConnector == connector) {
				min = w->rightConnectorPin;
				for (int n=i+1; n<cnt; ++n) {
					if (w->rightConnector == wires[n]->rightConnector && wires[n]->rightConnectorPin < min) {
						min = wires[n]->rightConnectorPin;
						minIdx = n;
					}
				}
				if (min < w->rightConnectorPin) {
					wires[i] = wires[minIdx];
					wires[minIdx] = w;
				}
			}
		}
	}
	
	void SortLeft(Connector* connector, int &pinStart) {
		for (Cable *cable : cables) {
			cable->SortLeft(connector, pinStart);
		}
		
		for (Wire *wire : wires) {
			if (wire->leftConnector == connector && pinStart < connector->GetPinCount()) {
				int p=0;
				for (; p<pinStart; ++p) {
					if (connector->pins[p] == wire->leftConnectorPin) break;
				}
				if (p == pinStart) connector->pins.Set(pinStart++, wire->leftConnectorPin);
			}
		}
	}
	
	Rect& CalcCoverRect(Size &iSize) {
		Rect rect;
		coverRect.Clear();
		for (Cable* c : cables) {
			rect = c->CalcCoverRect(iSize);
			if (!rect.IsEmpty()) {
				if (coverRect.IsEmpty()) {
					coverRect = rect;
				} else {
					coverRect.Union(rect);
				}
			}
		}
		if (!coverRect.IsEmpty()) {
			coverRect.top -= 25;
			coverRect.Inflate(5, 5);
		}
		if (wires.GetCount()) {
			Point pos;
			int top = iSize.cy, bottom = 0;
			for (Wire* w : wires) {
				if (w->rightConnector != NULL) {
					pos = w->rightConnector->GetPinPosition(w->rightConnectorPin);
					if (pos.y < top) top = pos.y;
					if (pos.y > bottom) bottom = pos.y;
				}
			}
			int right = iSize.cx - iSize.cx / 6 - 30;
			int left = right - iSize.cx / 5;
			Rect wiresRect = {left, top - 10, right, bottom + 10};
			if (coverRect.IsEmpty()) {
				coverRect = wiresRect;
			} else {
				coverRect.Union(wiresRect);
			}
		}
		return coverRect;
	}
	
	Rect& GetCoverRect() {
		return coverRect;
	}
	
	void DrawCovers(ImageDraw& imgDraw, ImageDraw& objImg, Size &iSize) {
		objImg.DrawRect(coverRect, ViewerSelector::GetId(this));
		imgDraw.DrawPolygon({
			Point(coverRect.left, coverRect.top),
			Point(coverRect.right, coverRect.top),
			Point(coverRect.right, coverRect.bottom),
			Point(coverRect.left, coverRect.bottom),
		}, color, 1, DarkColor(color));
		imgDraw.DrawText(coverRect.left + 2, coverRect.top +  (cables.GetCount() ? 0 : 10), name, Arial(20), Black);
		for (Cable* c : cables) {
			c->DrawCovers(imgDraw, objImg, iSize);
		}
	}
	
	void Draw(ImageDraw& imgDraw, ImageDraw& objImg, int coverWidth) {
		for (Cable* c : cables) {
			c->Draw(imgDraw, objImg, coverWidth);
		}
		for (Wire* w : wires) {
			w->Draw(imgDraw, objImg, coverWidth);
		}
	}
	
	bool isCover() const {return cables.GetCount() > 0;};
	
	String ToString() const {
		bool first = true;
		String str = "Cable{";
		str << "name=\"" << name << "\", isCover=" << isCover() << ", cables=[";
		for (Cable* c : cables) {
			if (!first) {
				str << ",";
				first = false;
			}
			str << c->ToString();
		}
		str << "], wires=[";
		first = true;
		for (Wire* w : wires) {
			if (!first) {
				str << ",";
				first = false;
			}
			str << w->ToString();
		}
		str << "]}";
		return str;
	};
	
	virtual String GetTip() {
		return name;
	}
	
	Color GetColor() {
		return color;
	}
};

#endif
