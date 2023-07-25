#include "GGAbstractModel.h"
#include <cmath>
#define DEBUG 0
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif
GGAbstractModel::GGAbstractModel() : continueGame(true), wasSuccess(true), timer(sf::Vector2f(0, 0), 50, "Assets/Fonts/Minimal5x7.ttf", 0, 0, sf::Color::White) {}
GGAbstractModel::~GGAbstractModel() {}
std::vector<GGAbstractAsset*>& GGAbstractModel::GetAssets() {
	return assets;
}
void GGAbstractModel::AddAsset(GGAbstractAsset* asset) {
	assets.push_back(asset);
}
void GGAbstractModel::InsertAsset(GGAbstractAsset* asset, int index) {
	assets.insert(assets.begin() + index, asset);
}
int GGAbstractModel::GetNumAssets() {
	return (int) assets.size();
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
GGTimerAsset* GGAbstractModel::GetTimer() {
	return &timer;
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

GGCannonGameModel::GGCannonGameModel() : cannonAsset(sf::Vector2f(0, 0), "Assets/Animations/cannon_game/cannon.png", 
										 sf::Vector2u(4, 3), false, 10), backgroundAsset(sf::Vector2f(0,0), "Assets/Animations/cannon_game/court_level_1.png"),
										 cannonFiring(false),
										 cannonAngle(0),
										 moneyAssetIcon(sf::Vector2f(0, 0), "Assets/Animations/cannon_game/money_flying.png"),
										 ammunitionCountAsset(sf::Vector2f(0, 0), 70, "Assets/Fonts/Minimal5x7.ttf", sf::Color::White) {
	AddAsset(&backgroundAsset);
	backgroundAsset.Scale(sf::Vector2f(4, 4));
	backgroundAsset.SetOrigin(0, 0);

	for (int i = 0; i < GetNumProjectiles(); i++) {
		GGStaticAsset* moneyAsset = new GGStaticAsset(sf::Vector2f(0, 0), "Assets/Animations/cannon_game/money_flying.png");
		moneyAssets.push_back(moneyAsset);
		// AddAsset(moneyAsset);
	}
	for (int i = 0; i < GetNumTargets(); i++) {
		GGSheetAsset* targetAsset = new GGSheetAsset(sf::Vector2f(0, 0), "Assets/Animations/cannon_game/money_catch.png", sf::Vector2u(5, 1), false, 4);
		targetAsset->Scale(sf::Vector2f(5, 5));
		targetAsset->SetPos(sf::Vector2f(1350, 600));
		targetAssets.push_back(targetAsset);
		AddAsset(targetAsset);
	}
	float scale = 5.0f;
	cannonAsset.Scale(sf::Vector2f(scale, scale));
	cannonAsset.SetOrigin(sf::Vector2f(cannonAsset.GetTextureSize().x / 3.75f, ceil(cannonAsset.GetTextureSize().y / 1.67f)));
	cannonAsset.SetPos(sf::Vector2f(50, 675));
	cannonAsset.SetRotation(18.5);
	AddAsset(GetTimer());
	GetTimer()->SetTimer(sf::Vector2u(10, 0));
	GetTimer()->SetPos(sf::Vector2f(1175, 5));
	GetTimer()->StartTimer();

	for (int i = 0; i < GetNumProjectiles(); i++) {
		moneyAssets[i]->Scale(sf::Vector2f(4, 4));
		moneyAssets[i]->SetPos(sf::Vector2f(cannonAsset.GetPos().x + GetCannonLength(), cannonAsset.GetPos().y));
	}

	moneyAssetIcon.SetPos(sf::Vector2f(50, 50));
	moneyAssetIcon.Scale(sf::Vector2f(4, 4));
	AddAsset(&moneyAssetIcon);
	ammunitionCountAsset.SetPos(sf::Vector2f(90, 5));
	ammunitionCountAsset.SetText("x 10");
	AddAsset(&ammunitionCountAsset);

	AddAsset(&cannonAsset);
}
GGCannonGameModel::~GGCannonGameModel() {
	for (auto asset : moneyAssets) {
		delete asset;
	}
	for (auto asset : targetAssets) {
		delete asset;
	}
}
GGSheetAsset* GGCannonGameModel::GetCannonAsset() {
	return &cannonAsset;
}
void GGCannonGameModel::ResetData() {
	SetContinueGame(true);
	SetSuccess(true);
}
void GGCannonGameModel::SetCannonFiring(bool isCannonFiring) {
	cannonFiring = isCannonFiring;
}
bool GGCannonGameModel::GetCannonFiring() {
	return cannonFiring;
}
float GGCannonGameModel::GetCannonAngle() {
	return cannonAngle;
}
void GGCannonGameModel::SetCannonAngle(float angle) {
	cannonAsset.SetRotation(angle + 18.5f);
	cannonAngle = angle;
}
GGStaticAsset* GGCannonGameModel::GetProjectile(int index) {
	return moneyAssets[index];
}
GGSheetAsset* GGCannonGameModel::GetTarget(int index) {
	return targetAssets[index];
}
float GGCannonGameModel::GetCannonLength() {
	return 90.0f;
}
int GGCannonGameModel::GetNumProjectiles() {
	return 10;
}
int GGCannonGameModel::GetNumTargets() {
	return 3;
}
void GGCannonGameModel::MakeProjectileVisible(int index) {
	InsertAsset(moneyAssets[index], GetNumAssets() - 1);
}
void GGCannonGameModel::UpdateAmmunitionCount(int amt) {
	char str[128];
	sprintf_s(str, "x %d", amt);
	ammunitionCountAsset.SetText(str);
}