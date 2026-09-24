#ifndef _TESTER_PACKAGE_HPP_
#define _TESTER_PACKAGE_HPP_

#include "MainCable.hpp"
#include "../Common/ct_package.h"

#include <plugin/jpg/jpg.h>

using namespace Upp;

// Converts the cable schema into the tester package (see Common/ct_package.h)
class TesterPackage {
public:
	struct Issue : Moveable<Issue> {
		bool isError;
		String text;
		CableNode* node;
	};

	static constexpr int IMAGE_CX = 480;
	static constexpr int IMAGE_CY = 760;

	static void CollectWires(Cable* cable, Vector<Wire*>& wires) {
		for (Wire* w : cable->GetWires()) wires.Add(w);
		for (Cable* c : cable->GetCables()) CollectWires(c, wires);
	}

	static String ConnectorName(Connector* cn) {
		String name = ToUtf8(cn->GetName());
		name.Replace("\n", " ");
		return TrimBoth(name);
	}

	static String PinName(Connector* cn, int pin) {
		return ConnectorName(cn) + ":" + IntStr(pin);
	}

	static bool IsPinOnWire(const Vector<Wire*>& wires, Connector* cn, int pin) {
		for (Wire* w : wires) {
			if (w->GetLeftConnector() == cn && w->GetLeftConnectorPin() == pin) return true;
			if (w->GetRightConnector() == cn && w->GetRightConnectorPin() == pin) return true;
		}
		return false;
	}

	static Vector<Issue> Validate(MainCable& cable) {
		Vector<Issue> issues;
		auto Add = [&](bool isError, const String& text, CableNode* node) {
			Issue& is = issues.Add();
			is.isError = isError;
			is.text = text;
			is.node = node;
		};
		Vector<Wire*> wires;
		CollectWires(&cable, wires);

		if (cable.GetConnectors().GetCount() == 0) {
			Add(true, t_("The cable has no connectors"), NULL);
		}
		if (wires.GetCount() > CT_PKG_MAX_WIRES) {
			Add(true, Format(t_("Too many wires: %d (max %d)"), wires.GetCount(), CT_PKG_MAX_WIRES), NULL);
		}

		VectorMap<int, String> used; // slot pin -> "Connector:pin"
		for (Connector* cn : cable.GetConnectors()) {
			for (int pin = 1; pin <= cn->GetPinCount(); ++pin) {
				int tp = cn->GetTesterPin(pin);
				String pinName = PinName(cn, pin);
				if (tp == 0) {
					if (IsPinOnWire(wires, cn, pin)) {
						Add(true, Format(t_("%s: slot pin is not assigned"), pinName), cn);
					} else {
						Add(false, Format(t_("%s: slot pin is not assigned, the pin will not be tested"), pinName), cn);
					}
					continue;
				}
				if (tp < 1 || tp > CT_PKG_PIN_COUNT) {
					Add(true, Format(t_("%s: slot pin %d is out of range 1..%d"), pinName, tp, CT_PKG_PIN_COUNT), cn);
					continue;
				}
				int idx = used.Find(tp);
				if (idx >= 0) {
					Add(true, Format(t_("%s: slot pin %d is already used by %s"), pinName, tp, used[idx]), cn);
				} else {
					used.Add(tp, pinName);
				}
				if (cn->IsLeft() && tp > CT_PKG_LEFT_PIN_MAX) {
					Add(false, Format(t_("%s: slot pin %d of the left connector, expected 1..%d"), pinName, tp, CT_PKG_LEFT_PIN_MAX), cn);
				} else if (cn->IsRight() && tp <= CT_PKG_LEFT_PIN_MAX) {
					Add(false, Format(t_("%s: slot pin %d of the right connector, expected %d..%d"), pinName, tp, CT_PKG_LEFT_PIN_MAX + 1, CT_PKG_PIN_COUNT), cn);
				}
			}
		}

		for (Wire* w : wires) {
			Connector* l = w->GetLeftConnector();
			Connector* r = w->GetRightConnector();
			if ((l && w->GetLeftConnectorPin() > l->GetPinCount()) ||
			    (r && w->GetRightConnectorPin() > r->GetPinCount())) {
				Add(true, t_("The wire is connected to a pin that does not exist"), w);
				continue;
			}
			if (l && r && l == r && w->GetLeftConnectorPin() == w->GetRightConnectorPin()) {
				Add(false, Format(t_("%s: the wire is connected to the same pin"), PinName(l, w->GetLeftConnectorPin())), w);
			}
		}
		return issues;
	}

