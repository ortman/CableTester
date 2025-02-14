#ifndef _WIRE_HPP_
#define _WIRE_HPP_

#include "Connector.hpp"

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

class Wire : public CableNode {
	Color color;
	Connector *leftConnector;
	int leftConnectorPin;
	Connector *rightConnector;
	int rightConnectorPin;
	
private:
	int getPt( int n1 , int n2 , float perc ) {
	  int diff = n2 - n1;
	  return n1 + (int)round(diff * perc);
	}
	
	template<typename TDraw>
	void DrawBezier(TDraw& draw, int32_t x1, int32_t y1,
									int32_t x2, int32_t y2,
									int32_t x3, int32_t y3,
									int32_t x4, int32_t y4,
									Color color, int32_t width) {
		int lastX, lastY;
		int xa, ya, xb, yb, xc, yc, xm, ym, xn, yn, x, y;
		for (float i = 0.f ; i < 1.001f ; i += 0.02f) {
	    // The Green Lines
	    xa = getPt( x1 , x2 , i );
	    ya = getPt( y1 , y2 , i );
	    xb = getPt( x2 , x3 , i );
	    yb = getPt( y2 , y3 , i );
	    xc = getPt( x3 , x4 , i );
	    yc = getPt( y3 , y4 , i );
	
	    // The Blue Line
	    xm = getPt( xa , xb , i );
	    ym = getPt( ya , yb , i );
	    xn = getPt( xb , xc , i );
	    yn = getPt( yb , yc , i );
	
	    // The Black Dot
	    x = getPt( xm , xn , i );
	    y = getPt( ym , yn , i );
	
			if (i > 0) {
				draw.DrawLine(lastX,lastY, x,y, width, color);
			}
			lastX = x;
			lastY = y;
		}
	}
	
	template<typename TDraw>
	void DrawBezierLR(TDraw& draw, int32_t x1, int32_t y1, int32_t x2, int32_t y2, Color color, int32_t width) {
		int centerX = (x1 + x2) / 2;
		DrawBezier(draw, x1, y1, centerX, y1, centerX, y2, x2, y2, color, width);
	}
	
	template<typename TDraw>
	void DrawBezierLL(TDraw& draw, int32_t x1, int32_t y1, int32_t x2, int32_t y2, Color color, int32_t width) {
		int centerX = max(x1, x2) + (int)round(abs(y1 - y2) * 0.4);
		DrawBezier(draw, x1, y1, centerX, y1, centerX, y2, x2, y2, color, width);
	}
	
	template<typename TDraw>
	void DrawBezierRR(TDraw& draw, int32_t x1, int32_t y1, int32_t x2, int32_t y2, Color color, int32_t width) {
		int centerX = min(x1, x2) - (int)round(abs(y1 - y2) * 0.4);
		DrawBezier(draw, x1, y1, centerX, y1, centerX, y2, x2, y2, color, width);
	}
	
public:
	static int pen;
	
	Wire(Color color, Connector *leftConnector = NULL, int leftConnectorPin = 0,
			Connector *rightConnector = NULL, int rightConnectorPin = 0) :
				color(color), leftConnector(leftConnector), leftConnectorPin(leftConnectorPin),
				rightConnector(rightConnector), rightConnectorPin(rightConnectorPin) {
	}
	
	Wire(int32_t hexColor, Connector *leftConnector = NULL, int leftConnectorPin = 0,
			Connector *rightConnector = NULL, int rightConnectorPin = 0) :
				leftConnector(leftConnector), leftConnectorPin(leftConnectorPin),
				rightConnector(rightConnector), rightConnectorPin(rightConnectorPin) {
		color = Color::FromRaw((hexColor & 0x0000ff) << 16 | (hexColor & 0x00ff00) | (hexColor & 0xff0000) >> 16);
	}
			
