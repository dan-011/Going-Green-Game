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
	sf::Time currentTime;
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
	GGProjectileTickObserver(GGView& vw, GGCannonGameCtrl& controller, int index);
	~GGProjectileTickObserver();
	virtual void Update() override;

private:
	GGView& view;
	GGCannonGameCtrl& ctrl;
	sf::Time deltaT;
	sf::Time currentTime;
	int projectileIndex;
};

class GGTargetTickObserver : public GGAbstractObserver {
public:
	GGTargetTickObserver(GGView& vw, GGCannonGameCtrl& controller, int index);
	~GGTargetTickObserver();
	virtual void Update() override;

private:
	GGView& view;
	GGCannonGameCtrl& ctrl;
	sf::Time deltaT;
	sf::Time currentTime;
	int targetIndex;
};
#endif