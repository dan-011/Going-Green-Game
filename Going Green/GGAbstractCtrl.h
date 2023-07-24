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


enum GGPROJECTILE_STATUS {
	LOADED,
	FIRED,
	LANDED
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

private:
	GGCannonGameModel cannonMdl;
	std::vector<sf::Vector2f> velocities;
	std::vector<GGPROJECTILE_STATUS> projectileStatuses;
	std::vector<int> projectileDelays;
	const sf::Vector2f gravity;
	sf::Vector2f projectileAnchorPoint;
	int curProjectileAsset;

};
#endif
