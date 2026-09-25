#ifndef _MAIN_CABLE_HPP_
#define _MAIN_CABLE_HPP_

#include "Cable.hpp"

class MainCable : public Cable {
private:
	Vector<Connector*> connectors;
public:
	MainCable(WString name) : Cable(name, White) {}
	
	MainCable(const Cable &c) : Cable(c) {}
	
	~MainCable() {
		for (Connector *c : connectors) delete c;
	}
		
	void AddConnector(Connector* c) {
		connectors.Add(c);
	}
	
	Vector<Connector*>& GetConnectors() {
		return connectors;
	}
	
private:
	/* The layout of the cable blocks.
	   The pins of the connectors are ordered so that the wires of one cable
	   come to neighbour pins (see Sort). Then every wire goes straight from the
	   blocks to its right pin, the blocks stand one under another without
	   overlapping, and the wires do not cross on the left. */
	
	static constexpr int NO_KEY = INT_MAX;
	
	// Place of the wire in the order of the right pins (connectors from the top)
	int TrackKey(Wire* w) {
		Connector* right = w->GetRightConnector();
		if (right && right->IsRight()) {
			int index = 0;
			for (Connector* c : connectors) {
				if (c == right) break;
				if (c->IsRight()) ++index;
			}
			return index * 1000 + right->GetPinPlace(w->GetRightConnectorPin());
		}
		if (w->GoesThroughCover()) return NO_KEY - 1;   // ends inside the cable: at the bottom
		return NO_KEY;
	}
	
	// Average key of the own wires of the cable, NO_KEY when none goes to the right
	double OwnWiresKey(Cable* cable) {
		double sum = 0;
		int count = 0;
		for (Wire* w : cable->GetWires()) {
			int key = TrackKey(w);
			if (key < NO_KEY - 1) {
				sum += key;
				++count;
			}
		}
		return count ? sum / count : (double)NO_KEY;
	}
	
	// Average key of the own wires and of the sub-cables of the cable
	double OrderKeyOf(Cable* cable) {
		double sum = 0;
		int count = 0;
		double own = OwnWiresKey(cable);
		if (own != NO_KEY) {
			sum += own;
			++count;
		}
		for (Cable* c : cable->GetCables()) {
			double key = OrderKeyOf(c);
			if (key != NO_KEY) {
				sum += key;
				++count;
			}
		}
		return count ? sum / count : (double)NO_KEY;
	}
	
	// Sorts the wires and the sub-cables of the cable by the right pins
	void OrderTracks(Cable* cable) {
		StableSort(cable->GetWires(), [&](Wire* a, Wire* b) {return TrackKey(a) < TrackKey(b);});
		Vector<Cable*>& cables = cable->GetCables();
		VectorMap<Cable*, double> keys;
		for (Cable* c : cables) {
			OrderTracks(c);
			keys.Add(c, OrderKeyOf(c));
		}
		StableSort(cables, [&](Cable* a, Cable* b) {return keys.Get(a) < keys.Get(b);});
	}
	
	// The wires in the order the cable should have them: the wires of one cable
	// together, the cables by their right pins. OrderTracks() must be called
	void CollectTracks(Cable* cable, Vector<Wire*>& order) {
		auto OwnWires = [&] {
			for (Wire* w : cable->GetWires()) {
				if (w->GoesThroughCover()) order.Add(w);
			}
		};
		double ownKey = OwnWiresKey(cable);
		bool ownDone = false;
		for (Cable* c : cable->GetCables()) {
			if (!ownDone && ownKey <= OrderKeyOf(c)) {
				OwnWires();
				ownDone = true;
			}
			CollectTracks(c, order);
		}
		if (!ownDone) OwnWires();
	}
	
	// The block of the cable around its wires and sub-cables.
	// Returns it, an empty rect when the cable has no wires at all
	Rect PlaceBlocks(Cable* cable, bool isRoot, int xLeft, int xRight) {
		int half = (int)round(Cable::pinHeight * 0.4);   // a wire takes a row of the pin
		int label = Cable::textFont.GetHeight() + 4;
		Rect content(0, 0, 0, 0);
		bool has = false;
		auto Add = [&](const Rect& r) {
			content = has ? (content | r) : r;
			has = true;
		};
		for (Wire* w : cable->GetWires()) {
			if (w->GetTrackY() == INT_MIN) continue;
			Add(Rect(xLeft, w->GetTrackY() - half, xRight, w->GetTrackY() + half));
		}
		Vector<Cable*> empty;
		for (Cable* c : cable->GetCables()) {
			Rect r = PlaceBlocks(c, false, xLeft, xRight);
			if (r.IsEmpty()) {
				empty.Add(c);
			} else {
				Add(r);
			}
		}
		/* a cable without wires still has a block to select it: under the others */
		int top = has ? content.bottom + half : Cable::pinHeight;
		for (Cable* c : empty) {
			Rect r(xLeft, top, xRight, top + Cable::pinHeight);
			c->GetCableRect() = r;
			Add(r);
			top = r.bottom + half;
		}
		if (!isRoot) {
			if (has && cable->GetCables().GetCount()) {
				content.top -= label;                    // the row of the name above the sub-cables
				content.Inflate(5, 0);
			}
			cable->GetCableRect() = has ? content : Rect(0, 0, 0, 0);
		}
		return has ? content : Rect(0, 0, 0, 0);
	}
	