	static bool HasErrors(const Vector<Issue>& issues) {
		for (const Issue& is : issues) if (is.isError) return true;
		return false;
	}

	static bool HasAssignedPins(MainCable& cable) {
		for (Connector* cn : cable.GetConnectors()) {
			for (int pin = 1; pin <= cn->GetPinCount(); ++pin) {
				if (cn->GetTesterPin(pin)) return true;
			}
		}
		return false;
	}

	// Assigns slot pins in the order of connectors: left 1..30, right 31..60.
	// Returns false when there are not enough slot pins.
	static bool AutoAssign(MainCable& cable) {
		int next[2] = {1, CT_PKG_LEFT_PIN_MAX + 1};
		int last[2] = {CT_PKG_LEFT_PIN_MAX, CT_PKG_PIN_COUNT};
		bool ok = true;
		for (Connector* cn : cable.GetConnectors()) {
			int side = cn->IsLeft() ? 0 : 1;
			for (int pin = 1; pin <= cn->GetPinCount(); ++pin) {
				if (next[side] <= last[side]) {
					cn->SetTesterPin(pin, next[side]++);
				} else {
					cn->SetTesterPin(pin, 0);
					ok = false;
				}
			}
		}
		return ok;
	}

	// Draws the cable for the tester screen. Connector positions stay calculated
	// for the doubled size, so the pin points must be divided by 2.
	// Colors are fixed (light theme) and do not depend on the desktop theme.
	// The screen is rotated 90 degrees, so the images are drawn rotated.
	static Image RenderImage(MainCable& cable) {
		Color borderColor = Connector::borderColor;
		Color textColor = Connector::textColor;
		Connector::borderColor = Green;
		Connector::textColor = Blue;

		Size screenSize = {IMAGE_CY, IMAGE_CX};
		Size imageSize = {screenSize.cy * 2, screenSize.cx * 2};
		ImageDraw img(imageSize);
		img.DrawRect(imageSize, Color(240, 240, 240));
		cable.CalculateConnectorsPosition(imageSize);
		cable.Draw(img, NULL, imageSize);
		ImageDraw screenImg(screenSize);
		screenImg.DrawImage(screenSize, RotateClockwise(img));
		Connector::borderColor = borderColor;
		Connector::textColor = textColor;
		return screenImg;
	}

	static void CopyUtf8(char* dst, int size, const String& src) {
		// Cut on the UTF-8 character boundary
		int len = min(src.GetLength(), size - 1);
		while (len > 0 && len < src.GetLength() && (src[len] & 0xC0) == 0x80) --len;
		memset(dst, 0, size);
		memcpy(dst, ~src, len);
	}

	static int FindRoot(Vector<int>& parent, int i) {
		while (parent[i] != i) i = parent[i] = parent[parent[i]];
		return i;
	}

