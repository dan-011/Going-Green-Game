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
bool GGAbstractCtrl::GetClickSwitch() {
	return GetModel()->GetClickSwitch();
}
void GGAbstractCtrl::SetClickSwitch(bool clckSwtch) {
	GetModel()->SetClickSwitch(clckSwtch);
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

void GGPumpCtrl::AnimateOil()
{
	pumpMdl.GetOil()->NextAnimation();
}
void GGPumpCtrl::PumpClicked() {
	if (pumpMdl.GetTransition()->GetDrawing())
	{
		pumpMdl.GetTransition()->SetDrawing(false);
		pumpMdl.GetTimer()->StartTimer();
		return;
	}
	pumpMdl.SetNumPumps(pumpMdl.GetNumPumps() + 1);
	pumpMdl.IncrementPumps();
	if (pumpMdl.PumpMaxReached())
	{
		pumpMdl.GetOil()->SetStart(true);
	}
}

void GGPumpCtrl::CheckGameWon()
{
	if (pumpMdl.PumpMaxReached() && pumpMdl.GetOil()->CheckFinishedAnimating())
	{
		WinGame();
	}
}
bool GGPumpCtrl::IsAnimatingPump() {
	return pumpMdl.GetNumPumps() > 0;
}


void GGPumpCtrl::EndGame() {
	pumpMdl.SetSuccess(false);
	pumpMdl.SetContinueGame(false);
}

void GGPumpCtrl::WinGame()
{
	pumpMdl.SetSuccess(true);
	pumpMdl.SetContinueGame(false);
}
int GGPumpCtrl::GetQueuedPumps()
{
	return pumpMdl.GetNumPumps();
}

bool GGPumpCtrl::TimerTick()
{
	if (!pumpMdl.GetTimer()->GetTimerStarted()) return false;
	pumpMdl.GetTimer()->TickMS();
	return pumpMdl.GetTimer()->TimerCompleted();
}

bool GGPumpCtrl::TimerCompleted()
{
	return pumpMdl.GetTimer()->TimerCompleted();
}

GGNewsCtrl::GGNewsCtrl() : newsMdl(10)
{
	GenerateQuestion();
}

GGNewsCtrl::~GGNewsCtrl() {}

GGAbstractModel* GGNewsCtrl::GetModel()
{
	return &newsMdl;
}

void GGNewsCtrl::EndGame()
{
	newsMdl.SetContinueGame(false);
	newsMdl.SetSuccess(false);
	newsMdl.StopAllVoices();
}

void GGNewsCtrl::WinGame()
{
	newsMdl.SetContinueGame(false);
	newsMdl.SetSuccess(true);
}

bool GGNewsCtrl::IsAnimatingButton()
{
	return (newsMdl.GetButton(0)->GetClicked() || newsMdl.GetButton(1)->GetClicked());
}

void GGNewsCtrl::ClearButtonAnim()
{
	newsMdl.GetButton(0)->SetClicked(false);
	newsMdl.GetButton(0)->SetCurFrame(0);
	newsMdl.GetButton(1)->SetClicked(false);
	newsMdl.GetButton(1)->SetCurFrame(0);
}
void GGNewsCtrl::PressButton(int button)
{
	if (!IsAnimatingButton())
	{
		newsMdl.GetButton(button)->SetClicked(true);
		if (button == goodAnswer)
		{
			newsMdl.SetNumAnswers(newsMdl.GetNumAnswers() + 1);
			newsMdl.GetButton(button)->SetCurFrame(1);
			GenerateQuestion();
		}
		else
		{
			newsMdl.GetButton(button)->SetCurFrame(2);
			newsMdl.SetNumAnswers(newsMdl.GetNumAnswers() - 1);
			GenerateQuestion();
		}
		SetAnimatingMouth(true);
		SetNewClick(true);
	}
	if (newsMdl.GoalMet())
	{
		newsMdl.SetSuccess(true);
		newsMdl.SetContinueGame(false);
	}
}

void GGNewsCtrl::ProcessClick(sf::Vector2f mousePos)
{
	if (newsMdl.GetTransition()->GetDrawing())
	{
		newsMdl.GetTransition()->SetDrawing(false);
		newsMdl.GetTimer()->StartTimer();
		return;
	}
	if (newsMdl.GetButton(0)->GetGlobalBounds().contains(mousePos))
	{
		PressButton(0);
	}
	else if (newsMdl.GetButton(1)->GetGlobalBounds().contains(mousePos))
	{
		PressButton(1);
	}
}

void GGNewsCtrl::GenerateQuestion()
{
	newsMdl.PlayVoiceSFX();
	int qNum = rand() % questions.size();
	newsMdl.GetQuestionText()->SetText(questions[qNum]);
	goodAnswer = rand() % 2;
	if (goodAnswer == 1)
	{
		newsMdl.GetButton(0)->SetText(answers[2 * qNum]);
		newsMdl.GetButton(1)->SetText(answers[2 * qNum + 1]);
	}
	else
	{
		newsMdl.GetButton(1)->SetText(answers[2 * qNum]);
		newsMdl.GetButton(0)->SetText(answers[2 * qNum + 1]);
	}
}

bool GGNewsCtrl::TimerTick() {
	if (!newsMdl.GetTimer()->GetTimerStarted()) return false;
	newsMdl.GetTimer()->TickMS();
	return newsMdl.GetTimer()->TimerCompleted();
}

bool GGNewsCtrl::TimerCompleted()
{
	return newsMdl.GetTimer()->TimerCompleted();
}
void GGNewsCtrl::ChangeMouth()
{
	newsMdl.ChangeMouth();
}
void GGNewsCtrl::ResetMouth()
{
	newsMdl.ResetMouth();
}
bool GGNewsCtrl::IsAnimatingMouth()
{
	return isAnimatingMouth;
}
void GGNewsCtrl::SetAnimatingMouth(bool val)
{
	isAnimatingMouth = val;
	if (val)
	{
		ChangeMouth();
	}
	else
	{
		ResetMouth();
	}
}
bool GGNewsCtrl::GetNewClick()
{
	return newClick;
}
void GGNewsCtrl::SetNewClick(bool click)
{
	newClick = click;
}
GGStageTransitionCtrl::GGStageTransitionCtrl() : transMdl()
{
	transMdl.SetEnvelopeVelocity(initialEnvelopeVelocity);
}

GGStageTransitionCtrl::~GGStageTransitionCtrl()
{

}

GGAbstractModel* GGStageTransitionCtrl::GetModel()
{
	return &transMdl;
}

void GGStageTransitionCtrl::WinGame()
{
	transMdl.SetContinueGame(false);
	transMdl.SetSuccess(true);
}

bool GGStageTransitionCtrl::IsEnvelopeMoving()
{
	return (transMdl.GetEnvelopeVelocity() != 0);
}

bool GGStageTransitionCtrl::IsLetterMoving()
{
	return (transMdl.GetLetterVelocity() != 0);
}

bool GGStageTransitionCtrl::HasLetterMoved()
{
	return transMdl.GetLetterMoved();
}

void GGStageTransitionCtrl::MoveLetter()
{
	if (!IsLetterMoving())
	{
		transMdl.SetLetterVelocity(initialLetterVelocity);
		transMdl.PlayLetterSound();
		return;
	}
	transMdl.GetLetter()->SetPos(sf::Vector2f(transMdl.GetLetter()->GetPos().x, transMdl.GetLetter()->GetPos().y + transMdl.GetLetterVelocity()));
	transMdl.SetLetterVelocity(transMdl.GetLetterVelocity() + transMdl.GetLetterDeceleration());
	if (transMdl.GetLetterVelocity() >= 0)
	{
		transMdl.SetLetterVelocity(0);
		transMdl.SetLetterMoved(true);
	}
}

void GGStageTransitionCtrl::MoveEnvelope()
{
	transMdl.GetEnvelope()->SetPos(sf::Vector2f(transMdl.GetEnvelope()->GetPos().x, transMdl.GetEnvelope()->GetPos().y + transMdl.GetEnvelopeVelocity()));
	transMdl.SetEnvelopeVelocity(transMdl.GetEnvelopeVelocity() + transMdl.GetEnvelopeDeceleration());
	if (transMdl.GetEnvelopeVelocity() <= 0)
	{
		transMdl.SetEnvelopeVelocity(0);
	}
}

GGCannonGameCtrl::GGCannonGameCtrl(): gravity(0.0f, .01f) {}
GGCannonGameCtrl::~GGCannonGameCtrl() {}
GGAbstractModel* GGCannonGameCtrl::GetModel() {
	return &cannonMdl;
}
void GGCannonGameCtrl::FireCannon(sf::Vector2i mousePos) {
	if (!cannonMdl.GetGameStarted()) {
		cannonMdl.GetTransition()->SetDrawing(false);
		cannonMdl.SetGameStarted(true);
		return;
	}
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
	if (!cannonMdl.GetGameStarted()) return;
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
	if (!cannonMdl.GetGameStarted()) return;
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
	if (!cannonMdl.GetGameStarted()) return;
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

GGBookendsCtrl::GGBookendsCtrl(GGBookendsModel* bookendMdl) : bookendModel(bookendMdl) {}
GGBookendsCtrl::~GGBookendsCtrl() {}
GGAbstractModel* GGBookendsCtrl::GetModel() {
	return bookendModel;
}
void GGBookendsCtrl::Continue() {
	bookendModel->SetSuccess(true);
	bookendModel->SetContinueGame(false);
}
void GGBookendsCtrl::SwitchTextVisibility() {
	bookendModel->SetTextVisibility(!bookendModel->GetTextVisibility());
}

GGSecretEndingCtrl::GGSecretEndingCtrl() {}
GGSecretEndingCtrl::~GGSecretEndingCtrl() {}
GGAbstractModel* GGSecretEndingCtrl::GetModel() {
	return &secretEndingModel;
}