#include "GGAbstractCtrl.h"
#define DEBUG 0
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif
GGAbstractCtrl::GGAbstractCtrl() {}
GGAbstractCtrl::~GGAbstractCtrl() {
}
void GGAbstractCtrl::ResetMdl() {
	GetModel()->ResetData();
}
GGPumpCtrl::GGPumpCtrl() {

}
GGPumpCtrl::~GGPumpCtrl() {}
GGAbstractModel* GGPumpCtrl::GetModel() {
	return &pumpMdl;
}
void GGPumpCtrl::AnimatePump() {
	pumpMdl.GetPump()->NextAnimation();
	if (pumpMdl.GetPump()->AnimationCompleted()) {
		pumpMdl.SetNumPumps(pumpMdl.GetNumPumps() - 1);
	}
}

void GGPumpCtrl::AnimateOil()
{
	pumpMdl.GetOil()->NextAnimation();
}
void GGPumpCtrl::PumpClicked() {
	if (pumpMdl.GetTransition()->GetDrawing())
	{
		pumpMdl.GetTransition()->SetDrawing(false);
		pumpMdl.GetTimer()->StartTimer();
		return;
	}
	pumpMdl.SetNumPumps(pumpMdl.GetNumPumps() + 1);
	pumpMdl.IncrementPumps();
	if (pumpMdl.PumpMaxReached())
	{
		pumpMdl.GetOil()->SetStart(true);
	}
}

void GGPumpCtrl::CheckGameWon()
{
	if (pumpMdl.PumpMaxReached() && pumpMdl.GetOil()->CheckFinishedAnimating())
	{
		WinGame();
	}
}
bool GGPumpCtrl::IsAnimatingPump() {
	return pumpMdl.GetNumPumps() > 0;
}


void GGPumpCtrl::EndGame() {
	pumpMdl.SetSuccess(false);
	pumpMdl.SetContinueGame(false);
}

void GGPumpCtrl::WinGame()
{
	pumpMdl.SetSuccess(true);
	pumpMdl.SetContinueGame(false);
}
int GGPumpCtrl::GetQueuedPumps()
{
	return pumpMdl.GetNumPumps();
}

bool GGPumpCtrl::TimerTick()
{
	if (!pumpMdl.GetTimer()->GetTimerStarted()) return false;
	pumpMdl.GetTimer()->TickMS();
	return pumpMdl.GetTimer()->TimerCompleted();
}

bool GGPumpCtrl::TimerCompleted()
{
	return pumpMdl.GetTimer()->TimerCompleted();
}

GGNewsCtrl::GGNewsCtrl() : newsMdl(10)
{
	GenerateQuestion();
}

GGNewsCtrl::~GGNewsCtrl() {}

GGAbstractModel* GGNewsCtrl::GetModel()
{
	return &newsMdl;
}

void GGNewsCtrl::EndGame()
{
	newsMdl.SetContinueGame(false);
	newsMdl.SetSuccess(false);
}

void GGNewsCtrl::WinGame()
{
	newsMdl.SetContinueGame(false);
	newsMdl.SetSuccess(true);
}

bool GGNewsCtrl::IsAnimatingButton()
{
	return (newsMdl.GetButton(0)->GetClicked() || newsMdl.GetButton(1)->GetClicked());
}

void GGNewsCtrl::ClearButtonAnim()
{
	newsMdl.GetButton(0)->SetClicked(false);
	newsMdl.GetButton(0)->SetCurFrame(0);
	newsMdl.GetButton(1)->SetClicked(false);
	newsMdl.GetButton(1)->SetCurFrame(0);
}
void GGNewsCtrl::PressButton(int button)
{
	if (!IsAnimatingButton())
	{
		newsMdl.GetButton(button)->SetClicked(true);
		if (button == goodAnswer)
		{
			newsMdl.SetNumAnswers(newsMdl.GetNumAnswers() + 1);
			newsMdl.GetButton(button)->SetCurFrame(1);
			GenerateQuestion();
		}
		else
		{
			newsMdl.GetButton(button)->SetCurFrame(2);
			newsMdl.SetNumAnswers(newsMdl.GetNumAnswers() - 1);
			GenerateQuestion();
		}
		SetAnimatingMouth(true);
		SetNewClick(true);
	}
	if (newsMdl.GoalMet())
	{
		newsMdl.SetSuccess(true);
		newsMdl.SetContinueGame(false);
	}
}

void GGNewsCtrl::ProcessClick(sf::Vector2f mousePos)
{
	if (newsMdl.GetTransition()->GetDrawing())
	{
		newsMdl.GetTransition()->SetDrawing(false);
		newsMdl.GetTimer()->StartTimer();
		return;
	}
	if (newsMdl.GetButton(0)->GetGlobalBounds().contains(mousePos))
	{
		PressButton(0);
	}
	else if (newsMdl.GetButton(1)->GetGlobalBounds().contains(mousePos))
	{
		PressButton(1);
	}
}

