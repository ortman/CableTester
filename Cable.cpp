#include "Cable.h"

//////////////////////////////////////////////////////////////
Wire::Wire(Color color, Connector *leftConnector, int leftConnectorPin,
			Connector *rightConnector, int rightConnectorPin) :
			color(color), leftConnector(leftConnector), leftConnectorPin(leftConnectorPin),
			rightConnector(rightConnector), rightConnectorPin(rightConnectorPin) {
}

Wire::Wire(Wire &w) {
	color = w.color;
	leftConnector = w.leftConnector;
	leftConnectorPin = w.leftConnectorPin;
	rightConnector = w.rightConnector;
	rightConnectorPin = w.rightConnectorPin;
}

Wire::Wire(int32_t hexColor, Connector *leftConnector, int leftConnectorPin,
			Connector *rightConnector, int rightConnectorPin) :
			leftConnector(leftConnector), leftConnectorPin(leftConnectorPin),
			rightConnector(rightConnector), rightConnectorPin(rightConnectorPin) {
	color = Color::Special((hexColor & 0x0000ff) << 16 | (hexColor & 0x00ff00) | (hexColor & 0xff0000) >> 16);
}

int getPt( int n1 , int n2 , float perc )
{
    int diff = n2 - n1;
    return n1 + ( diff * perc );
}

void Wire::DrawBezier(ImageDraw& imgDraw, int32_t x1, int32_t y1, int32_t x4, int32_t y2, Color color, int32_t width) {
	int xa,ya,xb,yb,xc,yc,xm,ym,xn,yn,x,y;
	int x23 = (x4+x1)/2;
	int lastX, lastY;
	for( float i = 0 ; i < 1.001 ; i += 0.05) {
		// The Green Lines
	    xa = getPt( x1 , x23, i );
	    ya = getPt( y1 , y1 , i );
	    xb = getPt( x23, x23, i );
	    yb = getPt( y1 , y2 , i );
	    xc = getPt( x23, x4, i );
	    yc = getPt( y2 , y2 , i );
	
	    // The Blue Line
	    xm = getPt( xa , xb , i );
	    ym = getPt( ya , yb , i );
	    xn = getPt( xb , xc , i );
	    yn = getPt( yb , yc , i );
	
	    // The Black Dot
	    x = getPt( xm , xn , i );
	    y = getPt( ym , yn , i );
	
		if (i>0) {
			imgDraw.DrawLine(lastX,lastY, x,y, width, color);
		}
	    //w.DrawPixel( x , y , color );
		lastX = x;
		lastY = y;
	}
}

void Wire::Draw(ImageDraw& imgDraw) {
	if (leftConnector && rightConnector) {
		Point left = leftConnector->GetPinPosition(leftConnectorPin);
		Point right = rightConnector->GetPinPosition(rightConnectorPin);
		DrawBezier(imgDraw,left.x, left.y, right.x, right.y, color, 4);
	}
}

//////////////////////////////////////////////////////////////
Connector::Connector(const char *name, int32_t pinCount, int32_t x, int32_t y, bool isLeft)
		:pinCount(pinCount), x(x), y(y), isLeft(isLeft), name(name) {
}

Connector::Connector(const char *name, int32_t pinCount, bool isLeft)
		:pinCount(pinCount), x(0), y(0), isLeft(isLeft), name(name) {
}

Connector::Connector(Connector&& c) {
	name = c.name;
	pinCount = c.pinCount;
	x = c.x;
	y = c.y;
	isLeft = c.isLeft;
}

void Connector::operator=(Connector&& c) {
	name = c.name;
	pinCount = c.pinCount;
	x = c.x;
	y = c.y;
	isLeft = c.isLeft;
}

