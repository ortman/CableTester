#ifndef _CableTester_Cabel_h_
#define _CableTester_Cabel_h_

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
	Connector(const char *name, int32_t pinCount, int32_t x, int32_t y, bool isLeft);
	Connector(const char *name, int32_t pinCount, bool isLeft);
	Connector(Connector&& c);
	void operator=(Connector&& c);
	int32_t GetHeight();
	void Draw(ImageDraw& imgDraw);
	int32_t GetX() {return x;};
	int32_t GetY() {return y;};
	void SetX(int32_t x) {this->x = x;};
	void SetY(int32_t y) {this->y = y;};
	bool IsLeft() {return isLeft;};
	Point GetPinPosition(int32_t pin);
};

class Wire {
	friend class Cable;
	Color color;
	Connector *leftConnector;
	int leftConnectorPin;
	Connector *rightConnector;
	int rightConnectorPin;
private:
	void DrawBezier(ImageDraw& imgDraw, int32_t x1, int32_t y1, int32_t x2, int32_t y2, Color color, int32_t width=1);
public:
	Wire(Color color, Connector *leftConnector = NULL, int leftConnectorPin = 0,
			Connector *rightConnector = NULL, int rightConnectorPin = 0);
	Wire(int32_t hexColor, Connector *leftConnector = NULL, int leftConnectorPin = 0,
			Connector *rightConnector = NULL, int rightConnectorPin = 0);
	Wire(Wire &w);
	void Draw(ImageDraw& imgDraw);
};

class Cable {
	String name;
	Vector<Cable*> cables;
	Vector<Wire*> wires;
private:
	void GetAllLeftConnectors(Vector<Connector*>& connectors);
	void GetAllRightConnectors(Vector<Connector*>& connectors);
public:
	Cable(String name);
	Cable(Cable &c);
	void Add(Cable *cable);
	void Add(Wire *wire);
	Vector<Cable*>&GetCables() {return cables;};
	Vector<Wire*>&GetWires() {return wires;};
	void Sort();
	void CalculateConnectorsPosition(Size size);
	void DrawWires(ImageDraw& imgDraw);
	void Draw(ImageDraw& imgDraw);
};

#endif
