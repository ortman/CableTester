#ifndef _VIEWER_SELECTOR_HPP_
#define _VIEWER_SELECTOR_HPP_

#include "CableNode.hpp"

class ViewerSelector {
private:
	static Color lastGenID;
	static VectorMap<Color, CableNode*> mapID;
	
	ViewerSelector() {}
	
public:
	static Color NextID() {
		return lastGenID = Color::FromRaw(lastGenID.GetRaw() + 1);
	}
	
	static void Add(Color id, CableNode* obj) {
		mapID.Add(id, obj);
	}
	
	static Color Add(CableNode* obj) {
		Color id = NextID();
		mapID.Add(id, obj);
		return id;
	}
	
	static CableNode* Get(Color id) {
		return mapID.Get(id, NULL);
	}
	
	static Color GetId(CableNode* obj) {
		Vector<CableNode*> &v = mapID.GetValues();
		int cnt = v.GetCount();
		for (int i=0; i<cnt; ++i) {
			if (obj == v[i]) {
				return mapID.GetKey(i);
			}
		}
		return Color::FromRaw(0);
	}
	
	static void Clear() {
		mapID.Clear();
	}
	
	static void Remove(Color id) {
		mapID.RemoveKey(id);
	}
	
};

Color ViewerSelector::lastGenID = Red; //Color::FromRaw(0);
VectorMap<Color, CableNode*> ViewerSelector::mapID;

#endif