void Connector::Draw(ImageDraw& imgDraw) {
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
			imgDraw.DrawLine(x+widthRect, yPin, x+50, yPin, 2, Green);
		} else {
			imgDraw.DrawLine(x, yPin, xRect, yPin, 2, Green);
		}
		imgDraw.DrawTextA(x+(isLeft ? 25 : 15), yPin-7, AsString(i+1), Arial(10), Blue);
	}
	FontInfo fi = Arial(10).Info();
	int nameCnt = (heightRect-20) / fi.GetAveWidth();
	if (name.GetLength() < nameCnt) {
		nameCnt = name.GetLength();
	}
	imgDraw.DrawTextA(x+(isLeft ? 15 : 50),y+5,-900,name,Arial(10),Blue,nameCnt,NULL);
}

int32_t Connector::GetHeight() {
	return pinCount*15 + 15 - 1;;
}

Point Connector::GetPinPosition(int32_t pin) {
	if (isLeft) {
		return {x + 50, y + 15*pin};
	} else {
		return {x, y + 15*pin};
	}
}

//////////////////////////////////////////////////////////////
Cable::Cable(String name) :
		name(name) {
}

Cable::Cable(Cable &c) {
	name = c.name;
}

void Cable::Add(Cable *cable) {
	cables.Add(cable);
}

void Cable::Add(Wire *wire) {
	wires.Add(wire);
}

void Cable::Sort() {
}


void Cable::GetAllLeftConnectors(Vector<Connector*>& connectors) {
	bool isExists;
	for (Wire* w : wires) {
		if (w->leftConnector) {
			isExists = false;
			for (Connector *c : connectors) {
				if (c == w->leftConnector) {
					isExists = true;
					break;
				}
			}
			if (!isExists) connectors.Add(w->leftConnector);
		}
	}
	for (Cable* c : cables) {
		c->GetAllLeftConnectors(connectors);
	}
}

void Cable::GetAllRightConnectors(Vector<Connector*>& connectors) {
	bool isExists;
	for (Wire* w : wires) {
		if (w->rightConnector) {
			isExists = false;
			for (Connector *c : connectors) {
				if (c == w->rightConnector) {
					isExists = true;
					break;
				}
			}
			if (!isExists) connectors.Add(w->rightConnector);
		}
	}
	for (Cable* c : cables) {
		c->GetAllRightConnectors(connectors);
	}
}

void Cable::CalculateConnectorsPosition(Size size) {
	Vector<Connector*> leftConnectors, rightConnectors;
	GetAllLeftConnectors(leftConnectors);
	GetAllRightConnectors(rightConnectors);
	
	int32_t topLeft, leftAllSize = 0;
	int32_t topRight, rightAllSize = 0;
	for (Connector* lc : leftConnectors) {
		leftAllSize += lc->GetHeight() + 10;
		lc->SetX(10);
	}
	if (leftConnectors.GetCount() > 0) leftAllSize -= 10;
	for (Connector* rc : rightConnectors) {
		rightAllSize += rc->GetHeight() + 10;
		rc->SetX(440);
	}
	if (rightConnectors.GetCount() > 0) rightAllSize -= 10;
	if (leftAllSize > rightAllSize) {
		topLeft  = 10;
		topRight = (leftAllSize - rightAllSize)/2 + 10;
	} else {
		topLeft  = (rightAllSize - leftAllSize)/2 + 10;
		topRight = 10;
	}
	for (Connector* lc : leftConnectors) {
		lc->SetY(topLeft);
		topLeft += lc->GetHeight() + 10;
	}
	for (Connector* rc : rightConnectors) {
		rc->SetY(topRight);
		topRight += rc->GetHeight() + 10;
	}
}

void Cable::DrawWires(ImageDraw& imgDraw) {
	for (Cable* c : cables) {
		c->DrawWires(imgDraw);
	}
	for (Wire* w : wires) {
		w->Draw(imgDraw);
	}
}

void Cable::Draw(ImageDraw& imgDraw) {
  Vector<Connector*> leftConnectors, rightConnectors;
  GetAllLeftConnectors(leftConnectors);
  GetAllRightConnectors(rightConnectors);
	for (Connector* c : leftConnectors) {
		c->Draw(imgDraw);
	}
	for (Connector* c : rightConnectors) {
		c->Draw(imgDraw);
	}
	DrawWires(imgDraw);
}
