#ifndef __GGABSTRACTCTRL_H
#define __GGABSTRACTCTRL_H

#include "GGAbstractModel.h"

class GGAbstractCtrl {
public:
	GGAbstractCtrl(GGAbstractModel* mdl);
	virtual ~GGAbstractCtrl();
	GGAbstractModel* GetModel();
	virtual void LeftClickDown(sf::Vector2f clickPos);

private:
	GGAbstractModel* model;
};

#endif
