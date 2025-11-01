#ifndef _CONNECTOR_HPP_
#define _CONNECTOR_HPP_

#include "ViewerSelector.hpp"
#include "CableNode.hpp"

#include "DataCT.h"
#include <CtrlLib/CtrlLib.h>
using namespace Upp;

class Connector : public CableNode {
private:
	int32_t pinCount;
	Point position;
	Size pinSize = {50, 15};
	bool isLeft;
	String name;
	uint32_t id;
	uint8_t *testerPins;

public:
	static Color borderColor;
	static Color textColor;
	static int borderWidth;
	
	Vector<int> pins;
	static Font textFont;
	
	Connector(const String &name, int32_t pinCount, Point& position, bool isLeft)
			:pinCount(pinCount), position(position), isLeft(isLeft), name(name), pins(pinCount) {
		for (int i = 0; i < pinCount; ++i) {
			pins[i] = i+1;
		}
		id = GetNextId();
		testerPins = (uint8_t*) malloc(pinCount * sizeof(uint8_t));
	}
	
	Connector(const String &name, int32_t pinCount, bool isLeft)
			:pinCount(pinCount), position(0, 0), isLeft(isLeft), name(name), pins(pinCount) {
		for (int i = 0; i < pinCount; ++i) {
			pins[i] = i+1;
		}
		id = GetNextId();
		testerPins = (uint8_t*) malloc(pinCount * sizeof(uint8_t));
	}
	
	Connector(const Connector&& c) : pins(c.pinCount) {
		id = c.id;
		name = c.name;
		pinCount = c.pinCount;
		position = c.position;
		isLeft = c.isLeft;
		for (int i=0; i<pinCount; ++i) {
			pins[i] = c.pins[i];
		}
		testerPins = (uint8_t*) malloc(pinCount * sizeof(uint8_t));
		memcpy(testerPins, c.testerPins, pinCount * sizeof(uint8_t));
	}
	
	void operator=(const Connector&& c) {
		id = c.id;
		name = c.name;
		pinCount = c.pinCount;
		position = c.position;
		isLeft = c.isLeft;
		pins.SetCount(c.pins.GetCount());
		for (int i=0; i<pinCount; ++i) {
			pins[i] = c.pins[i];
		}
	}
	
	inline uint32_t GetId() {
		return id;
	}
	
	inline void SetId(const uint32_t& id) {
		this->id = id;
	}
	
	int32_t GetHeight() {
		return pinCount * pinSize.cy + pinSize.cy - 1;
	}
	
	void Draw(ImageDraw& imgDraw, ImageDraw* objImg, Size &iSize) {
		int32_t heightRect = GetHeight();
		int32_t widthRect = pinSize.cx - pinSize.cy / 3;
		int32_t yRect = position.y, xRect = (isLeft ? 0 : pinSize.cy / 4) + position.x;
		Point rect[] = {
			{xRect, yRect},
			{xRect + widthRect, yRect},
			{xRect+widthRect, yRect + heightRect},
			{xRect, yRect + heightRect},
			{xRect, yRect}
		};
		String pinText;
		imgDraw.DrawPolyline(rect, 5, borderWidth, borderColor);
		Color id = ViewerSelector::GetId(this);
		if (objImg) objImg->DrawPolygon(rect, 5, id);
		int32_t yPin;
		FontInfo fi = textFont.Info();
		int pinXL, pinXR;
		for (int i = 0; i < pinCount; ++i) {
			yPin = position.y + pinSize.cy + i * pinSize.cy;
			pinText = IntStr(pins[i]);
			if (isLeft) {
				pinXL = position.x + widthRect + 1;
				pinXR = position.x + pinSize.cx;
				imgDraw.DrawText(position.x + widthRect - GetTextSize(pinText, textFont).cx - 10, yPin - fi.GetHeight() / 2, pinText, textFont, textColor);
			} else {
				pinXL = position.x;
				pinXR = xRect;
				imgDraw.DrawText(position.x + pinSize.cy / 4 + 10, yPin - fi.GetHeight() / 2, pinText, textFont, textColor);
			}
			imgDraw.DrawLine(pinXL, yPin, pinXR, yPin, borderWidth, borderColor);
			if (objImg) objImg->DrawRect(pinXL, yPin - pinSize.cy/4, pinXR - pinXL, pinSize.cy/2, Color::FromRaw(id.GetRaw() + ((pins[i]) << 16)));
		}
		int maxCnt = (heightRect - 20) / fi.GetAveWidth();
		int nameSize, textX;
		if (isLeft) {
			textX = position.x + widthRect - fi.GetHeight() - (int)round(fi.GetWidth('0') * ((pinCount < 10) ? 1.3 : ((pinCount < 100) ? 2.6 : 3.9)));
		} else {
			textX = position.x + pinSize.cx - 5;
		}
		Vector<String> names = Split(name, '\n');
		for (String name : names) {
			nameSize = name.GetLength();
			if (nameSize > maxCnt) {
				nameSize = maxCnt;
				name = name.Left(nameSize);
			}
			imgDraw.DrawText(textX, position.y + 5, -900, name, textFont, textColor);
			textX += (int)(fi.GetHeight() / (isLeft ? 1. : -1.));
		}
	}
	
