#ifndef _MAIN_CABLE_HPP_
#define _MAIN_CABLE_HPP_

#include "Cable.hpp"

class MainCable : public Cable {
private:
	VectorMap<int, Connector*> connectors;
public:
	MainCable(String name, Color color) : Cable(name, color) {}
	
	~MainCable() {
		for (Connector *c : connectors) delete c;
	}
	
	void AddConnector(int id, Connector* c) {connectors.Add(id, c);}
	
	int AddConnector(Connector* c) {
		int id = 1;
		for (int i : connectors.GetKeys()) {
			if (i >= id) id = i + 1;
		}
		connectors.Add(id, c);
		return id;
	}
	
	void ClearConnectors() {connectors.Clear();};
	
	Connector* GetConnector(int id) {
		if (connectors.Find(id) < 0) return NULL;
		return connectors.Get(id);
	}
	
	void Sort() {
		for (Connector *c : connectors) {
			if (c->IsRight()) SortRight(c);
		}
		for (Connector *c : connectors) {
			if (c->IsLeft()) {
				int pinStart = 0;
				SortLeft(c, pinStart);
				if (pinStart < c->GetPinCount()) {
					int j;
					for (int p = 1; p <= c->GetPinCount(); ++p) {
						for (j = 0; j < pinStart; ++j) {
							if (c->pins[j] == p) break;
						}
						if (j == pinStart) {
							c->pins[pinStart++] = p;
						}
					}
				}
			}
		}
	};
	
	void CalculateConnectorsPosition(Size size) {
		int32_t topLeft = 0;
		int32_t topRight = 0;
		int pinWidth = size.cx / 6;
		int leftPinCount = 1;
		int rightPinCount = 1;
		for (Connector* c : connectors) {
			c->PinSize().cx = pinWidth;
			if (c->IsLeft()) {
				c->Position().x = 10;
				leftPinCount += c->GetPinCount() + 2;
			} else {
				c->Position().x = size.cx - pinWidth - 10;
				rightPinCount += c->GetPinCount() + 2;
			}
		}
		int pinHeight = size.cy / max(leftPinCount, rightPinCount);
		if (leftPinCount > rightPinCount) {
			topLeft  = pinHeight;
			topRight = (leftPinCount - rightPinCount) * pinHeight / 2 + pinHeight;
		} else {
			topLeft  = (rightPinCount - leftPinCount) * pinHeight / 2 + pinHeight;
			topRight = pinHeight;
		}
		for (Connector* c : connectors) {
			c->PinSize().cy = pinHeight;
			if (c->IsLeft()) {
				c->Position().y = topLeft;
				topLeft += c->GetHeight() + pinHeight;
			} else {
				c->Position().y = topRight;
				topRight += c->GetHeight() + pinHeight;
			}
		}
		Connector::textFont.Height(min(pinHeight * 2 / 3, pinWidth / 4));
		Cable::textFont.Height(max(20, min(pinWidth / 5, pinHeight * 2 / 5)));
		Cable::pinHeight = pinHeight;
		Wire::pen = pinHeight / 6;
	}
	
	virtual void Draw(ImageDraw& imgDraw, ImageDraw* objImg, Size &iSize) {
		for (Cable* c : GetCables()) {
			c->CalcCableRect(iSize);
			c->DrawCable(imgDraw, objImg, iSize);
		}
		Cable::Draw(imgDraw, objImg, iSize.cx / 5);
		for (Connector* c : connectors) {
			c->Draw(imgDraw, objImg, iSize);
		}
	}
		
	void RemoveConnector(Connector* c, bool removeAll) {
		RemoveWires(c);
		if (removeAll) {
			int cnt = connectors.GetCount();
			for (int i = 0; i < cnt; ++i) {
				if (connectors[i] == c) {
					connectors.Remove(i);
					break;
				}
			}
		}
	}
};

#endif