	// Builds the package. RenderImage() must be called before to place connectors.
	static String Build(MainCable& cable, const String& name) {
		Vector<Wire*> allWires;
		CollectWires(&cable, allWires);

		CtPkgPin pins[CT_PKG_PIN_COUNT];
		memset(pins, 0, sizeof(pins));
		for (int i = 0; i < CT_PKG_PIN_COUNT; ++i) {
			CopyUtf8(pins[i].label, CT_PKG_LABEL_SIZE, Format(t_("Pin %d"), i + 1));
		}
		for (Connector* cn : cable.GetConnectors()) {
			String cnName = ConnectorName(cn);
			for (int pin = 1; pin <= cn->GetPinCount(); ++pin) {
				int tp = cn->GetTesterPin(pin);
				if (tp < 1 || tp > CT_PKG_PIN_COUNT) continue;
				CtPkgPin& p = pins[tp - 1];
				Point pos = cn->GetPinPosition(pin);
				p.flags = CT_PKG_PIN_USED | (cn->IsLeft() ? CT_PKG_PIN_LEFT : 0);
				p.x = (uint16_t)clamp(pos.x / 2, 0, IMAGE_CX - 1);
				p.y = (uint16_t)clamp(pos.y / 2, 0, IMAGE_CY - 1);
				String pinText = ":" + IntStr(pin);
				char nameBuf[CT_PKG_LABEL_SIZE];
				CopyUtf8(nameBuf, CT_PKG_LABEL_SIZE - pinText.GetLength(), cnName);
				CopyUtf8(p.label, CT_PKG_LABEL_SIZE, String(nameBuf) + pinText);
			}
		}

		// Wires between two assigned slot pins, nets by union-find
		Vector<CtPkgWire> wires;
		Vector<int> parent;
		for (int i = 0; i <= CT_PKG_PIN_COUNT; ++i) parent.Add(i);
		for (Wire* w : allWires) {
			if (!w->GetLeftConnector() || !w->GetRightConnector()) continue;
			int a = w->GetLeftConnector()->GetTesterPin(w->GetLeftConnectorPin());
			int b = w->GetRightConnector()->GetTesterPin(w->GetRightConnectorPin());
			if (a < 1 || b < 1 || a > CT_PKG_PIN_COUNT || b > CT_PKG_PIN_COUNT || a == b) continue;
			if (wires.GetCount() >= CT_PKG_MAX_WIRES) break;
			CtPkgWire& cw = wires.Add();
			cw.pinA = (uint8_t)a;
			cw.pinB = (uint8_t)b;
			parent[FindRoot(parent, a)] = FindRoot(parent, b);
		}
		Vector<int> groupSize;
		groupSize.SetCount(CT_PKG_PIN_COUNT + 1, 0);
		for (int i = 1; i <= CT_PKG_PIN_COUNT; ++i) groupSize[FindRoot(parent, i)]++;
		VectorMap<int, int> netOfRoot;
		for (int i = 1; i <= CT_PKG_PIN_COUNT; ++i) {
			int root = FindRoot(parent, i);
			if (groupSize[root] < 2) continue;
			int idx = netOfRoot.Find(root);
			if (idx < 0) {
				idx = netOfRoot.GetCount();
				netOfRoot.Add(root, idx + 1);
			}
			pins[i - 1].net = (uint8_t)netOfRoot[idx];
		}

		CtPkgHeader header;
		memset(&header, 0, sizeof(header));
		memcpy(header.magic, CT_PKG_MAGIC, 4);
		header.version = CT_PKG_VERSION;
		header.headerSize = sizeof(CtPkgHeader);
		header.totalSize = sizeof(CtPkgHeader) + sizeof(pins) + wires.GetCount() * sizeof(CtPkgWire);
		CopyUtf8(header.name, CT_PKG_NAME_SIZE, name);
		header.imageWidth = IMAGE_CX;
		header.imageHeight = IMAGE_CY;
		header.pinCount = CT_PKG_PIN_COUNT;
		header.wireCount = (uint8_t)wires.GetCount();
		header.netCount = (uint8_t)netOfRoot.GetCount();

		StringBuffer data;
		data.Cat((const char*)&header, sizeof(header));
		data.Cat((const char*)pins, sizeof(pins));
		if (wires.GetCount()) data.Cat((const char*)wires.begin(), wires.GetCount() * sizeof(CtPkgWire));
		uint32_t crc = CRC32(~data, data.GetLength());
		memcpy(~data + offsetof(CtPkgHeader, crc32), &crc, sizeof(crc));
		return String(data);
	}

	static bool SaveJpeg(const String& fileName, const Image& img) {
		JPGEncoder jpg(90);
		return jpg.SaveFile(fileName, img);
	}
};

#endif