	Wire(Wire &w) {
		color = w.color;
		leftConnector = w.leftConnector;
		leftConnectorPin = w.leftConnectorPin;
		rightConnector = w.rightConnector;
		rightConnectorPin = w.rightConnectorPin;
	}
	
	int GetLeftConnectorPin() {return leftConnectorPin;}
	
	int GetRightConnectorPin() {return rightConnectorPin;}
	
	Connector* GetLeftConnector() {return leftConnector;}
	
	void SetLeftConnector(Connector* c, int pin) {
		leftConnector = c;
		leftConnectorPin = pin;
	}
	
	Connector* GetRightConnector() {return rightConnector;}
	
	void SetRightConnector(Connector* c, int pin) {
		rightConnector = c;
		rightConnectorPin = pin;
	}

	void Draw(Draw& w, Sizef scale, Point p, int coverStartX) {
		int penScale = (int)round((double)pen / scale.cx);
		if (leftConnector) {
			Point left = leftConnector->GetPinPosition(leftConnectorPin);
			left.x = (int)round((double)left.x / scale.cx);
			left.y = (int)round((double)left.y / scale.cy);
			if (p.x < left.x + abs(p.y - left.y) * 0.4) {
				DrawBezierLL(w, left.x, left.y, p.x, p.y, color, penScale);
			} else {
				DrawBezierLR(w, left.x, left.y, min(coverStartX, p.x), p.y, color, penScale);
				if (p.x > coverStartX) {
					w.DrawLine(coverStartX, p.y, p.x, p.y, penScale, color);
				}
			}
		} else if (rightConnector) {
			Point right = rightConnector->GetPinPosition(rightConnectorPin);
			right.x = (int)round((double)right.x / scale.cx);
			right.y = (int)round((double)right.y / scale.cy);
			w.DrawLine(coverStartX, right.y, right.x, right.y, penScale, color);
			if (p.x < coverStartX - abs(p.y - right.y) * 0.4) {
				DrawBezierLR(w, p.x, p.y, coverStartX, right.y, color, penScale);
			} else if (p.x > coverStartX) {
				w.DrawLine(coverStartX, p.y, p.x, p.y, penScale, color);
				DrawBezierRR(w, coverStartX, p.y, coverStartX, right.y, color, penScale);
			} else {
				DrawBezierRR(w, p.x, p.y, coverStartX, right.y, color, penScale);
			}
		}
	}
	
	void Draw(ImageDraw& imgDraw, int coverWidth, int pen, const Color& color) {
		if (leftConnector && rightConnector) {
			Point left = leftConnector->GetPinPosition(leftConnectorPin);
			Point right = rightConnector->GetPinPosition(rightConnectorPin);
			if (rightConnector->IsRight()) {	// ? - r
				imgDraw.DrawLine(right.x - coverWidth, right.y, right.x, right.y, pen, color);
			}
			if (leftConnector->IsRight()) { // r - r
				imgDraw.DrawLine(left.x - coverWidth, left.y, left.x, left.y, pen, color);
				DrawBezierRR(imgDraw, left.x - coverWidth, left.y, right.x - coverWidth, right.y, color, pen);
			} else if (rightConnector->IsLeft()) { // l - l
				DrawBezierLL(imgDraw, left.x, left.y, right.x, right.y, color, pen);
			} else { // l - r
				DrawBezierLR(imgDraw, left.x, left.y, right.x - coverWidth, right.y, color, pen);
			}
		}
	}
	
	void Draw(ImageDraw& imgDraw, int coverWidth) {
		Draw(imgDraw, coverWidth, pen, color);
	}
	
	String ToString() const {
		String str = "Wire{";
		str << leftConnector << "-" << rightConnector << ":" << leftConnectorPin << "-" << rightConnectorPin << "#" << color << "}";
		return str;
	};
	
	virtual String GetTip() {
		return ColorToHtml(color);
	}
	
	void SetColor(const Color& c) {
		color = c;
	}
	
	Color& GetColor() {return color;}
};

int Wire::pen = 4;

#endif