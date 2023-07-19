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
	pumpMdl.SetNumPumps(pumpMdl.GetNumPumps() + 1);
	pumpMdl.IncrementPumps();
	if (pumpMdl.PumpMaxReached())
	{
		pumpMdl.GetOil()->Start();
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