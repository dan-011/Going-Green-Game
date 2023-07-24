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

GGNewsCtrl::GGNewsCtrl() : newsMdl(10)
{

}

GGNewsCtrl::~GGNewsCtrl() {}

GGAbstractModel* GGNewsCtrl::GetModel()
{
	return &newsMdl;
}

void GGNewsCtrl::EndGame()
{
	newsMdl.SetContinueGame(true);
	newsMdl.SetSuccess(false);
}

void GGNewsCtrl::WinGame()
{
	newsMdl.SetContinueGame(true);
	newsMdl.SetSuccess(true);
}

bool GGNewsCtrl::IsAnimatingButton()
{
	return (newsMdl.GetButton(0)->GetClicked() || newsMdl.GetButton(1)->GetClicked());
}

void GGNewsCtrl::ClearButtonAnim()
{
	newsMdl.GetButton(0)->SetClicked(false);
	newsMdl.GetButton(1)->SetClicked(false);
}
void GGNewsCtrl::PressButton(int button)
{
	if (!IsAnimatingButton())
		newsMdl.GetButton(button)->SetClicked(true);
}

void GGNewsCtrl::ProcessClick(sf::Vector2f mousePos)
{
	if (newsMdl.GetButton(0)->GetRect().getGlobalBounds().contains(mousePos))
	{
		cout << "button 1 click" << endl;
	}
	else if (newsMdl.GetButton(1)->GetRect().getGlobalBounds().contains(mousePos))
	{
		cout << "button 2 click" << endl;
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