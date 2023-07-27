#ifndef __GGINDIVOBSERVERS_H
#define __GGINDIVOBSERVERS_H

#include "GGAbstractObserver.h"
#include "GGAbstractCtrl.h"
#include "GGSubject.h"
#include "GGView.h"

class GGLeftClickObserver : public GGAbstractObserver {
public:
	GGLeftClickObserver(GGSubject& subject, GGAbstractCtrl& controller);
	virtual ~GGLeftClickObserver();
	virtual void Update() override;

private:
	GGSubject& subj;
	GGAbstractCtrl& ctrl;
};

class GGPumpClickObserver : public GGAbstractObserver {
public:
	GGPumpClickObserver(GGView& vw, GGPumpCtrl& controller);
	~GGPumpClickObserver();
	virtual void Update() override;

private:
	GGView& view;
	GGPumpCtrl& ctrl;
	bool clickSwitch;
};

class GGPumpTickObserver : public GGAbstractObserver {
public:
	GGPumpTickObserver(GGView& vw, GGPumpCtrl& controller, sf::Time dt);
	~GGPumpTickObserver();
	virtual void Update() override;

private:
	GGView& view;
	GGPumpCtrl& ctrl;
	sf::Time deltaT;
	sf::Time currentTimePump;
	sf::Time currentTime;
};

class GGNewsTickObserver : public GGAbstractObserver {
public:
	GGNewsTickObserver(GGView& vw, GGNewsCtrl& controller, sf::Time dt);
	~GGNewsTickObserver();
	virtual void Update() override;
	

private:
	GGView& view;
	GGNewsCtrl& ctrl;
	sf::Time deltaT;
	sf::Time currentTime;
	sf::Time currentTimeMouth;
	sf::Time mouthDeltaTime;
	sf::Time currentTimeMouthTotal;
	sf::Time mouthTotalDeltaTime;
};

class GGNewsButtonClickObserver : public GGAbstractObserver
{
public:
	GGNewsButtonClickObserver(GGView& vw, GGNewsCtrl& controller);
	~GGNewsButtonClickObserver();
	virtual void Update() override;
private:
	GGView& view;
	GGNewsCtrl& ctrl;
	bool clickSwitch = false;
};

class GGNewsTimerObserver : public GGAbstractObserver
{
public:
	GGNewsTimerObserver(GGView& vw, GGNewsCtrl& controller);
	~GGNewsTimerObserver();
	virtual void Update() override;
private:
	GGView& view;
	GGNewsCtrl& ctrl;
	sf::Time currentTime;
};

class GGPumpTimerObserver : public GGAbstractObserver
{
public:
	GGPumpTimerObserver(GGView& vw, GGPumpCtrl& controller);
	~GGPumpTimerObserver();
	virtual void Update() override;
private:
	GGView& view;
	GGPumpCtrl& ctrl;
	sf::Time currentTime;
};
class GGStageTransitionTickObserver : public GGAbstractObserver
{
public:
	GGStageTransitionTickObserver(GGView& vw, GGStageTransitionCtrl& controller, sf::Time dt);
	~GGStageTransitionTickObserver();
	virtual void Update() override;
private:
	GGView& view;
	GGStageTransitionCtrl& ctrl;
	sf::Time currentTime;
	sf::Time deltaT;
};

class GGStageTransitionClickObserver : public GGAbstractObserver
{
public:
	GGStageTransitionClickObserver(GGView& vw, GGStageTransitionCtrl& controller);
	~GGStageTransitionClickObserver();
	virtual void Update() override;
private:
	GGView& view;
	GGStageTransitionCtrl& ctrl;
	bool clickSwitch = false;
private:
};
class GGTestGameOverTick : public GGAbstractObserver {
public:
	GGTestGameOverTick(GGView& vw, GGTestGameOverCtrl& controller);
	~GGTestGameOverTick();
	virtual void Update() override;

private:
	GGView& view;
	GGTestGameOverCtrl& ctrl;
	sf::Time deltaT;
	sf::Time currentTime;

};

class GGEndGameObserver : public GGAbstractObserver {
public:
	GGEndGameObserver(GGView& vw, GGPumpCtrl& controller);
	~GGEndGameObserver();
	virtual void Update() override;

private:
	GGView& view;
	GGPumpCtrl& ctrl;
};

class GGRestartGameObserver : public GGAbstractObserver {
public:
	GGRestartGameObserver(GGView& vw, GGTestGameOverCtrl& controller);
	~GGRestartGameObserver();
	virtual void Update() override;

private:
	GGView& view;
	GGTestGameOverCtrl& ctrl;
};
#endif