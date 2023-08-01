#ifndef __GGABSTRACTCTRL_H
#define __GGABSTRACTCTRL_H

#include "GGAbstractModel.h"

class GGAbstractCtrl {
public:
	GGAbstractCtrl();
	virtual ~GGAbstractCtrl();
	virtual GGAbstractModel* GetModel() = 0;
	virtual void ResetMdl();
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
private:
	GGNewsModel newsMdl;
	int numAnswers;
	int goodAnswer;
	std::vector<std::string> questions = { "Experts say that ___ can be blamed for recent climate change", "We need to take action against climate change or things will be ___", "Recent effects of oil usage deemed ___ for the environment", "Natural habitats are being ___ by industry action"};
	std::vector<std::string> answers = { "Industry", "People", "Awful", "Fine", "Bad", "Good", "Damaged", "Helped" };
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
	float initialLetterVelocity = -11.4;
	float initialEnvelopeVelocity = 9.5;
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

#endif
