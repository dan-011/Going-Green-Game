#ifndef __GGABSTRACTMODEL_H
#define __GGABSTRACTMODEL_H

#include "GGAbstractAsset.h"
#include <vector>

class GGAbstractModel {
public:
	GGAbstractModel();
	virtual ~GGAbstractModel();
	std::vector<GGAbstractAsset*>& GetAssets();
	void AddAsset(GGAbstractAsset* asset);
	void InsertAsset(GGAbstractAsset* asset, int index);
	void RemoveAsset(int index);
	int GetNumAssets();
	bool GetContinueGame();
	void SetContinueGame(bool isContinuing);
	bool GetSuccess();
	void SetSuccess(bool success);
	virtual void ResetData() = 0;
	virtual GGTimerAsset* GetTimer();

private:
	std::vector<GGAbstractAsset*> assets;
	bool continueGame;
	bool wasSuccess;
	GGTimerAsset timer;
};

class GGPumpModel : public GGAbstractModel {
public:
	GGPumpModel();
	virtual ~GGPumpModel();
	GGSheetAsset* GetPump();
	int GetNumPumps();
	void SetNumPumps(int nPumps);
	virtual void ResetData() override;

private:
	GGSheetAsset* pump; // change to object
	int maxPumps;
	int numPumps;
	bool maxedOut;
};

class GGTestGameOverModel : public GGAbstractModel {
public:
	GGTestGameOverModel();
	~GGTestGameOverModel();
	GGListAsset* GetGameOverAsset();
	virtual void ResetData() override;

private:
	GGListAsset* gameOverScreen; // change to object
};

enum GGPROJECTILE_STATUS {
	LOADED,
	FIRED,
	LANDED
};

class GGCannonGameModel : public GGAbstractModel {
public:
	GGCannonGameModel();
	~GGCannonGameModel();
	GGSheetAsset* GetCannonAsset();
	virtual void ResetData() override;
	void SetCannonFiring(bool isCannonFiring);
	bool GetCannonFiring();
	float GetCannonAngle();
	void SetCannonAngle(float angle);
	GGStaticAsset* GetProjectile(int index);
	GGSheetAsset* GetTarget(int index);
	int GetNumProjectiles();
	int GetNumTargets();
	float GetCannonLength();
	void MakeProjectileVisible(int index);
	void UpdateAmmunitionCount(int amt);
	sf::Vector2f GetVelocity(int index);
	void SetVelocity(int index, sf::Vector2f vel);
	GGPROJECTILE_STATUS GetProjectileStatus(int index);
	void SetProjectileStatus(int index, GGPROJECTILE_STATUS status);
	bool GetTargetHitStatus(int index);
	void SetTargetHitStatus(int index, bool status);
	int GetProjectileDelay(int index);
	int GetCurProjectileAsset();
	void SetCurProjectileAsset(int index);
	int TargetWaitTick(int index);

private:
	GGSheetAsset cannonAsset;
	GGStaticAsset backgroundAsset;
	std::vector<GGStaticAsset*> moneyAssets;
	std::vector<GGSheetAsset*> targetAssets;
	GGStaticAsset moneyAssetIcon;
	GGTextAsset ammunitionCountAsset;
	bool cannonFiring;
	float cannonAngle;
	std::vector<int> targetWaitTicks;
	std::vector<sf::Vector2f> velocities;
	std::vector<GGPROJECTILE_STATUS> projectileStatuses;
	std::vector<bool> targetHitStatuses;
	std::vector<int> projectileDelays;
	bool first;
	int curProjectileAsset;
};

#endif