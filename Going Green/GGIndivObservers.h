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

class GGClockMSObserver : public GGAbstractObserver {
public:
	GGClockMSObserver(GGView& vw, GGAbstractCtrl& controller);
	~GGClockMSObserver();
	virtual void Update() override;

private:
	GGView& view;
	GGAbstractCtrl& ctrl;
	sf::Time deltaT;
	sf::Time currentTime;
};

class GGCannonFireObserver : public GGAbstractObserver {
public:
	GGCannonFireObserver(GGView& vw, GGCannonGameCtrl& controller);
	~GGCannonFireObserver();
	virtual void Update() override;

private:
	GGView& view;
	GGCannonGameCtrl& ctrl;
};

class GGCannonTickObserver : public GGAbstractObserver {
public:
	GGCannonTickObserver(GGView& vw, GGCannonGameCtrl& controller);
	~GGCannonTickObserver();
	virtual void Update() override;

private:
	GGView& view;
	GGCannonGameCtrl& ctrl;
	sf::Time deltaT;
	sf::Time currentTime;
};

class GGCannonMoveObserver : public GGAbstractObserver {
public:
	GGCannonMoveObserver(GGView& vw, GGCannonGameCtrl& controller);
	~GGCannonMoveObserver();
	virtual void Update() override;

private:
	GGView& view;
	GGCannonGameCtrl& ctrl;
};

class GGProjectileTickObserver : public GGAbstractObserver {
public:
	GGProjectileTickObserver(GGView& vw, GGCannonGameCtrl& controller, int index, int stg);
	~GGProjectileTickObserver();
	virtual void Update() override;

private:
	GGView& view;
	GGCannonGameCtrl& ctrl;
	sf::Time deltaT;
	sf::Time currentTime;
	int projectileIndex;
	int stage;
};

class GGTargetTickObserver : public GGAbstractObserver {
public:
	GGTargetTickObserver(GGView& vw, GGCannonGameCtrl& controller, int index, int stg);
	~GGTargetTickObserver();
	virtual void Update() override;

private:
	GGView& view;
	GGCannonGameCtrl& ctrl;
	sf::Time currentTime;
	int targetIndex;
	int stage;
};

class GGStageFourSwitchObserver : public GGAbstractObserver {
public:
	GGStageFourSwitchObserver(GGView& vw, GGStageFourCtrl& controller);
	~GGStageFourSwitchObserver();
	virtual void Update() override;

private:
	GGView& view;
	GGStageFourCtrl& ctrl;
	sf::Time deltaT;
	sf::Time currentTime;
};

class GGContinueGameObserver : public GGAbstractObserver {
public:
	GGContinueGameObserver(GGView& vw, GGBookendsCtrl& controller, sf::Keyboard::Key continueKey);
	~GGContinueGameObserver();
	virtual void Update() override;

private:
	GGView& view;
	GGBookendsCtrl& ctrl;
	sf::Keyboard::Key key;
};

class GGBookendsTextTickObserver : public GGAbstractObserver {
public:
	GGBookendsTextTickObserver(GGView& vw, GGBookendsCtrl& controller);
	~GGBookendsTextTickObserver();
	virtual void Update() override;

private:
	GGView& view;
	GGBookendsCtrl& ctrl;
	sf::Time deltaT;
	sf::Time currentTime;
};

class GGRollCreditsObserver : public GGAbstractObserver {
public:
	GGRollCreditsObserver(GGView& vw, GGStageFourCtrl& controller);
	~GGRollCreditsObserver();
	virtual void Update() override;

private:
	GGView& view;
	GGStageFourCtrl& ctrl;
	sf::Time deltaT;
	sf::Time currentTime;
};

class GGTransitionExitObserver : public GGAbstractObserver {
public:
	GGTransitionExitObserver(GGView& vw, GGAbstractCtrl& controller);
	~GGTransitionExitObserver();
	virtual void Update() override;

private:
	GGView& view;
	GGAbstractCtrl& ctrl;
	sf::Time waitTime;
};
#endif