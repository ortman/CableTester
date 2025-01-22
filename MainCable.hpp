#ifndef _MAIN_CABLE_HPP_
#define _MAIN_CABLE_HPP_

#include "Cable.hpp"

class MainCable {
private:
	VectorMap<int, Connector*> connectors;
	Cable* cable;
public:
	MainCable(String name) {
	}
	
	void SetCable(Cable* c) {cable = c;}
	
	void AddConnector(int id, Connector* c) {connectors.Add(id, c);}
	
	void ClearConnectors() {connectors.Clear();};
	
	Connector* GetConnector(int id) {
		if (connectors.Find(id) < 0) return NULL;
		return connectors.Get(id);
	}
	
	void SortLeft() {
		for (Connector *c : connectors) {
			if (c->IsLeft()) {
				int pinStart = 0;
				cable->SortLeft(c, pinStart);
			}
		}
	};
	
	void CalculateConnectorsPosition(Size size) {
		int32_t topLeft, leftAllSize = 0;
		int32_t topRight, rightAllSize = 0;
		for (Connector* c : connectors) {
			if (c->IsLeft()) {
				leftAllSize += c->GetHeight() + 10;
				c->SetX(10);
			} else {
				c->SetX(440);
				rightAllSize += c->GetHeight() + 10;
			}
		}
		if (leftAllSize > 0) leftAllSize -= 10;
		if (rightAllSize > 0) rightAllSize -= 10;
		if (leftAllSize > rightAllSize) {
			topLeft  = 10;
			topRight = (leftAllSize - rightAllSize)/2 + 10;
		} else {
			topLeft  = (rightAllSize - leftAllSize)/2 + 10;
			topRight = 10;
		}
		for (Connector* c : connectors) {
			if (c->IsLeft()) {
				c->SetY(topLeft);
				topLeft += c->GetHeight() + 10;
			} else {
				c->SetY(topRight);
				topRight += c->GetHeight() + 10;
			}
		}
	}
	
	void Draw(DrawingDraw& imgDraw) {
		for (Connector* c : connectors) {
			c->Draw(imgDraw);
		}
		for (Cable* c : cable->GetCables()) {
			c->DrawCovers(imgDraw);
		}
		cable->Draw(imgDraw);
	}
};

#endif