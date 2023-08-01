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
	bool GetClickSwitch();
	void SetClickSwitch(bool clckSwtch);
	virtual void RemoveTransition();
};

class GGPumpCtrl : public GGAbstractCtrl {
public:
	GGPumpCtrl();
	virtual ~GGPumpCtrl();
	virtual GGAbstractModel* GetModel() override;
	virtual void AnimatePump();
	virtual void AnimateOil();
	virtual void PumpClicked();
	virtual bool IsAnimatingPump();
	virtual void CheckGameWon();
	virtual void EndGame();
	virtual void WinGame();
	virtual int GetQueuedPumps();
	virtual bool TimerTick();
	virtual bool TimerCompleted();
	virtual void RemoveTransition() override;

private:
	GGPumpModel pumpMdl;

};

class GGNewsCtrl : public GGAbstractCtrl {
public:
	GGNewsCtrl();
	virtual ~GGNewsCtrl();
	virtual GGAbstractModel* GetModel() override;
	virtual void EndGame();
	virtual void WinGame();
	virtual bool IsAnimatingButton();
	virtual void ClearButtonAnim();
	virtual void PressButton(int button);
	virtual void ProcessClick(sf::Vector2f mousePos);
	virtual void GenerateQuestion();
	virtual bool TimerTick();
	virtual bool TimerCompleted();
	virtual void ChangeMouth();
	virtual void ResetMouth();
	virtual bool IsAnimatingMouth();
	virtual void SetAnimatingMouth(bool val);
	virtual bool GetNewClick();
	virtual void SetNewClick(bool click);
	virtual void RemoveTransition() override;

private:
	GGNewsModel newsMdl;
	int numAnswers;
	int goodAnswer;
	std::vector<std::string> questions = { "Experts say that ___ can be blamed for recent climate change", "If we don't focus on climate change, things will be ___", "Recent effects of oil usage deemed ___ for the environment", "Natural habitats are being ___ by industry action", "Restrictions on our consumption of fossil fuels are ___", "___ are putting in enough effort to save the environment", "Removing funds from company expansion is ___"};
	std::vector<std::string> answers = { "Industry", "People", "Awful", "Fine", "Bad", "Good", "Damaged", "Helped", "Good", "Bad", "People", "Industry", "Fine", "Awful"};
	bool isAnimatingMouth = false;
	bool newClick = false;
};

class GGStageTransitionCtrl : public GGAbstractCtrl
{
public:
	GGStageTransitionCtrl();
	virtual ~GGStageTransitionCtrl();
	virtual GGAbstractModel* GetModel() override;
	virtual void WinGame();
	virtual bool IsEnvelopeMoving();
	virtual bool IsLetterMoving();
	virtual bool HasLetterMoved();
	virtual void MoveLetter();
	virtual void MoveEnvelope();
private:
	GGStageTransitionModel transMdl;
	float initialLetterVelocity = -11.4f;
	float initialEnvelopeVelocity = 9.5f;
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
	bool ProjectileFired(int index);
	bool ProjectileFinised(int index);
	bool TargetHit(int index);
	void TargetTick(int index);
	sf::Time GetTargetDeltaT();
	virtual void RemoveTransition() override;

private:
	GGCannonGameModel cannonMdl;
	const sf::Vector2f gravity;
	sf::Vector2f projectileAnchorPoint;

};

class GGStageFourCtrl : public GGAbstractCtrl {
public:
	GGStageFourCtrl();
	~GGStageFourCtrl();
	virtual GGAbstractModel* GetModel() override;
	void NextGame();
	bool ContinueOntoNext();
	void ShiftCredits();

private:
	GGStageFourModel stageFourModel;
};

class GGBookendsCtrl : public GGAbstractCtrl {
public:
	GGBookendsCtrl(GGBookendsModel* bookendMdl);
	~GGBookendsCtrl();
	virtual GGAbstractModel* GetModel() override;
	void Continue();
	void SwitchTextVisibility();

private:
	GGBookendsModel* bookendModel;
};

class GGSecretEndingCtrl : public GGAbstractCtrl {
public:
	GGSecretEndingCtrl();
	~GGSecretEndingCtrl();
	virtual GGAbstractModel* GetModel() override;

private:
	GGSecretEndingModel secretEndingModel;
};

#endif
