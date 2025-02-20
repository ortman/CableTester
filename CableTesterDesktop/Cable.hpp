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
	Rect cableRect;
	Color color;
	
public:
	static int pinHeight;
	static Font textFont;
	
	Cable(String name, Color color) : name(name), color(color) {}
	
	Cable(const Cable& c) {
		color = c.color;
		name = c.name;
		for (Cable* cc : c.cables) {
			cables.Add(new Cable(*cc));
		}
		for (Wire* w : c.wires) {
			wires.Add(new Wire(*w));
		}
	}
	
	~Cable() {
		for (Cable *c : cables) delete c;
		for (Wire *w : wires) delete w;
	}
	
	void Add(Cable *cable) {cables.Add(cable);}
	
	void Add(Wire *wire) {wires.Add(wire);}
	
	Vector<Cable*>& GetCables() {return cables;};
	
	Vector<Wire*>& GetWires() {return wires;};
	
	Cable* GetWireCable(const Wire* wire) {
		Cable* res = NULL;
		for (Wire* w : wires) {
			if (w == wire) return this;
		}
		for (Cable* c : cables) {
			res = c->GetWireCable(wire);
			if (res) return res;
		}
		return res;
	}
	
	Cable* GetParentCable(const Cable* cable) {
		Cable* res = NULL;
		for (Cable* c : cables) {
			if (c == cable) return this;
			res = c->GetParentCable(cable);
			if (res) return res;
		}
		return res;
	}
	
	void SortRight(Connector* connector) {
		for (Cable *cable : cables) {
			cable->SortRight(connector);
		}
		int min, minIdx, cnt = wires.GetCount();
		Wire *w;
		for (int i=0; i<cnt; ++i) {
			w = wires[i];
			if (w->GetRightConnector() == connector) {
				min = w->GetRightConnectorPin();
				for (int n=i+1; n<cnt; ++n) {
					if (w->GetRightConnector() == wires[n]->GetRightConnector() && wires[n]->GetRightConnectorPin() < min) {
						min = wires[n]->GetRightConnectorPin();
						minIdx = n;
					}
				}
				if (min < w->GetRightConnectorPin()) {
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
			if (wire->GetLeftConnector() == connector && pinStart < connector->GetPinCount()) {
				int p=0;
				for (; p<pinStart; ++p) {
					if (connector->pins[p] == wire->GetLeftConnectorPin()) break;
				}
				if (p == pinStart) connector->pins.Set(pinStart++, wire->GetLeftConnectorPin());
			}
		}
	}
	
	Rect& CalcCableRect(const Size &iSize) {
		Rect rect;
		int right = iSize.cx - iSize.cx / 6 - 30;
		int left = right - iSize.cx / 5;
		int top = 0;
		cableRect.Clear();
		for (Cable* c : cables) {
			rect = c->CalcCableRect(iSize);
			if (!rect.IsEmpty()) {
				if (rect.bottom > top) top = rect.bottom + pinHeight / 6;
				if (cableRect.IsEmpty()) {
					cableRect = rect;
				} else {
					cableRect.Union(rect);
				}
			}
		}
		for (Cable* c : cables) {
			Rect& r = c->GetCableRect();
			if (r.IsEmpty()) {
				r = {left, top, right, top + pinHeight};
				top += pinHeight / 6 + pinHeight;
				cableRect.Union(r);
			}
		}
		if (!cableRect.IsEmpty()) {
			cableRect.top -= max(20, pinHeight / 2);
			cableRect.Inflate(5, 5);
		}
		if (wires.GetCount()) {
			Point pos;
			top = iSize.cy;
			int top = iSize.cy, bottom = 0;
			for (Wire* w : wires) {
				if (w->GetRightConnector() != NULL) {
					pos = w->GetRightConnector()->GetPinPosition(w->GetRightConnectorPin());
					if (pos.y < top) top = pos.y;
					if (pos.y > bottom) bottom = pos.y;
				}
			}
			Rect wiresRect = {left, top - pinHeight / 6, right, bottom + pinHeight / 6};
			if (cableRect.IsEmpty()) {
				cableRect = wiresRect;
			} else {
				cableRect.Union(wiresRect);
			}
		}
		return cableRect;
	}
	
	Rect& GetCableRect() {
		return cableRect;
	}
	
	void DrawCable(ImageDraw& imgDraw, ImageDraw* objImg, const Size &iSize) {
		if (objImg) objImg->DrawRect(cableRect, ViewerSelector::GetId(this));
		imgDraw.DrawPolygon({
			Point(cableRect.left, cableRect.top),
			Point(cableRect.right, cableRect.top),
			Point(cableRect.right, cableRect.bottom),
			Point(cableRect.left, cableRect.bottom),
		}, color, 1, DarkColor(color));
		imgDraw.DrawText(cableRect.left + 4, cableRect.top +
				(cables.GetCount() ? 0 : (int)round((pinHeight - textFont.GetHeight() * 0.95) / 2.)),
				name, textFont, IsDark(color) ? White : Black);
		for (Cable* c : cables) {
			c->DrawCable(imgDraw, objImg, iSize);
		}
	}
	
	virtual void Draw(ImageDraw& imgDraw, ImageDraw* objImg, const Size& imgSize) {
		for (Cable* c : cables) {
			c->Draw(imgDraw, objImg, imgSize);
		}
		for (Wire* w : wires) {
			w->Draw(imgDraw, imgSize);
			if (objImg) w->Draw(*objImg, imgSize, Wire::pen * 2, ViewerSelector::GetId(w));
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
	
	const String& GetName() {
		return name;
	}
	
	void SetName(const String& str) {
		name = str;
	}
	
	const Color& GetColor() {
		return color;
	}
	
	void SetColor(const Color& c) {
		color = c;
	}
	
	void RemoveWire(Wire* w, bool recursive) {
		int cnt = wires.GetCount();
		for (int i = 0; i < cnt; ++i) {
			if (wires[i] == w) {
				wires.Remove(i);
				break;
			}
		}
		if (recursive) {
			for (Cable* c : cables) {
				c->RemoveWire(w, recursive);
			}
		}
	}
	
	void RemoveWires(Connector *cr) {
		for (int i = wires.GetCount() - 1; i >= 0; --i) {
			if (wires[i]->GetLeftConnector() == cr || wires[i]->GetRightConnector() == cr) {
				wires.Remove(i);
			}
		}
		for (Cable* c : cables) {
			c->RemoveWires(cr);
		}
	}
	
	void RemoveCable(Cable* c, bool removeCable, bool removeWires) {
		int cnt = cables.GetCount();
		for (int i = 0; i < cnt; ++i) {
			cables[i]->RemoveCable(c, removeCable, removeWires);
			if (removeCable && cables[i] == c) {
				cables.Remove(i);
				break;
			}
		}
		if (removeWires && this == c) {
			for (Wire* w : wires) delete w;
			wires.Clear();
		}
	}
	
	static Cable* FromData(Vector<Connector *>& connectors, Stream& in) {
		CableCT_t data;
		in.Get(&data.color, sizeof(data.color));
		in.Get(&data.name, sizeof(data.name));
		in.Get(&data.wiresCount, sizeof(data.wiresCount));
		Cable* c = new Cable(data.name, Color::FromRaw(data.color));
		int32_t count = data.wiresCount;
		while (count) {
			c->Add(Wire::FromData(connectors, in));
			--count;
		}
		in.Get(&data.cablesCount, sizeof(data.cablesCount));
		count = data.cablesCount;
		while (count) {
			c->Add(Cable::FromData(connectors, in));
			--count;
		}
		return c;
	}
	
	virtual void ToData(Stream& out) {
		CableCT_t data;
		data.color = color.GetRaw();
		strcpy_s(data.name, sizeof(data.name), name);
		data.wiresCount = wires.GetCount();
		data.cablesCount = cables.GetCount();
		
		out.Put(&data.color, sizeof(data.color));
		out.Put(data.name, sizeof(data.name));
		out.Put(data.wiresCount, sizeof(data.wiresCount));
		for (Wire* w : wires) {
			w->ToData(out);
		}
		out.Put(data.cablesCount, sizeof(data.cablesCount));
		for (Cable* c : cables) {
			c->ToData(out);
		}
	}
};

int Cable::pinHeight = 10;
Font Cable::textFont = Arial(20);

#endif
