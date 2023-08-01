#include "GGIndivObservers.h"
GGLeftClickObserver::GGLeftClickObserver(GGSubject& subject, GGAbstractCtrl& controller) : subj(subject), ctrl(controller) {}
GGLeftClickObserver::~GGLeftClickObserver() {}
void GGLeftClickObserver::Update() {
	// do something
}

GGPumpClickObserver::GGPumpClickObserver(GGView& vw, GGPumpCtrl& controller) : view(vw), ctrl(controller) {
	view.AddObserver(this);
}
GGPumpClickObserver::~GGPumpClickObserver() {}
void GGPumpClickObserver::Update() {
	if (view.GetEvent().type == sf::Event::MouseButtonPressed) {
		ctrl.SetClickSwitch(true);
	}

	if (view.GetEvent().type == sf::Event::MouseButtonReleased && ctrl.GetClickSwitch()) {
		ctrl.PumpClicked();
		ctrl.SetClickSwitch(false);
	}
}

GGPumpTickObserver::GGPumpTickObserver(GGView& vw, GGPumpCtrl& controller, sf::Time dt) : view(vw), ctrl(controller), deltaT(dt), currentTime(sf::microseconds(0)), currentTimePump(sf::microseconds(0)) {
	view.AddObserver(this);
}
GGPumpTickObserver::~GGPumpTickObserver() {}
void GGPumpTickObserver::Update() {
	if (ctrl.IsAnimatingPump() && currentTimePump == sf::milliseconds(0)) {
		currentTimePump = view.GetElapsedTime();
	}
	if (view.GetElapsedTime() - currentTimePump >= deltaT / (float)ctrl.GetQueuedPumps() && ctrl.IsAnimatingPump()) {
		ctrl.AnimatePump();
		currentTimePump = view.GetElapsedTime();
	}
	if (view.GetElapsedTime() - currentTime >= deltaT)
	{
		ctrl.AnimateOil();
		currentTime = view.GetElapsedTime();
	}
	ctrl.CheckGameWon();
}

GGNewsTickObserver::GGNewsTickObserver(GGView& vw, GGNewsCtrl& controller, sf::Time dt) : view(vw), ctrl(controller), deltaT(dt)
{
	view.AddObserver(this);
	mouthDeltaTime = sf::milliseconds(75);
	mouthTotalDeltaTime = sf::seconds(2);
}

GGNewsTickObserver::~GGNewsTickObserver(){}

void GGNewsTickObserver::Update()
{
	if (currentTime == sf::milliseconds(0) || !ctrl.IsAnimatingButton())
	{
		currentTime = view.GetElapsedTime();
	}
	if (view.GetElapsedTime() - currentTime >= deltaT && ctrl.IsAnimatingButton())
	{
		ctrl.ClearButtonAnim();
		currentTime = view.GetElapsedTime();
	}
	if (currentTimeMouth == sf::milliseconds(0) || !ctrl.IsAnimatingMouth())
	{
		currentTimeMouth = view.GetElapsedTime();
	}
	if (view.GetElapsedTime() - currentTimeMouth >= mouthDeltaTime && ctrl.IsAnimatingMouth())
	{
		ctrl.ChangeMouth();
		currentTimeMouth = view.GetElapsedTime();
	}
	if (currentTimeMouthTotal == sf::milliseconds(0) || !ctrl.IsAnimatingMouth() || ctrl.GetNewClick())
	{
		currentTimeMouthTotal = view.GetElapsedTime();
		ctrl.SetNewClick(false);
	}
	if (view.GetElapsedTime() - currentTimeMouthTotal >= mouthTotalDeltaTime && ctrl.IsAnimatingMouth())
	{
		ctrl.ResetMouth();
		ctrl.SetAnimatingMouth(false);
	}
}

GGNewsButtonClickObserver::GGNewsButtonClickObserver(GGView& vw, GGNewsCtrl& controller) : view(vw), ctrl(controller)
{
	view.AddObserver(this);
}

