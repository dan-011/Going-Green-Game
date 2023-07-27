#ifndef __GGABSTRACTCTRL_H
#define __GGABSTRACTCTRL_H

#include "GGAbstractModel.h"
#include <cmath>
#include <stdlib.h>

class GGAbstractCtrl {
public:
	GGAbstractCtrl();
	virtual ~GGAbstractCtrl();
	virtual GGAbstractModel* GetModel() = 0;
	virtual void ResetMdl();
	virtual bool TimerTick();
};

class GGGameOverCtrl : public GGAbstractCtrl {
public:
	GGGameOverCtrl();
	~GGGameOverCtrl();
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
	void ProjectileTick(sf::Time deltaT, int index);
	// virtual void EndGame();
	bool ProjectileFired(int index);
	bool ProjectileFinised(int index);
	bool TargetHit(int index);
	void TargetTick(int index);
	sf::Time GetTargetDeltaT();

private:
	GGCannonGameModel cannonMdl;
	const sf::Vector2f gravity;
	sf::Vector2f projectileAnchorPoint;

};
#endif
