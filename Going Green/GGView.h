#ifndef __GGVIEW_H
#define __GGVIEW_H

#include "GGSubject.h"
#include "GGAbstractCtrl.h"
#include "GGAbstractModel.h"

class GGView : GGSubject {
public:
	GGView(GGAbstractCtrl* controller);
	virtual ~GGView();
	virtual bool Show(); /* unique controls and models for each game/stage - control creates the model */

private:
	GGAbstractCtrl* ctrl;
	GGAbstractModel* model; // model has components that the view draws
};

#endif