GGNewsButtonClickObserver::~GGNewsButtonClickObserver()
{

}

void GGNewsButtonClickObserver::Update()
{
	if (view.GetEvent().type == sf::Event::MouseButtonPressed) {
		ctrl.SetClickSwitch(true);
	}

	if (view.GetEvent().type == sf::Event::MouseButtonReleased && ctrl.GetClickSwitch()) {
		sf::Vector2i mousePos = (sf::Mouse::getPosition(GGWindow::Instance().GetWindow()));
		ctrl.ProcessClick(sf::Vector2f(mousePos));
		ctrl.SetClickSwitch(false);
	}
}

GGNewsTimerObserver::GGNewsTimerObserver(GGView& vw, GGNewsCtrl& controller) : view(vw), ctrl(controller)
{
	view.AddObserver(this);
}

GGNewsTimerObserver::~GGNewsTimerObserver()
{

}

void GGNewsTimerObserver::Update()
{
	if (currentTime == sf::milliseconds(0))
	{
		currentTime = view.GetElapsedTime();
	}
	if (view.GetElapsedTime() - currentTime >= sf::milliseconds(10))
	{
		ctrl.TimerTick();
		currentTime = view.GetElapsedTime();
	}
	if (ctrl.TimerCompleted())
	{
		ctrl.EndGame();
	}
}

GGPumpTimerObserver::GGPumpTimerObserver(GGView& vw, GGPumpCtrl& controller) : view(vw), ctrl(controller)
{
	view.AddObserver(this);
}
GGPumpTimerObserver::~GGPumpTimerObserver()
{
}

void GGPumpTimerObserver::Update()
{
	if (currentTime == sf::milliseconds(0))
	{
		currentTime = view.GetElapsedTime();
	}
	if (view.GetElapsedTime() - currentTime >= sf::milliseconds(10))
	{
		ctrl.TimerTick();
		currentTime = view.GetElapsedTime();
	}
	if (ctrl.TimerCompleted())
	{
		ctrl.EndGame();
	}
}


GGStageTransitionTickObserver::GGStageTransitionTickObserver(GGView& vw, GGStageTransitionCtrl& controller, sf::Time dt) : view(vw), ctrl(controller), deltaT(dt)
{
	view.AddObserver(this);
}

GGStageTransitionTickObserver::~GGStageTransitionTickObserver()
{

}

void GGStageTransitionTickObserver::Update()
{
	if (currentTime == sf::milliseconds(0))
	{
		currentTime = view.GetElapsedTime();
	}
	if (view.GetElapsedTime() - currentTime >= deltaT)
	{
		if (ctrl.IsLetterMoving())
		{
			ctrl.MoveLetter();
		}
		if (ctrl.IsEnvelopeMoving())
		{
			ctrl.MoveEnvelope();
		}
		currentTime = view.GetElapsedTime();
	}

}

GGStageTransitionClickObserver::GGStageTransitionClickObserver(GGView& vw, GGStageTransitionCtrl& controller) : view(vw), ctrl(controller)
{
	view.AddObserver(this);
}

GGStageTransitionClickObserver::~GGStageTransitionClickObserver()
{

}

void GGStageTransitionClickObserver::Update()
{
	if (view.GetEvent().type == sf::Event::MouseButtonPressed) {
		ctrl.SetClickSwitch(true);
	}

	if (view.GetEvent().type == sf::Event::MouseButtonReleased && ctrl.GetClickSwitch()) {
		if (!ctrl.HasLetterMoved())
		{
			if (!ctrl.IsEnvelopeMoving())
			{
				ctrl.MoveLetter();
			}
			else {
				ctrl.SetClickSwitch(false);
			}
		}
		else
		{
			ctrl.WinGame();
		}
		ctrl.SetClickSwitch(false);
	}
}

