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

GGPumpModel::GGPumpModel() : pump(new GGSheetAsset(sf::Vector2f(650, 292), "Assets/Animations/oil_game/oil_drill_sprite_sheet.png", sf::Vector2u(4, 3))), maxPumps(10), numPumps(0), maxedOut(false), goalPumps(25), totalPumps(0), oil(new GGSheetAsset(sf::Vector2f(590, 360), "Assets/Animations/oil_game/oil_sprite_sheet.png", sf::Vector2u(3, 3), true, false)),
background(new GGStaticAsset(sf::Vector2f(640, 360), "Assets/Animations/oil_game/oil_minigame_background.png")), transition(new GGMinigameTransition("Drill!", "Click as fast as you can!")) {
	AddAsset(background);
	AddAsset(oil);
	AddAsset(pump);
	AddAsset(transition);
	background->Scale(sf::Vector2f(4, 4));
	pump->Scale(sf::Vector2f(4, 4));
	oil->Scale(sf::Vector2f(16, 16));
}
GGPumpModel::~GGPumpModel() {
	delete pump;
	delete oil;
	delete background;
	delete transition;
}
GGSheetAsset* GGPumpModel::GetPump() {
	return pump;
}

GGSheetAsset* GGPumpModel::GetOil()
{
	return oil;
}

GGMinigameTransition* GGPumpModel::GetTransition()
{
	return transition;
}
int GGPumpModel::GetNumPumps() {
	return numPumps;
}
void GGPumpModel::SetNumPumps(int nPumps) {
	if (maxedOut) return; // continue
	if (nPumps >= maxPumps) {
		maxedOut = true;
		numPumps = maxPumps;
	}
	else {
		numPumps = nPumps;
	}
}
void GGPumpModel::IncrementPumps()
{
	totalPumps++;
}
bool GGPumpModel::PumpMaxReached()
{
	return (totalPumps >= goalPumps);
}
void GGPumpModel::ResetData() {
	numPumps = 0;
	SetContinueGame(true);
	SetSuccess(true);
	pump->SetCurFrame(0);
	maxedOut = false;
	totalPumps = 0;
	transition->SetDrawing(true);
	oil->SetFinishedAnimating(false);
	oil->SetStart(false);
}

GGNewsModel::GGNewsModel(int maxReports) : goalReports(maxReports), numReports(0)
{
	button1 = new GGButton(sf::Vector2f(200, 300), "INCREDI");
	button2 = new GGButton(sf::Vector2f(400, 300), "MISLEAD");
	AddAsset(button1);
	AddAsset(button2);
}

GGNewsModel::~GGNewsModel()
{
	delete(button1);
	delete(button2);
}

GGButton* GGNewsModel::GetButton(int index)
{
	if (index == 0)
	{
		return button1;
	}
	else
		return button2;
}

void GGNewsModel::ResetData()
{
	numReports = 0;
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