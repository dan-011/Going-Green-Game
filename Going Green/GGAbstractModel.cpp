#include "GGAbstractModel.h"
#define DEBUG 0
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif
GGAbstractModel::GGAbstractModel() : continueGame(true), wasSuccess(true) {}
GGAbstractModel::~GGAbstractModel() {}
std::vector<GGAbstractAsset*>& GGAbstractModel::GetAssets() {
	return assets;
}
void GGAbstractModel::AddAsset(GGAbstractAsset* asset) {
	assets.push_back(asset);
}

bool GGAbstractModel::GetContinueGame() {
	return continueGame;
}
void GGAbstractModel::SetContinueGame(bool isContinuing) {
	continueGame = isContinuing;
}
bool GGAbstractModel::GetSuccess() {
	return wasSuccess;
}
void GGAbstractModel::SetSuccess(bool success) {
	wasSuccess = success;
}

GGPumpModel::GGPumpModel() : pump(new GGSheetAsset(sf::Vector2f(500, 500), "Assets/Animations/oil_game/oil_drill_sprite_sheet.png", sf::Vector2u(4, 3))), maxPumps(10), numPumps(0), maxedOut(false) {
	AddAsset(pump);
}
GGPumpModel::~GGPumpModel() {
	delete pump;
}
GGSheetAsset* GGPumpModel::GetPump() {
	return pump;
}
int GGPumpModel::GetNumPumps() {
	return numPumps;
}
void GGPumpModel::SetNumPumps(int nPumps) {
	if (maxedOut) return; // continue
	if (nPumps > maxPumps) {
		maxedOut = true;
		numPumps = maxPumps;
	}
	else {
		numPumps = nPumps;
	}
}
void GGPumpModel::ResetData() {
	numPumps = 0;
	SetContinueGame(true);
	SetSuccess(true);
	pump->SetCurFrame(0);
	maxedOut = false;
}

GGTestGameOverModel::GGTestGameOverModel() : gameOverScreen(new GGListAsset(sf::Vector2f(400, 400), vector<std::string> {
	"Assets/Animations/test_game_over/frame0.png",
	"Assets/Animations/test_game_over/frame1.png",
	"Assets/Animations/test_game_over/frame2.png",
	"Assets/Animations/test_game_over/frame3.png",
	"Assets/Animations/test_game_over/frame4.png",
	"Assets/Animations/test_game_over/frame5.png",
	"Assets/Animations/test_game_over/frame6.png",
	"Assets/Animations/test_game_over/frame7.png",
	"Assets/Animations/test_game_over/frame8.png",
	"Assets/Animations/test_game_over/frame9.png",
	"Assets/Animations/test_game_over/frame10.png",
	"Assets/Animations/test_game_over/frame11.png",
	"Assets/Animations/test_game_over/frame12.png",
	"Assets/Animations/test_game_over/frame13.png",
	"Assets/Animations/test_game_over/frame14.png"
})){
	AddAsset(gameOverScreen);
}
GGTestGameOverModel::~GGTestGameOverModel() {
	delete gameOverScreen;
}
GGListAsset* GGTestGameOverModel::GetGameOverAsset() {
	return gameOverScreen;
}
void GGTestGameOverModel::ResetData() {
	SetContinueGame(true);
	SetSuccess(true);
	gameOverScreen->SetCurFrame(0);
}