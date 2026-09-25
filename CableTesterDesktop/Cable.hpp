#ifndef _CABLE_HPP_
#define _CABLE_HPP_

#include "Wire.hpp"
#include "CableNode.hpp"
#include <CtrlLib/CtrlLib.h>
using namespace Upp;

class Cable : public CableNode {
private:
	WString name;
	Vector<Cable*> cables;
	Vector<Wire*> wires;
	Rect cableRect;
	Color color;
	
public:
	static int pinHeight;
	static Font textFont;
	
	Cable(WString name, Color color) : name(name), color(color) {}
	
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
		// the name of a cable with sub-cables takes the row at the top of its block,
		// the name of a cable of wires goes between its first and second wire
		// (see MainCable::PlaceBlocks)
		int textY = cables.GetCount() ? cableRect.top + 2 : cableRect.top + pinHeight * 55 / 100;
		imgDraw.DrawText(cableRect.left + 4, textY, name, textFont, IsDark(color) ? White : Black);
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
		return name.ToString();
	}
	
	const WString& GetName() {
		return name;
	}
	
	void SetName(const WString& str) {
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
	
	static Cable* FromData(Vector<Connector *>& connectors, Stream& in, int version) {
		CableCT_t data = {0};
		GetStreamThrow(in, &data.color, sizeof(data.color));
		WString cableName = ReadName(in);
		GetStreamThrow(in, &data.wiresCount, sizeof(data.wiresCount));
		One<Cable> c = new Cable(cableName, Color::FromRaw(data.color));
		int32_t count = data.wiresCount;
		while (count) {
			c->Add(Wire::FromData(connectors, in));
			--count;
		}
		GetStreamThrow(in, &data.cablesCount, sizeof(data.cablesCount));
		count = data.cablesCount;
		while (count) {
			c->Add(Cable::FromData(connectors, in, version));
			--count;
		}
		return c.Detach();
	}

	virtual void ToData(Stream& out) {
		CableCT_t data = {0};
		data.color = color.GetRaw();
		data.wiresCount = wires.GetCount();
		data.cablesCount = cables.GetCount();

		out.Put(&data.color, sizeof(data.color));
		WriteName(out, name);
		out.Put(&data.wiresCount, sizeof(data.wiresCount));
		for (Wire* w : wires) {
			w->ToData(out);
		}
		out.Put(&data.cablesCount, sizeof(data.cablesCount));
		for (Cable* c : cables) {
			c->ToData(out);
		}
	}
};

int Cable::pinHeight = 10;
Font Cable::textFont = Arial(20);

#endif
