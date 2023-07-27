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

class GGTestGameOverTick : public GGAbstractObserver {
public:
	GGTestGameOverTick(GGView& vw, GGGameOverCtrl& controller);
	~GGTestGameOverTick();
	virtual void Update() override;

private:
	GGView& view;
	GGGameOverCtrl& ctrl;
	sf::Time deltaT;
	sf::Time currentTime;

};

class GGRestartGameObserver : public GGAbstractObserver {
public:
	GGRestartGameObserver(GGView& vw, GGGameOverCtrl& controller);
	~GGRestartGameObserver();
	virtual void Update() override;

private:
	GGView& view;
	GGGameOverCtrl& ctrl;
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
	bool clickSwitch;
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

class GGExitTitleScreenObserver : public GGAbstractObserver {
public:
	GGExitTitleScreenObserver(GGView& vw, GGTitleScreenCtrl& controller);
	~GGExitTitleScreenObserver();
	virtual void Update() override;

private:
	GGView& view;
	GGTitleScreenCtrl& ctrl;
};
#endif