void GGNewsCtrl::GenerateQuestion()
{
	newsMdl.PlayVoiceSFX();
	int qNum = rand() % questions.size();
	newsMdl.GetQuestionText()->SetText(questions[qNum]);
	goodAnswer = rand() % 2;
	if (goodAnswer == 1)
	{
		newsMdl.GetButton(0)->SetText(answers[2 * qNum]);
		newsMdl.GetButton(1)->SetText(answers[2 * qNum + 1]);
	}
	else
	{
		newsMdl.GetButton(1)->SetText(answers[2 * qNum]);
		newsMdl.GetButton(0)->SetText(answers[2 * qNum + 1]);
	}
}

bool GGNewsCtrl::TimerTick() {
	if (!newsMdl.GetTimer()->GetTimerStarted()) return false;
	newsMdl.GetTimer()->TickMS();
	return newsMdl.GetTimer()->TimerCompleted();
}

bool GGNewsCtrl::TimerCompleted()
{
	return newsMdl.GetTimer()->TimerCompleted();
}
void GGNewsCtrl::ChangeMouth()
{
	newsMdl.ChangeMouth();
}
void GGNewsCtrl::ResetMouth()
{
	newsMdl.ResetMouth();
}
bool GGNewsCtrl::IsAnimatingMouth()
{
	return isAnimatingMouth;
}
void GGNewsCtrl::SetAnimatingMouth(bool val)
{
	isAnimatingMouth = val;
	if (val)
	{
		ChangeMouth();
	}
	else
	{
		ResetMouth();
	}
}
bool GGNewsCtrl::GetNewClick()
{
	return newClick;
}
void GGNewsCtrl::SetNewClick(bool click)
{
	newClick = click;
}
GGStageTransitionCtrl::GGStageTransitionCtrl() : transMdl()
{
	transMdl.SetEnvelopeVelocity(initialEnvelopeVelocity);
}

GGStageTransitionCtrl::~GGStageTransitionCtrl()
{

}

GGAbstractModel* GGStageTransitionCtrl::GetModel()
{
	return &transMdl;
}

void GGStageTransitionCtrl::WinGame()
{
	transMdl.SetContinueGame(false);
	transMdl.SetSuccess(true);
}

bool GGStageTransitionCtrl::IsEnvelopeMoving()
{
	return (transMdl.GetEnvelopeVelocity() != 0);
}

bool GGStageTransitionCtrl::IsLetterMoving()
{
	return (transMdl.GetLetterVelocity() != 0);
}

bool GGStageTransitionCtrl::HasLetterMoved()
{
	return transMdl.GetLetterMoved();
}

void GGStageTransitionCtrl::MoveLetter()
{
	if (!IsLetterMoving())
	{
		transMdl.SetLetterVelocity(initialLetterVelocity);
		transMdl.PlayLetterSound();
		return;
	}
	transMdl.GetLetter()->SetPos(sf::Vector2f(transMdl.GetLetter()->GetPos().x, transMdl.GetLetter()->GetPos().y + transMdl.GetLetterVelocity()));
	transMdl.SetLetterVelocity(transMdl.GetLetterVelocity() + transMdl.GetLetterDeceleration());
	if (transMdl.GetLetterVelocity() >= 0)
	{
		transMdl.SetLetterVelocity(0);
		transMdl.SetLetterMoved(true);
	}
}

void GGStageTransitionCtrl::MoveEnvelope()
{
	transMdl.GetEnvelope()->SetPos(sf::Vector2f(transMdl.GetEnvelope()->GetPos().x, transMdl.GetEnvelope()->GetPos().y + transMdl.GetEnvelopeVelocity()));
	transMdl.SetEnvelopeVelocity(transMdl.GetEnvelopeVelocity() + transMdl.GetEnvelopeDeceleration());
	if (transMdl.GetEnvelopeVelocity() <= 0)
	{
		transMdl.SetEnvelopeVelocity(0);
	}
}



GGTestGameOverCtrl::GGTestGameOverCtrl() {}
GGTestGameOverCtrl::~GGTestGameOverCtrl() {}
GGAbstractModel* GGTestGameOverCtrl::GetModel() {
	return &gOMdl;
}
void GGTestGameOverCtrl::AnimateScreen() {
	gOMdl.GetGameOverAsset()->NextAnimation();
}
void GGTestGameOverCtrl::RestartGame() {
	gOMdl.SetContinueGame(false);
	gOMdl.SetSuccess(true);

}