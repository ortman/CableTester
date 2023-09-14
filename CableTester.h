#ifndef _CableTester_CableTester_h
#define _CableTester_CableTester_h

#include <CtrlLib/CtrlLib.h>
#include "Viewer.h"

using namespace Upp;

#define LAYOUTFILE <CableTester/CableTester.lay>
#include <CtrlCore/lay.h>

class CableTester : public WithCableTesterLayout<TopWindow> {
private:
	Viewer viewer;
	ColumnList list;
	void LoadFile(String fileName);
public:
	CableTester();
};

#endif
