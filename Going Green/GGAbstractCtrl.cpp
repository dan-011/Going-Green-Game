#include "GGAbstractCtrl.h"
#define PI 3.14159265359f
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

GGGameOverCtrl::GGGameOverCtrl() {}
GGGameOverCtrl::~GGGameOverCtrl() {}
GGAbstractModel* GGGameOverCtrl::GetModel() {
	return &gOMdl;
}
void GGGameOverCtrl::AnimateScreen() {
	gOMdl.GetGameOverAsset()->NextAnimation();
}
void GGGameOverCtrl::RestartGame() {
	gOMdl.SetContinueGame(false);
	gOMdl.SetSuccess(true);

}

GGCannonGameCtrl::GGCannonGameCtrl(): gravity(0.0f, .01f) {}
GGCannonGameCtrl::~GGCannonGameCtrl() {}
GGAbstractModel* GGCannonGameCtrl::GetModel() {
	return &cannonMdl;
}
void GGCannonGameCtrl::FireCannon(sf::Vector2i mousePos) {
	cannonMdl.SetCannonFiring(true);
	cannonMdl.GetCannonSound()->Play();
	int curProjectileAsset = cannonMdl.GetCurProjectileAsset();
	if (curProjectileAsset >= cannonMdl.GetNumProjectiles()) return;
	float velX = (mousePos.x - cannonMdl.GetCannonAsset()->GetPos().x) / 400;
	float velY = (mousePos.y - cannonMdl.GetCannonAsset()->GetPos().y) / 200;
	cannonMdl.SetVelocity(curProjectileAsset, sf::Vector2f(velX, velY));
	cannonMdl.SetProjectileStatus(curProjectileAsset, FIRED);
	cannonMdl.UpdateAmmunitionCount(cannonMdl.GetNumProjectiles() - curProjectileAsset - 1);
	cannonMdl.SetCurProjectileAsset(curProjectileAsset + 1);
}
void GGCannonGameCtrl::ProjectileTick(sf::Time deltaT, int index) {
	if (cannonMdl.GetProjectileDelay(index) > 0 || cannonMdl.GetProjectileStatus(index) == LANDED) return;
	int val = cannonMdl.GetProjectileDelay(index);
	if(val == -1) cannonMdl.MakeProjectileVisible(index);
	float dt = (float) deltaT.asMilliseconds();
	sf::Vector2f pos = cannonMdl.GetProjectile(index)->GetPos();
	sf::Vector2f vel = cannonMdl.GetVelocity(index);
	sf::Vector2f prevPos = pos;
	pos.x = pos.x + (dt * vel.x); // *horizontalTravelOffset);
	pos.y = pos.y + (dt * vel.y); // update position

	vel.y = vel.y + (dt * gravity.y); // update velocity
	cannonMdl.SetVelocity(index, vel);
	cannonMdl.GetProjectile(index)->SetPos(pos);


	for (int i = 0; i < cannonMdl.GetNumTargets(); i++) {
		// line by y = 550
		GGSheetAsset* target = cannonMdl.GetTarget(i);
		sf::FloatRect targetBoundingBox = target->GetBoundingBox();
		float leftEdge = targetBoundingBox.left;
		float rightEdge = targetBoundingBox.left + targetBoundingBox.width;
		sf::Vector2f p2S(leftEdge, 550);
		sf::Vector2f p2E(rightEdge, 550);
		if (IsIntersect(prevPos, pos, p2S, p2E) && cannonMdl.GetTargetHitStatus(i) == false) {
			cannonMdl.SetTargetHitStatus(i, true);
			target->SetCurFrame(4);
			target->SetPos(sf::Vector2f(target->GetPos().x - 10, target->GetPos().y));
			pos = sf::Vector2f(-100, -100);
			cannonMdl.SetProjectileStatus(index, LANDED);
			cannonMdl.IncrementHitCount();
			break;
		}
	}
	if (pos.y > 570 && prevPos.y < pos.y) {
		cannonMdl.SetProjectileStatus(index, LANDED);
	}
	cannonMdl.GetProjectile(index)->SetPos(pos);
	if (cannonMdl.GetHitCount() == cannonMdl.GetNumTargets()) {
		cannonMdl.SetSuccess(true);
		cannonMdl.SetContinueGame(false);
	}
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
		if (cannonMdl.GetProjectileStatus(i) == LOADED) {
			cannonMdl.GetProjectile(i)->SetPos(newPos);
		}
	}
	projectileAnchorPoint = newPos;
}
bool GGCannonGameCtrl::ProjectileFired(int index) {
	return cannonMdl.GetProjectileStatus(index) == FIRED;
}
bool GGCannonGameCtrl::ProjectileFinised(int index) {
	return cannonMdl.GetProjectileStatus(index) == LANDED;
}
bool GGCannonGameCtrl::TargetHit(int index) {
	return cannonMdl.GetTargetHitStatus(index) == true;
}
void GGCannonGameCtrl::TargetTick(int index) {
	if (cannonMdl.TargetWaitTick(index) > 0) return;
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

	if (target->GetPos().x <= cannonMdl.GetCannonAsset()->GetPos().x) {
		for (int i = 0; i < cannonMdl.GetNumTargets(); i++) {
			cannonMdl.SetTargetHitStatus(i, true);
			// maybe sleep
			cannonMdl.SetContinueGame(false);
			cannonMdl.SetSuccess(false);
		}
	}
}
sf::Time GGCannonGameCtrl::GetTargetDeltaT() {
	return cannonMdl.GetTagetSpeed();
}

GGStageFourCtrl::GGStageFourCtrl() {}
GGStageFourCtrl::~GGStageFourCtrl() {}
GGAbstractModel* GGStageFourCtrl::GetModel() {
	return &stageFourModel;
}
void GGStageFourCtrl::NextGame() {
	stageFourModel.NextScreen();
}
bool GGStageFourCtrl::ContinueOntoNext() {
	return stageFourModel.GetScreenNumber() < 3;
}

GGTitleScreenCtrl::GGTitleScreenCtrl() {}
GGTitleScreenCtrl::~GGTitleScreenCtrl() {}
GGAbstractModel* GGTitleScreenCtrl::GetModel() {
	return &titleScreenModel;
}
void GGTitleScreenCtrl::ExitTitleScreen() {
	titleScreenModel.SetSuccess(true);
	titleScreenModel.SetContinueGame(false);
}
