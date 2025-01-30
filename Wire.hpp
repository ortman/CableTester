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
	
	void DrawBezier(Draw& draw, int32_t x1, int32_t y1, int32_t x4, int32_t y2, Color color, int32_t width=1) {
		int xa,ya,xb,yb,xc,yc,xm,ym,xn,yn,x,y;
		int x23 = (x4+x1)/2;
		int lastX, lastY;
		for (float i = 0.f ; i < 1.001f ; i += 0.02f) {
	    xa = getPt( x1 , x23, i );
	    ya = getPt( y1 , y1 , i );
	    xb = getPt( x23, x23, i );
	    yb = getPt( y1 , y2 , i );
	    xc = getPt( x23, x4 , i );
	    yc = getPt( y2 , y2 , i );
	
	    xm = getPt( xa , xb , i );
	    ym = getPt( ya , yb , i );
	    xn = getPt( xb , xc , i );
	    yn = getPt( yb , yc , i );
	
	    x = getPt( xm , xn , i );
	    y = getPt( ym , yn , i );
			if (i>0) {
				draw.DrawLine(lastX,lastY, x,y, width, color);
			}
			lastX = x;
			lastY = y;
		}
	}
	
	void DrawBezier(ImageDraw& imgDraw, int32_t x1, int32_t y1, int32_t x4, int32_t y2, Color color, int32_t width=1) {
		int xa,ya,xb,yb,xc,yc,xm,ym,xn,yn,x,y;
		int x23 = (x4+x1)/2;
		int lastX, lastY;
		for (float i = 0.f ; i < 1.001f ; i += 0.02f) {
	    xa = getPt( x1 , x23, i );
	    ya = getPt( y1 , y1 , i );
	    xb = getPt( x23, x23, i );
	    yb = getPt( y1 , y2 , i );
	    xc = getPt( x23, x4 , i );
	    yc = getPt( y2 , y2 , i );
	
	    xm = getPt( xa , xb , i );
	    ym = getPt( ya , yb , i );
	    xn = getPt( xb , xc , i );
	    yn = getPt( yb , yc , i );
	
	    x = getPt( xm , xn , i );
	    y = getPt( ym , yn , i );
			if (i>0) {
				imgDraw.DrawLine(lastX,lastY, x,y, width, color);
			}
			lastX = x;
			lastY = y;
		}
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
		color = Color::Special((hexColor & 0x0000ff) << 16 | (hexColor & 0x00ff00) | (hexColor & 0xff0000) >> 16);
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
			DrawBezier(w, (int)round((double)left.x / scale.cx), (int)round((double)left.y / scale.cy), min(coverStartX, p.x), p.y, color, penScale);
			if (p.x > coverStartX) {
				w.DrawLine(coverStartX, p.y, p.x, p.y, penScale, color);
			}
		} else if (rightConnector) {
			Point right = rightConnector->GetPinPosition(rightConnectorPin);
			int yRight = (int)round((double)right.y / scale.cy);
			w.DrawLine(max(coverStartX, p.x), yRight, (int)round((double)right.x / scale.cx), yRight, penScale, color);
			if (p.x < coverStartX) {
				DrawBezier(w, p.x, p.y, coverStartX, yRight, color, penScale);
			}
		}
	}
	
	void Draw(ImageDraw& imgDraw, int coverWidth, int pen, const Color& color) {
		if (leftConnector && rightConnector) {
			Point left = leftConnector->GetPinPosition(leftConnectorPin);
			Point right = rightConnector->GetPinPosition(rightConnectorPin);
			DrawBezier(imgDraw, left.x, left.y, right.x - coverWidth, right.y, color, pen);
			imgDraw.DrawLine(right.x - coverWidth, right.y, right.x, right.y, pen, color);
		}
	}
	
	void Draw(ImageDraw& imgDraw, ImageDraw* objImg, int coverWidth) {
		if (leftConnector && rightConnector) {
			Draw(imgDraw, coverWidth, pen, color);
			if (objImg) {
				Point left = leftConnector->GetPinPosition(leftConnectorPin);
				Point right = rightConnector->GetPinPosition(rightConnectorPin);
				Color id = ViewerSelector::GetId(this);
				DrawBezier(*objImg, left.x, left.y, right.x - coverWidth, right.y, id, pen * 2);
				objImg->DrawLine(right.x - coverWidth, right.y, right.x, right.y, pen * 2, id);
			}
		}
	}
	
	String ToString() const {
		String str = "Wire{";
		str << leftConnector << "-" << rightConnector << ":" << leftConnectorPin << "-" << rightConnectorPin << "#" << color << "}";
		return str;
	};
	
	virtual String GetTip() {
		return ColorToHtml(color);
	}
	
	Color& GetColor() {return color;}
};

int Wire::pen = 4;

#endif