GGClockMSObserver::GGClockMSObserver(GGView& vw, GGAbstractCtrl& controller) : view(vw), ctrl(controller), deltaT(sf::milliseconds(10)), currentTime(sf::milliseconds(0)) {
	view.AddObserver(this);
}
GGClockMSObserver::~GGClockMSObserver() {}
void GGClockMSObserver::Update() {
	if (!ctrl.GetModel()->GetTimer()->GetTimerStarted()) return;
	if (currentTime == sf::milliseconds(0)) {
		currentTime = view.GetElapsedTime();
	}
	if (view.GetElapsedTime() - currentTime >= deltaT) {
		ctrl.TimerTick();
		currentTime = view.GetElapsedTime();
	}
}
GGCannonFireObserver::GGCannonFireObserver(GGView& vw, GGCannonGameCtrl& controller) : view(vw), ctrl(controller) {
	view.AddObserver(this);
}
GGCannonFireObserver::~GGCannonFireObserver() {}
void GGCannonFireObserver::Update() {
	if (view.GetEvent().type == sf::Event::MouseButtonPressed) {
		ctrl.SetClickSwitch(true);
	}
	if (view.GetEvent().type == sf::Event::MouseButtonReleased && ctrl.GetClickSwitch()) {
		ctrl.FireCannon(sf::Mouse::getPosition(GGWindow::Instance().GetWindow()));
		ctrl.SetClickSwitch(false);
	}
}

GGCannonTickObserver::GGCannonTickObserver(GGView& vw, GGCannonGameCtrl& controller) : view(vw), ctrl(controller), deltaT(sf::milliseconds(50)), currentTime(sf::milliseconds(0)) {
	view.AddObserver(this);
}
GGCannonTickObserver::~GGCannonTickObserver() {}
void GGCannonTickObserver::Update() {
	if (ctrl.IsCannonFiring() && currentTime == sf::milliseconds(0)) {
		currentTime = view.GetElapsedTime();
	}
	if (!ctrl.IsCannonFiring()) return;
	if (view.GetElapsedTime() - currentTime >= deltaT && ctrl.IsCannonFiring()) {
		ctrl.AnimateCannonFire();
		currentTime = view.GetElapsedTime();
	}
}
#include <iostream>
using namespace std;
GGCannonMoveObserver::GGCannonMoveObserver(GGView& vw, GGCannonGameCtrl& controller) : view(vw), ctrl(controller) {
	view.AddObserver(this);
}
GGCannonMoveObserver::~GGCannonMoveObserver() {}
void GGCannonMoveObserver::Update() {
	if (view.GetEvent().type == sf::Event::MouseMoved && !ctrl.IsCannonFiring()) {
		ctrl.ChangeCannonAngle(sf::Mouse::getPosition(GGWindow::Instance().GetWindow()));
	}
}

GGProjectileTickObserver::GGProjectileTickObserver(GGView& vw, GGCannonGameCtrl& controller, int index, int stg) : view(vw), ctrl(controller), deltaT(sf::milliseconds(20)), currentTime(sf::milliseconds(0)), projectileIndex(index), stage(stg) {
	view.AddObserver(this);
}
GGProjectileTickObserver::~GGProjectileTickObserver() {}
void GGProjectileTickObserver::Update() {
	if (stage > ctrl.GetModel()->GetStage()) return;
	if (ctrl.IsCannonFiring() && currentTime == sf::milliseconds(0)) { // if jumping has been initiated and we have not recorded start time
		currentTime = view.GetElapsedTime();
	}
	else if (ctrl.ProjectileFinised(projectileIndex)) { // if jumping has finished
		currentTime = sf::milliseconds(0);
		return;
	}
	if (ctrl.ProjectileFired(projectileIndex) && view.GetElapsedTime() - currentTime >= deltaT) { // if we are currently jumping
		ctrl.ProjectileTick(deltaT, projectileIndex);
		currentTime = view.GetElapsedTime();
	}
} // limit ammunition and create that many observers
// make an asset for a projectile

