#include "GGAbstractCtrl.h"
GGAbstractCtrl::GGAbstractCtrl(GGAbstractModel* mdl) : model(mdl) {}
GGAbstractCtrl::~GGAbstractCtrl() {
	delete model;
}
GGAbstractModel* GGAbstractCtrl::GetModel() {
	return model;
}
void GGAbstractCtrl::LeftClickDown(sf::Vector2f clickPos) {}