	// The wires to the right pins go at the height of their pin, the wires that
	// end inside the cable at the height of their left pin. The connectors must be placed
	void LayoutTracks(const Size& size) {
		Vector<Wire*> wires;
		CollectWires(this, wires);
		for (Wire* w : wires) {
			int y = INT_MIN;
			if (w->GoesThroughCover()) {
				y = w->GetRightConnector()
				    ? w->GetRightConnector()->GetPinPosition(w->GetRightConnectorPin()).y
				    : w->GetLeftConnector()->GetPinPosition(w->GetLeftConnectorPin()).y;
			}
			w->SetTrackY(y);
		}
		PlaceBlocks(this, true, Wire::CoverLeft(size), Wire::CoverRight(size));
	}
	
	// Orders the pins of the connector by the value of their wires, the pins
	// without it go after them in their order
	static void SortPins(Connector* c, const Vector<int>& value) {
		Vector<int> pins;
		for (int pin = 1; pin <= c->GetPinCount(); ++pin) pins.Add(pin);
		StableSort(pins, [&](int a, int b) {return value[a] < value[b];});
		for (int i = 0; i < pins.GetCount(); ++i) c->pins[i] = pins[i];
	}

public:
	// Orders the pins of the connectors: the wires of one cable come to
	// neighbour pins on the right, and the wires do not cross on the left
	void Sort() {
		/* 1. the order of the wires is found by the natural order of the right
		      pins: the cables that come to the upper pins go higher */
		for (Connector* c : connectors) {
			if (c->IsRight()) {
				for (int i = 0; i < c->GetPinCount(); ++i) c->pins[i] = i + 1;
			}
		}
		OrderTracks(this);
		Vector<Wire*> order;
		CollectTracks(this, order);
	
		/* 2. the pins of the right connectors go in this order */
		for (Connector* c : connectors) {
			if (!c->IsRight()) continue;
			Vector<int> first;
			first.SetCount(c->GetPinCount() + 1, INT_MAX);
			for (int i = 0; i < order.GetCount(); ++i) {
				Wire* w = order[i];
				int pin = w->GetRightConnectorPin();
				if (w->GetRightConnector() == c && pin >= 1 && pin <= c->GetPinCount()) {
					first[pin] = min(first[pin], i);
				}
			}
			SortPins(c, first);
		}
	
		/* 3. the pins of the left connectors go by the height of their wires on
		      the right, so the wires do not cross */
		Size size(960, 1520);
		CalculateConnectorsPosition(size);
		for (Connector* c : connectors) {
			if (!c->IsLeft()) continue;
			Vector<int> top;
			top.SetCount(c->GetPinCount() + 1, INT_MAX);
			for (Wire* w : order) {
				int pin = w->GetLeftConnectorPin();
				if (w->GetLeftConnector() != c || !w->GetRightConnector() || pin < 1 || pin > c->GetPinCount()) continue;
				int y = w->GetRightConnector()->GetPinPosition(w->GetRightConnectorPin()).y;
				top[pin] = min(top[pin], y);
			}
			SortPins(c, top);
		}
	}
	
	static void CollectWires(Cable* cable, Vector<Wire*>& wires) {
		for (Wire* w : cable->GetWires()) wires.Add(w);
		for (Cable* c : cable->GetCables()) CollectWires(c, wires);
	}
	
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
		LayoutTracks(size);
	}
	
	virtual void Draw(ImageDraw& imgDraw, ImageDraw* objImg, Size &iSize) {
		for (Cable* c : GetCables()) {
			c->DrawCable(imgDraw, objImg, iSize);
		}
		Cable::Draw(imgDraw, objImg, iSize);
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
	
	static constexpr const char* FILE_MAGIC = "CTBL";

	static MainCable* FromData(Stream& in, int version) {
		MainCableCT_t data;
		GetStreamThrow(in, &data.connectorCount, sizeof(data.connectorCount));
		Array<Connector> connectorsOwner;
		Vector<Connector*> connectors;
		int32_t count = data.connectorCount;
		while (count) {
			connectors.Add(&connectorsOwner.Add(Connector::FromData(in, version)));
			--count;
		}
		One<Cable> c = Cable::FromData(connectors, in, version);
		MainCable* mc = new MainCable(*c);
		while (connectorsOwner.GetCount()) {
			mc->AddConnector(connectorsOwner.Detach(0));
		}
		return mc;
	}

	// Loads the .cbl file with the "CTBL" header
	static MainCable* FromData(const String& fileData) {
		if (!fileData.StartsWith(FILE_MAGIC)) {
			throw FileError(t_("Unknown file format"));
		}
		StringStream in(fileData);
		in.SeekCur(4);
		uint16_t version;
		GetStreamThrow(in, &version, sizeof(version));
		if (version != FORMAT_CURRENT) {
			throw FileError(Format(t_("Unsupported file version %d"), version));
		}
		return FromData(in, version);
	}

	virtual void ToData(Stream& out) {
		out.Put(FILE_MAGIC, 4);
		uint16_t version = FORMAT_CURRENT;
		out.Put(&version, sizeof(version));
		MainCableCT_t data;
		data.connectorCount = connectors.GetCount();
		out.Put(&data.connectorCount, sizeof(data.connectorCount));
		uint32_t connectorId = 0;
		for (Connector* cn : connectors) {
			cn->SetId(++connectorId);
			cn->ToData(out);
		}
		Cable::ToData(out);
	}
};

#endif