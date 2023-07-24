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
	GGStaticAsset* GetProjectile();
	float GetCannonLength();

private:
	GGSheetAsset cannonAsset;
	GGStaticAsset backgroundAsset;
	GGStaticAsset moneyAsset;
	bool cannonFiring;
	float cannonAngle;
};

#endif