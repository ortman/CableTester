#ifndef _CableTester_Cabel_h_
#define _CableTester_Cabel_h_

#include "Wire.hpp"
#include <CtrlLib/CtrlLib.h>
using namespace Upp;

class Cable {
private:
	String name;
	Vector<Cable*> cables;
	Vector<Wire*> wires;
	
public:
	Cable(String name) : name(name) {}
	
	void Add(Cable *cable) {cables.Add(cable);}
	
	void Add(Wire *wire) {wires.Add(wire);}
	
	Vector<Cable*>&GetCables() {return cables;};
	
	Vector<Wire*>&GetWires() {return wires;};
	
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
	
	Vector<Point> DrawCovers(DrawingDraw& imgDraw) {
		Vector<Point> result, cablePoints;
		for (Cable* c : cables) {
			cablePoints = c->DrawCovers(imgDraw);
			if (result.GetCount() == 4) {
				if (cablePoints[0].y < result[0].y) {
					result[0] = cablePoints[0];
					result[1] = cablePoints[1];
				}
				if (cablePoints[2].y > result[2].y) {
					result[2] = cablePoints[2];
					result[3] = cablePoints[3];
				}
			} else if (cablePoints.GetCount() == 4) {
				result = {
					cablePoints[0],
					cablePoints[1],
					cablePoints[2],
					cablePoints[3]
				};
			}
		}
		if (wires.GetCount() > 0) {
			Point pos;
			Size sz = imgDraw.GetSize();
			int minYRight = sz.cy, maxYRight = 0;
			for (Wire* w : wires) {
				if (w->rightConnector != NULL) {
					pos = w->rightConnector->GetPinPosition(w->rightConnectorPin);
					if (pos.y < minYRight) minYRight = pos.y-5;
					if (pos.y > maxYRight) maxYRight = pos.y+5;
				}
			}
			Vector<Point> points = {
				Point(340, minYRight),
				Point(430, minYRight),
				Point(430, maxYRight),
				Point(340, maxYRight)
			};
			imgDraw.DrawPolygon(points, LtGray, 1, Gray);
			imgDraw.DrawText(points[0].x+2, points[0].y+7, name, Arial(10), Black);
			return points;
		} else if (result.GetCount() == 4) {
			result[0] = {result[0].x-2, result[0].y-15};
			result[1] = {result[1].x+2, result[1].y-15};
			result[2] = {result[2].x+2, result[2].y+2};
			result[3] = {result[3].x-2, result[3].y+2};
			imgDraw.DrawPolyline(result, 2, Gray);
			imgDraw.DrawLine(result[3], result[0], 2, Gray);
			imgDraw.DrawText(result[0].x+2, result[0].y, name, Arial(12), Black);
		}
		return result;
	}
	
	void Draw(DrawingDraw& imgDraw) {
		for (Cable* c : cables) {
			c->Draw(imgDraw);
		}
		for (Wire* w : wires) {
			w->Draw(imgDraw);
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
};

#endif
