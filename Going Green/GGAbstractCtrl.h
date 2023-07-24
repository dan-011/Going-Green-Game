#ifndef __GGABSTRACTCTRL_H
#define __GGABSTRACTCTRL_H

#include "GGAbstractModel.h"
#include <cmath>

class GGAbstractCtrl {
public:
	GGAbstractCtrl();
	virtual ~GGAbstractCtrl();
	virtual GGAbstractModel* GetModel() = 0;
	virtual void ResetMdl();
	virtual bool TimerTick();
};

class GGPumpCtrl : public GGAbstractCtrl {
public:
	GGPumpCtrl();
	virtual ~GGPumpCtrl();
	virtual GGAbstractModel* GetModel() override;
	virtual void AnimatePump();
	virtual void PumpClicked();
	virtual bool IsAnimatingPump();
	virtual void EndGame();

private:
	GGPumpModel pumpMdl;

};

class GGTestGameOverCtrl : public GGAbstractCtrl {
public:
	GGTestGameOverCtrl();
	~GGTestGameOverCtrl();
	virtual GGAbstractModel* GetModel() override;
	virtual void AnimateScreen();
	virtual void RestartGame();

private:
	GGTestGameOverModel gOMdl;
};

class GGCannonGameCtrl : public GGAbstractCtrl {
public:
	GGCannonGameCtrl();
	~GGCannonGameCtrl();
	virtual GGAbstractModel* GetModel() override;
	void FireCannon(sf::Vector2i mousePos);
	void AnimateCannonFire();
	bool IsCannonFiring();
	void ChangeCannonAngle(sf::Vector2i mousePos);
	void ProjectileTick(sf::Time deltaT);
	// virtual void EndGame();

	bool ProjectileFinised(); // temp
	bool hasFired = false; // REMOVE
private:
	GGCannonGameModel cannonMdl;
	sf::Vector2f velocity;
	const sf::Vector2f gravity;
	int fireDelayCount;
};
#endif
