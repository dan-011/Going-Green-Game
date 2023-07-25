#include "GGAbstractCtrl.h"
#define PI 3.14159265359f
#define DELAY 15
#define DEBUG 0
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

bool OnSegment(sf::Vector2f pi, sf::Vector2f pj, sf::Vector2f pk) {
	return (min(pi.x, pj.x) <= pk.x) && (pk.x <= max(pi.x, pj.x)) && (min(pi.y, pj.y) <= pk.y) && (pk.y <= max(pi.y, pj.y));
}
double Direction(sf::Vector2f pi, sf::Vector2f pj, sf::Vector2f pk) {
	sf::Vector2f diff1(pk.x - pi.x, pk.y - pi.y);
	sf::Vector2f diff2(pj.x - pi.x, pj.y - pi.y);
	return (diff1.x * diff2.y) - (diff2.x * diff1.y);
}
bool IsIntersect(sf::Vector2f p1S, sf::Vector2f p1E, sf::Vector2f p2S, sf::Vector2f p2E) {
	sf::Vector2f p1 = p1S;
	sf::Vector2f p2 = p1E;
	sf::Vector2f p3 = p2S;
	sf::Vector2f p4 = p2E;

	double d1 = Direction(p3, p4, p1);
	double d2 = Direction(p3, p4, p2);
	double d3 = Direction(p1, p2, p3);
	double d4 = Direction(p1, p2, p4);
	if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
		return true;
	}
	else if (d1 == 0 && OnSegment(p3, p4, p1)) {
		return true;
	}
	else if (d2 == 0 && OnSegment(p3, p4, p2)) {
		return true;
	}
	else if (d3 == 0 && OnSegment(p1, p2, p3)) {
		return true;
	}
	else if (d4 == 0 && OnSegment(p1, p2, p4)) {
		return true;
	}
	else {
		return false;
	}
}

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

	srand((unsigned int) time(NULL));
	for (int i = 0; i < cannonMdl.GetNumTargets(); i++) {
		targetHitStatuses.push_back(false);
		// targetWaitTicks.push_back(rand() % 20);
	}
	targetWaitTicks.push_back(0);
	targetWaitTicks.push_back(75);
	targetWaitTicks.push_back(110);
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
	if (projectileDelays[index]-- > 0 || projectileStatuses[index] == LANDED) return;
	cannonMdl.MakeProjectileVisible(index);
	float dt = (float) deltaT.asMilliseconds();
	sf::Vector2f pos = cannonMdl.GetProjectile(index)->GetPos();
	sf::Vector2f prevPos = pos;
	pos.x = pos.x + (dt * velocities[index].x); // *horizontalTravelOffset);
	pos.y = pos.y + (dt * velocities[index].y); // update position

	velocities[index].y = velocities[index].y + (dt * gravity.y); // update velocity
	cannonMdl.GetProjectile(index)->SetPos(pos);


	for (int i = 0; i < cannonMdl.GetNumTargets(); i++) {
		// line by y = 550
		GGSheetAsset* target = cannonMdl.GetTarget(i);
		sf::FloatRect targetBoundingBox = target->GetBoundingBox();
		float leftEdge = targetBoundingBox.left;
		float rightEdge = targetBoundingBox.left + targetBoundingBox.width;
		sf::Vector2f p2S(leftEdge, 550);
		sf::Vector2f p2E(rightEdge, 550);
		if (IsIntersect(prevPos, pos, p2S, p2E)) {
			targetHitStatuses[i] = true;
			target->SetCurFrame(4);
			target->SetPos(sf::Vector2f(target->GetPos().x - 10, target->GetPos().y));
			pos = sf::Vector2f(-100, -100);
			projectileStatuses[index] = LANDED;
			break;
		}
	}
	if (pos.y > 570 && prevPos.y < pos.y) {
		projectileStatuses[index] = LANDED;
	}
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
	return projectileStatuses[index] == LANDED;
}
bool GGCannonGameCtrl::TargetHit(int index) {
	return targetHitStatuses[index] == true;
}
void GGCannonGameCtrl::TargetTick(int index) {
	if (targetWaitTicks[index]-- > 0) return;
	GGSheetAsset* target = cannonMdl.GetTarget(index);
	target->NextAnimation();
	sf::Vector2f pos = target->GetPos();
	int currentFrame = target->GetCurFrame();
	int xOffset = -15;
	if (currentFrame == 0) {
		xOffset = 25;
	}
	if (currentFrame == 3) {
		xOffset = -10;
	}
	
	target->SetPos(sf::Vector2f(pos.x + xOffset, pos.y));
}