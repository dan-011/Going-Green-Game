#include "GGIndivObservers.h"
GGLeftClickObserver::GGLeftClickObserver(GGSubject& subject, GGAbstractCtrl& controller) : subj(subject), ctrl(controller) {}
GGLeftClickObserver::~GGLeftClickObserver() {}
void GGLeftClickObserver::Update() {
	// do something
}

GGPumpClickObserver::GGPumpClickObserver(GGView& vw, GGPumpCtrl& controller) : view(vw), ctrl(controller), clickSwitch(false) {
	view.AddObserver(this);
}
GGPumpClickObserver::~GGPumpClickObserver() {}
void GGPumpClickObserver::Update() {
	if (view.GetEvent().type == sf::Event::MouseButtonPressed) {
		clickSwitch = true;
	}
	if (view.GetEvent().type == sf::Event::MouseButtonReleased && clickSwitch) {
		ctrl.PumpClicked();
		clickSwitch = false;
	}
}

GGPumpTickObserver::GGPumpTickObserver(GGView& vw, GGPumpCtrl& controller, sf::Time dt) : view(vw), ctrl(controller), deltaT(dt), currentTime(sf::microseconds(0)) {
	view.AddObserver(this);
}
GGPumpTickObserver::~GGPumpTickObserver() {}
void GGPumpTickObserver::Update() { // eventual implementation is to cycle the animation only when they have clicked (count the number of times they click and animate it x number of times)
	if (ctrl.IsAnimatingPump() && currentTime == sf::milliseconds(0)) {
		currentTime = view.GetElapsedTime();
	}
	if (view.GetElapsedTime() - currentTime >= deltaT && ctrl.IsAnimatingPump()) {
		ctrl.AnimatePump();
		currentTime = view.GetElapsedTime();
	}
}

GGTestGameOverTick::GGTestGameOverTick(GGView& vw, GGTestGameOverCtrl& controller) : view(vw), ctrl(controller), deltaT(sf::milliseconds(60)), currentTime(sf::milliseconds(0)) {
	view.AddObserver(this);
}
GGTestGameOverTick::~GGTestGameOverTick() {}
void GGTestGameOverTick::Update() {
	if (currentTime == sf::milliseconds(0)) {
		currentTime = view.GetElapsedTime();
	}
	if (view.GetElapsedTime() - currentTime >= deltaT) {
		ctrl.AnimateScreen();
		currentTime = view.GetElapsedTime();
	}
}

GGEndGameObserver::GGEndGameObserver(GGView& vw, GGPumpCtrl& controller) : view(vw), ctrl(controller) {
	view.AddObserver(this);
}
GGEndGameObserver::~GGEndGameObserver() {}
void GGEndGameObserver::Update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		ctrl.EndGame();
	}
}

GGRestartGameObserver::GGRestartGameObserver(GGView& vw, GGTestGameOverCtrl& controller) : view(vw), ctrl(controller) {
	view.AddObserver(this);
}
GGRestartGameObserver::~GGRestartGameObserver() {}
void GGRestartGameObserver::Update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		ctrl.RestartGame();
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
GGCannonFireObserver::GGCannonFireObserver(GGView& vw, GGCannonGameCtrl& controller) : view(vw), ctrl(controller), clickSwitch(false) {
	view.AddObserver(this);
}
GGCannonFireObserver::~GGCannonFireObserver() {}
void GGCannonFireObserver::Update() {
	if (view.GetEvent().type == sf::Event::MouseButtonPressed) {
		clickSwitch = true;
	}
	if (view.GetEvent().type == sf::Event::MouseButtonReleased && clickSwitch) {
		ctrl.FireCannon(sf::Mouse::getPosition(GGWindow::Instance().GetWindow()));
		clickSwitch = false;
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

GGProjectileTickObserver::GGProjectileTickObserver(GGView& vw, GGCannonGameCtrl& controller, int index) : view(vw), ctrl(controller), deltaT(sf::milliseconds(20)), currentTime(sf::milliseconds(0)), projectileIndex(index) {
	view.AddObserver(this);
}
GGProjectileTickObserver::~GGProjectileTickObserver() {}
void GGProjectileTickObserver::Update() {
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

GGTargetTickObserver::GGTargetTickObserver(GGView& vw, GGCannonGameCtrl& controller, int index) : view(vw), ctrl(controller), targetIndex(index), currentTime(sf::milliseconds(0)), deltaT(sf::milliseconds(200)) {
	view.AddObserver(this);
}
GGTargetTickObserver::~GGTargetTickObserver() {}
void GGTargetTickObserver::Update() {
	if (currentTime == sf::milliseconds(0)) {
		currentTime = view.GetElapsedTime();
	}
	if (!ctrl.TargetHit(targetIndex) && view.GetElapsedTime() - currentTime >= deltaT) { // if we are currently jumping
		ctrl.TargetTick(targetIndex);
		currentTime = view.GetElapsedTime();
	}
}