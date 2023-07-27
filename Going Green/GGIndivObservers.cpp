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
	if (view.GetEvent().type == sf::Event::MouseButtonPressed && !clickSwitch)
	{
		sf::Vector2i mousePos = (sf::Mouse::getPosition(GGWindow::Instance().GetWindow()));
		ctrl.ProcessClick(sf::Vector2f(mousePos));
		clickSwitch = true;
	}
	else if (view.GetEvent().type == sf::Event::MouseButtonReleased && clickSwitch)
	{
		clickSwitch = false;
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
	if (view.GetElapsedTime() - currentTime >= sf::milliseconds(1))
	{
		ctrl.TimerTick();
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
	if (view.GetElapsedTime() - currentTime >= sf::milliseconds(1))
	{
		ctrl.TimerTick();
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
	if (view.GetEvent().type == sf::Event::MouseButtonPressed && !clickSwitch)
	{
		clickSwitch = true;
		if (!ctrl.HasLetterMoved())
		{
			if (!ctrl.IsEnvelopeMoving())
			{
				ctrl.MoveLetter();
			}
		}
		else
		{
			ctrl.WinGame();
		}
	}
	else if (view.GetEvent().type == sf::Event::MouseButtonReleased && clickSwitch)
	{
		clickSwitch = false;
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
