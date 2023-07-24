#include "GGAbstractCtrl.h"
#define PI 3.14159265359f
#define DELAY 15
#define DEBUG 0
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif
GGAbstractCtrl::GGAbstractCtrl() {}
GGAbstractCtrl::~GGAbstractCtrl() {
}
void GGAbstractCtrl::ResetMdl() {
	GetModel()->ResetData();
}
bool GGAbstractCtrl::TimerTick() {
	GetModel()->GetTimer()->TickMS();
	return GetModel()->GetTimer()->TimerCompleted();
}
GGPumpCtrl::GGPumpCtrl() {

}
GGPumpCtrl::~GGPumpCtrl() {}
GGAbstractModel* GGPumpCtrl::GetModel() {
	return &pumpMdl;
}
void GGPumpCtrl::AnimatePump() {
	pumpMdl.GetPump()->NextAnimation();
	if (pumpMdl.GetPump()->AnimationCompleted()) {
		pumpMdl.SetNumPumps(pumpMdl.GetNumPumps() - 1);
	}
}

void GGPumpCtrl::PumpClicked() {
	pumpMdl.SetNumPumps(pumpMdl.GetNumPumps() + 1);
}

bool GGPumpCtrl::IsAnimatingPump() {
	return pumpMdl.GetNumPumps() > 0;
}
void GGPumpCtrl::EndGame() {
	pumpMdl.SetSuccess(false);
	pumpMdl.SetContinueGame(false);
}

GGTestGameOverCtrl::GGTestGameOverCtrl() {}
GGTestGameOverCtrl::~GGTestGameOverCtrl() {}
GGAbstractModel* GGTestGameOverCtrl::GetModel() {
	return &gOMdl;
}
void GGTestGameOverCtrl::AnimateScreen() {
	gOMdl.GetGameOverAsset()->NextAnimation();
}
void GGTestGameOverCtrl::RestartGame() {
	gOMdl.SetContinueGame(false);
	gOMdl.SetSuccess(true);

}

GGCannonGameCtrl::GGCannonGameCtrl(): gravity(0.0f, .01f), curProjectileAsset(0) {
	for (int i = 0; i < cannonMdl.GetNumProjectiles(); i++) {
		velocities.push_back(sf::Vector2f(0, 0));
		projectileStatuses.push_back(LOADED);
		projectileDelays.push_back(DELAY);
	}
}
GGCannonGameCtrl::~GGCannonGameCtrl() {}
GGAbstractModel* GGCannonGameCtrl::GetModel() {
	return &cannonMdl;
}
void GGCannonGameCtrl::FireCannon(sf::Vector2i mousePos) {
	cannonMdl.SetCannonFiring(true);
	if (curProjectileAsset >= cannonMdl.GetNumProjectiles()) return;
	velocities[curProjectileAsset].x = (mousePos.x - cannonMdl.GetCannonAsset()->GetPos().x) / 400;
	velocities[curProjectileAsset].y = (mousePos.y - cannonMdl.GetCannonAsset()->GetPos().y) / 200;
	projectileStatuses[curProjectileAsset] = FIRED;
	cannonMdl.UpdateAmmunitionCount(cannonMdl.GetNumProjectiles() - curProjectileAsset - 1);
	curProjectileAsset++;
}
void GGCannonGameCtrl::ProjectileTick(sf::Time deltaT, int index) {
	if (projectileDelays[index]-- > 0) return;
	cannonMdl.MakeProjectileVisible(index);
	float dt = (float) deltaT.asMilliseconds();
	sf::Vector2f pos = cannonMdl.GetProjectile(index)->GetPos();
	pos.x = pos.x + (dt * velocities[index].x); // *horizontalTravelOffset);
	pos.y = pos.y + (dt * velocities[index].y); // update position

	velocities[index].y = velocities[index].y + (dt * gravity.y); // update velocity
	cannonMdl.GetProjectile(index)->SetPos(pos);
}
void GGCannonGameCtrl::AnimateCannonFire() {
	cannonMdl.GetCannonAsset()->NextAnimation();
	if (cannonMdl.GetCannonAsset()->AnimationCompleted()) {
		cannonMdl.SetCannonFiring(false);
	}
}
bool GGCannonGameCtrl::IsCannonFiring() {
	return cannonMdl.GetCannonFiring();
}

void GGCannonGameCtrl::ChangeCannonAngle(sf::Vector2i mousePos) {
	sf::Vector2f cannonPos = cannonMdl.GetCannonAsset()->GetPos();
	sf::Vector2f cannonOrigin = cannonMdl.GetCannonAsset()->GetOrigin();
	float adj = mousePos.x - cannonPos.x;
	float opp = mousePos.y - cannonPos.y;
	float angle = atanf(opp / adj) * (180.0f / PI);
	if (angle > 15) {
		angle -= 180;
	}
	cannonMdl.SetCannonAngle(angle);

	float hyp = cannonMdl.GetCannonLength();
	float projX = cosf(angle * (PI / 180.0f)) * hyp;
	float projY = sinf(angle * (PI / 180.0f)) * hyp;
	sf::Vector2f newPos(cannonPos.x + projX, cannonPos.y + projY);
	for (int i = 0; i < cannonMdl.GetNumProjectiles(); i++) {
		if (projectileStatuses[i] == LOADED) {
			cannonMdl.GetProjectile(i)->SetPos(newPos);
		}
	}
	projectileAnchorPoint = newPos;
}
bool GGCannonGameCtrl::ProjectileFired(int index) {
	return projectileStatuses[index] == FIRED;
}
bool GGCannonGameCtrl::ProjectileFinised(int index) {
	return cannonMdl.GetProjectile(index)->GetPos().y >= 720;
}