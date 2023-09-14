#ifndef _CableTester_Viewer_h_
#define _CableTester_Viewer_h_

#include <CtrlLib/CtrlLib.h>
#include "Cable.h"

using namespace Upp;

class Viewer : public ParentCtrl {
private:
	Image img;
public:
	Viewer();
	virtual void Paint(Draw& w);
	void Show(Cable *cable);
};

#endif
