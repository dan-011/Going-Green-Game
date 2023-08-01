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
	virtual void AssignBackgroundMusic(std::string fileName, bool repeat = true);
	int GetStage();
	void SetStage(int stg);
	virtual void StageOne() = 0;
	virtual void StageTwo() = 0;
	virtual void StageThree() = 0;
	bool GetClickSwitch();
	void SetClickSwitch(bool clckSwtch);

private:
	std::vector<GGAbstractAsset*> assets;
	bool continueGame;
	bool wasSuccess;
	GGTimerAsset timer;
	GGMusicAsset* backgroundMusic;
	int stage;
	bool clickSwitch;
};

class GGPumpModel : public GGAbstractModel {
public:
	GGPumpModel();
	virtual ~GGPumpModel();
	GGSheetAsset* GetPump();
	GGSheetAsset* GetOil();
	GGMinigameTransition* GetTransition();
	int GetNumPumps();
	void SetNumPumps(int nPumps);
	virtual void ResetData() override;
	bool PumpMaxReached();
	void IncrementPumps();
	GGTimerAsset* GetTimer();
	virtual void StageOne() override;
	virtual void StageTwo() override;
	virtual void StageThree() override;
private:
	GGSheetAsset* pump; // change to object
	GGSheetAsset* oil;
	GGMinigameTransition* transition;
	GGStaticAsset* background;
	int maxPumps;
	int numPumps;
	int goalPumps;
	int totalPumps;
	bool maxedOut;
	GGTimerAsset* timer;
};

class GGNewsModel : public GGAbstractModel {
public:
	GGNewsModel(int maxReports);
	virtual ~GGNewsModel();
	GGButton* GetButton(int index);
	GGTextAsset* GetQuestionText();
	int GetNumAnswers();
	void SetNumAnswers(int nAnswers);
	bool GoalMet();
	void ResetData();
	GGMinigameTransition* GetTransition();
	GGTimerAsset* GetTimer();
	void ChangeMouth();
	void ResetMouth();
	virtual void StageOne() override;
	virtual void StageTwo() override;
	virtual void StageThree() override;
	void PlayVoiceSFX();
	void StopAllVoices();
private:
	GGButton* button1;
	GGButton* button2;
	GGMinigameTransition* transition;
	GGStaticAsset* background;
	GGStaticAsset* frame;
	GGStaticAsset* questionBubble;
	GGStaticAsset* reporter;
	GGTextAsset* questionText;
	GGSheetAsset* mouth;
	int goalReports;
	int numReports;
	GGTimerAsset* timer;
	std::vector<GGSFXAsset*> voicelines;
	int currentSound;
};

class GGStageTransitionModel : public GGAbstractModel
{
public:
	GGStageTransitionModel();
	virtual ~GGStageTransitionModel();
	GGStaticAsset* GetEnvelope();
	GGStaticAsset* GetLetter();
	bool GetLetterMoved();
	void SetLetterMoved(bool moved);
	float GetLetterVelocity();
	void SetLetterVelocity(float velocity);
	float GetLetterDeceleration();
	float GetEnvelopeVelocity();
	void SetEnvelopeVelocity(float velocity);
	float GetEnvelopeDeceleration();
	void ResetData() override;
	void PlayLetterSound();
	virtual void StageOne() override;
	virtual void StageTwo() override;
	virtual void StageThree() override;
private:
	GGStaticAsset* table;
	GGStaticAsset* envelope;
	GGStaticAsset* letter;
	GGSFXAsset* crinkle;
	float letterVelocity;
	const float letterDeceleration;
	float envelopeVelocity;
	const float envelopeDeceleration;
	bool letterMoved;
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
	GGMinigameTransition* GetTransition();
	bool GetGameStarted();
	void SetGameStarted(bool startGame);

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
	GGMinigameTransition transitionAsset;
	bool gameStarted;
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

class GGBookendsModel : public GGAbstractModel {
public:
	virtual ~GGBookendsModel();
	virtual void SetTextVisibility(bool isVisible) = 0;
	virtual bool GetTextVisibility() = 0;
};

class GGTitleScreenModel : public GGBookendsModel {
public:
	GGTitleScreenModel();
	~GGTitleScreenModel();
	virtual void StageOne() override;
	virtual void StageTwo() override;
	virtual void StageThree() override;
	virtual void SetTextVisibility(bool isVisible) override;
	virtual bool GetTextVisibility() override;

private:
	GGStaticAsset background;
	GGTextAsset pressStartText;
};

class GGGameOverModel : public GGBookendsModel {
public:
	GGGameOverModel();
	~GGGameOverModel();
	GGStaticAsset* GetGameOverAsset();
	virtual void StageOne() override;
	virtual void StageTwo() override;
	virtual void StageThree() override;
	virtual void SetTextVisibility(bool isVisible) override;
	virtual bool GetTextVisibility() override;

private:
	GGStaticAsset* gameOverScreen; // change to object
	GGTextAsset gameOverText;
	GGTextAsset restartGameText;
};

class GGSecretEndingModel : public GGAbstractModel {
public:
	GGSecretEndingModel();
	~GGSecretEndingModel();
	virtual void StageOne() override;
	virtual void StageTwo() override;
	virtual void StageThree() override;

private:
	GGStaticAsset backgroundAsset;
};
#endif