GGTargetTickObserver::GGTargetTickObserver(GGView& vw, GGCannonGameCtrl& controller, int index, int stg) : view(vw), ctrl(controller), targetIndex(index), currentTime(sf::milliseconds(0)), stage(stg) {
	view.AddObserver(this);
}
GGTargetTickObserver::~GGTargetTickObserver() {}
void GGTargetTickObserver::Update() {
	if (stage > ctrl.GetModel()->GetStage()) return;
	if (currentTime == sf::milliseconds(0)) {
		currentTime = view.GetElapsedTime();
	}
	if (!ctrl.TargetHit(targetIndex) && view.GetElapsedTime() - currentTime >= ctrl.GetTargetDeltaT()) { // if we are currently jumping
		ctrl.TargetTick(targetIndex);
		currentTime = view.GetElapsedTime();
	}
}

GGStageFourSwitchObserver::GGStageFourSwitchObserver(GGView& vw, GGStageFourCtrl& controller) : view(vw), ctrl(controller), deltaT(sf::seconds(6)), currentTime(sf::seconds(0)) {
	view.AddObserver(this);
}
GGStageFourSwitchObserver::~GGStageFourSwitchObserver() {}
void GGStageFourSwitchObserver::Update() {
	if (currentTime == sf::seconds(0)) {
		currentTime = view.GetElapsedTime();
	}
	if (ctrl.ContinueOntoNext() && view.GetElapsedTime() - currentTime >= deltaT) {
		ctrl.NextGame();
		currentTime = view.GetElapsedTime();
	}
}

GGBookendsTextTickObserver::GGBookendsTextTickObserver(GGView& vw, GGBookendsCtrl& controller) : view(vw), ctrl(controller), currentTime(sf::milliseconds(0)), deltaT(sf::milliseconds(750)) {
	view.AddObserver(this);
}
GGBookendsTextTickObserver::~GGBookendsTextTickObserver() {}
void GGBookendsTextTickObserver::Update() {
	if (currentTime == sf::milliseconds(0)) {
		currentTime = view.GetElapsedTime();
	}
	if (view.GetElapsedTime() - currentTime >= deltaT) {
		ctrl.SwitchTextVisibility();
		currentTime = view.GetElapsedTime();
	}
}

GGContinueGameObserver::GGContinueGameObserver(GGView& vw, GGBookendsCtrl& controller, sf::Keyboard::Key continueKey) : view(vw), ctrl(controller), key(continueKey) {
	view.AddObserver(this);
}
GGContinueGameObserver::~GGContinueGameObserver() {}
void GGContinueGameObserver::Update() {
	if (sf::Keyboard::isKeyPressed(key)) {
		ctrl.Continue();
	}
}

GGRollCreditsObserver::GGRollCreditsObserver(GGView& vw, GGStageFourCtrl& controller) : view(vw), ctrl(controller), currentTime(sf::milliseconds(0)), deltaT(sf::milliseconds(30)) {
	view.AddObserver(this);
}
GGRollCreditsObserver::~GGRollCreditsObserver() {}
void GGRollCreditsObserver::Update() {
	if (currentTime == sf::milliseconds(0)) {
		currentTime = view.GetElapsedTime();
	}
	if (view.GetElapsedTime() - currentTime >= deltaT) {
		ctrl.ShiftCredits();
		currentTime = view.GetElapsedTime();
	}
}

GGTransitionExitObserver::GGTransitionExitObserver(GGView& vw, GGAbstractCtrl& controller) : view(vw), ctrl(controller), waitTime(sf::seconds(2.5)) {
	view.AddObserver(this);
}
GGTransitionExitObserver::~GGTransitionExitObserver() {}
void GGTransitionExitObserver::Update() {
	if (ctrl.GetModel()->GetTransitionTime() == sf::seconds(0)) {
		ctrl.GetModel()->SetTransitionTime(view.GetElapsedTime());
	}
	if (view.GetElapsedTime() - ctrl.GetModel()->GetTransitionTime() > waitTime) {
		ctrl.RemoveTransition();
		GGTimerAsset* timer = ctrl.GetModel()->GetTimer();
		if (timer != NULL) {
			timer->StartTimer();
		}
	}
}