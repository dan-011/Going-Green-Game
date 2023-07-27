#include "GGIndivObservers.h"
GGLeftClickObserver::GGLeftClickObserver(GGSubject& subject, GGAbstractCtrl& controller) : subj(subject), ctrl(controller) {}
GGLeftClickObserver::~GGLeftClickObserver() {}
void GGLeftClickObserver::Update() {
	// do something
}

GGTestGameOverTick::GGTestGameOverTick(GGView& vw, GGGameOverCtrl& controller) : view(vw), ctrl(controller), deltaT(sf::milliseconds(60)), currentTime(sf::milliseconds(0)) {
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

GGRestartGameObserver::GGRestartGameObserver(GGView& vw, GGGameOverCtrl& controller) : view(vw), ctrl(controller) {
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