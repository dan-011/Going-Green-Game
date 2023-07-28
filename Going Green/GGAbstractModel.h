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
	virtual void ResetData();
	virtual GGTimerAsset* GetTimer();
	virtual GGMusicAsset* GetBackgroundMusic();
	virtual void AssignBackgroundMusic(std::string fileName);
	int GetStage();
	void SetStage(int stg);
	virtual void StageOne() = 0;
	virtual void StageTwo() = 0;
	virtual void StageThree() = 0;

private:
	std::vector<GGAbstractAsset*> assets;
	bool continueGame;
	bool wasSuccess;
	GGTimerAsset timer;
	GGMusicAsset* backgroundMusic;
	int stage;
};

class GGGameOverModel : public GGAbstractModel {
public:
	GGGameOverModel();
	~GGGameOverModel();
	GGStaticAsset* GetGameOverAsset();
	virtual void StageOne() override;
	virtual void StageTwo() override;
	virtual void StageThree() override;

private:
	GGStaticAsset* gameOverScreen; // change to object
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
	GGSFXAsset* GetCannonSound();
	sf::Time GetTagetSpeed();
	virtual void StageOne() override;
	virtual void StageTwo() override;
	virtual void StageThree() override;
	int GetHitCount();
	void IncrementHitCount();

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
	GGSFXAsset cannonSound;
	int totalProjectiles;
	int totalTargets;
	sf::Time targetSpeed;
	int hitCount;
};

class GGStageFourModel : public GGAbstractModel {
public:
	GGStageFourModel();
	~GGStageFourModel();
	int GetScreenNumber();
	void NextScreen();
	virtual void ResetData() override;
	virtual void StageOne() override;
	virtual void StageTwo() override;
	virtual void StageThree() override;

private:
	std::vector<std::string> screenFileNames;
	int screenIndex;
	GGStaticAsset background;
};

class GGTitleScreenModel : public GGAbstractModel {
public:
	GGTitleScreenModel();
	~GGTitleScreenModel();
	virtual void StageOne() override;
	virtual void StageTwo() override;
	virtual void StageThree() override;
	void SetTextVisibility(bool isVisible);
	bool GetTextVisibility();

private:
	GGStaticAsset background;
	GGTextAsset pressStartText;
};
#endif