	Point& Position() {
		return position;
	}
	
	Size& PinSize() {
		return pinSize;
	}
		
	bool IsLeft() {
		return isLeft;
	}
	
	bool IsRight() {
		return !isLeft;
	}
	
	void SetIsLeft(bool isLeft) {
		this->isLeft = isLeft;
	}
	
	Point GetPinPosition(int32_t pin) {
		int pinPos = 0;
		for (int i = 0; i < pinCount; ++i) {
			if (pins[i] == pin) {
				pinPos = i + 1;
				break;
			}
		}
		if (isLeft) {
			return {position.x + pinSize.cx, position.y + pinSize.cy * pinPos};
		} else {
			return {position.x, position.y + pinSize.cy * pinPos};
		}
	}
	
	String ToString() const {
		String str = "Connector{pinCount:";
		str << pinCount << ", isLeft=" << isLeft << ", x=" << position.x << ", y=" << position.y << ", name=\"" << name << "\"}";
		return str;
	}
	
	int GetPinCount() {return pinCount;}
	
	void SetPinCount(int count) {
		if (pinCount == count) return;
		pinCount = count;
		pins.SetCount(pinCount);
		for (int i = 0; i < pinCount; ++i) {
			pins[i] = i+1;
		}
	}
	
	virtual String GetTip() {
		return name;
	}
	
	const String& GetName() {
		return name;
	}
	
	void SetName(const String& str) {
		name = str;
	}
	
	static Connector* FromData(Stream& in) {
		ConnectorCT_t data;
		in.Get(&data.id, sizeof(data.id));
		in.Get(&data.pinCount, sizeof(data.pinCount));
		in.Get(data.name, sizeof(data.name));
		in.Get(&data.isLeft, sizeof(data.isLeft));
		in.Get(&data.color, sizeof(data.color));
		
		Connector* cn = new Connector(data.name, data.pinCount, (bool)data.isLeft);
		cn->SetId(data.id);
		
		in.Get(cn->testerPins, data.pinCount * sizeof(uint8_t));
		return cn;
	}
	
	virtual void ToData(Stream& out) {
		ConnectorCT_t data;
		data.id = id;
		data.pinCount = pinCount;
		strcpy_s(data.name, sizeof(data.name), name);
		data.isLeft = isLeft;
		data.color = White().GetRaw(); //reserved
		
		out.Put(&data.id, sizeof(data.id));
		out.Put(&data.pinCount, sizeof(data.pinCount));
		out.Put(data.name, sizeof(data.name));
		out.Put(&data.isLeft, sizeof(data.isLeft));
		out.Put(&data.color, sizeof(data.color));
		out.Put(testerPins, pinCount * sizeof(uint8_t));
	}
	
	static uint32_t GetNextId() {
		static uint32_t nextId = 0;
		return ++nextId;
	}
};

int Connector::borderWidth = 2;
Color Connector::borderColor = Green;
Color Connector::textColor = Blue;
Font Connector::textFont = Arial(10);

#endif