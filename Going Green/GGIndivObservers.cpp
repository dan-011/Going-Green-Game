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