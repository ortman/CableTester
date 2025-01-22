#ifndef _CONNECTOR_HPP_
#define _CONNECTOR_HPP_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

class Connector {
private:
	int32_t pinCount;
	int32_t x;
	int32_t y;
	bool isLeft;
	String name;
public:
	Vector<int> pins;
	
	Connector(const char *name, int32_t pinCount, int32_t x, int32_t y, bool isLeft)
			:pinCount(pinCount), x(x), y(y), isLeft(isLeft), name(name), pins(pinCount) {
		for (int i=0; i<pinCount; ++i) {
			pins[i] = i+1;
		}
	}
	
	Connector(const char *name, int32_t pinCount, bool isLeft)
			:pinCount(pinCount), x(0), y(0), isLeft(isLeft), name(name), pins(pinCount) {
		for (int i=0; i<pinCount; ++i) {
			pins[i] = i+1;
		}
	}
	
	Connector(Connector&& c) : pins(c.pinCount) {
		name = c.name;
		pinCount = c.pinCount;
		x = c.x;
		y = c.y;
		isLeft = c.isLeft;
		for (int i=0; i<pinCount; ++i) {
			pins[i] = c.pins[i];
		}
	}
	
	void operator=(Connector&& c) {
		name = c.name;
		pinCount = c.pinCount;
		x = c.x;
		y = c.y;
		isLeft = c.isLeft;
	}
	
	int32_t GetHeight() {
		return pinCount*15 + 15 - 1;
	}
	
	void Draw(DrawingDraw& imgDraw) {
		int32_t heightRect = GetHeight();
		int32_t widthRect = 50 - 11;
		int32_t yRect = y, xRect = (isLeft ? 1 : 10) + x;
		Point rect[] = {
			{xRect, yRect}, {xRect + widthRect, yRect}, {xRect+widthRect, yRect + heightRect}, {xRect, yRect + heightRect}, {xRect, yRect}
		};
		String s;
		imgDraw.DrawPolyline(rect, 5, 2, Green);
		int32_t yPin;
		for (int i=0; i<pinCount; ++i) {
			yPin = y + 15 + i*15;
			if (isLeft) {
				imgDraw.DrawLine(x+widthRect+1, yPin, x+50, yPin, 2, Green);
			} else {
				imgDraw.DrawLine(x, yPin, xRect, yPin, 2, Green);
			}
			imgDraw.DrawTextA(x+(isLeft ? 25 : 15), yPin-7, AsString(pins[i]), Arial(10), Blue);
		}
		FontInfo fi = Arial(10).Info();
		int maxCnt = (heightRect-20) / fi.GetAveWidth();
		int nameSize, textX = x+(isLeft ? 15 : 45);
		Vector<String> names = Split(name, "\\n");
		for (String name : names) {
			nameSize = name.GetLength();
			if (nameSize > maxCnt) {
				nameSize = maxCnt;
			}
			imgDraw.DrawTextA(textX,y+5,-900,name,Arial(10),Blue,nameSize,NULL);
			textX -= fi.GetHeight();
		}
	}
	
	int32_t GetX() {return x;};
	
	void SetX(int32_t x) {this->x = x;};
	
	int32_t GetY() {return y;};
	
	void SetY(int32_t y) {this->y = y;};
	
	bool IsLeft() {return isLeft;};
	
	Point GetPinPosition(int32_t pin) {
		int pinPos = 0;
		for (int i = 0; i < pinCount; ++i) {
			if (pins[i] == pin) {
				pinPos = i+1;
				break;
			}
		}
		if (isLeft) {
			return {x + 50, y + 15*pinPos};
		} else {
			return {x, y + 15*pinPos};
		}
	}
	
	String ToString() const {
		String str = "Connector{pinCount:";
		str << pinCount << ", isLeft=" << isLeft << ", x=" << x << ", y=" << y << ", name=\"" << name << "\"}";
		return str;
	};
	
	int GetPinCount() {return pinCount;};
};

#endif