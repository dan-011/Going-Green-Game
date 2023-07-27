#include "GGAbstractModel.h"
#include <cmath>
#define DEBUG 0
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

#define DELAY 15

GGAbstractModel::GGAbstractModel() : continueGame(true), wasSuccess(true), timer(sf::Vector2f(0, 0), 50, "Assets/Fonts/Minimal5x7.ttf", 0, 0, sf::Color::White), backgroundMusic(NULL) {}
GGAbstractModel::~GGAbstractModel() {
	delete backgroundMusic;
}
std::vector<GGAbstractAsset*>& GGAbstractModel::GetAssets() {
	return assets;
}
void GGAbstractModel::AddAsset(GGAbstractAsset* asset) {
	assets.push_back(asset);
}
void GGAbstractModel::InsertAsset(GGAbstractAsset* asset, int index) {
	assets.insert(assets.begin() + index, asset);
}
void GGAbstractModel::RemoveAsset(int index) {
	assets.erase(assets.begin() + index);
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
GGMusicAsset* GGAbstractModel::GetBackgroundMusic() {
	return backgroundMusic;
}
void GGAbstractModel::AssignBackgroundMusic(std::string fileName) {
	backgroundMusic = new GGMusicAsset(fileName);
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
										 ammunitionCountAsset(sf::Vector2f(0, 0), 70, "Assets/Fonts/Minimal5x7.ttf", sf::Color::White),
										 first(true),
										 cannonSound("Assets/Music/CannonFire.wav") {
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

	for (int i = 0; i < GetNumProjectiles(); i++) {
		velocities.push_back(sf::Vector2f(0, 0));
		projectileStatuses.push_back(LOADED);
		projectileDelays.push_back(DELAY);
	}

	srand((unsigned int)time(NULL));
	for (int i = 0; i < GetNumTargets(); i++) {
		targetHitStatuses.push_back(false);
		// targetWaitTicks.push_back(rand() % 20);
	}

	targetWaitTicks.push_back(0);
	targetWaitTicks.push_back(75);
	targetWaitTicks.push_back(110);

	AssignBackgroundMusic("Assets/Music/MainThemeLoop1.wav");
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
	velocities.clear();
	projectileStatuses.clear();
	projectileDelays.clear();
	targetHitStatuses.clear();
	targetWaitTicks.clear();
	for (int i = 0; i < GetNumProjectiles(); i++) {
		velocities.push_back(sf::Vector2f(0, 0));
		projectileStatuses.push_back(LOADED);
		projectileDelays.push_back(DELAY);
	}

	srand((unsigned int)time(NULL));
	for (int i = 0; i < GetNumTargets(); i++) {
		targetHitStatuses.push_back(false);
		// targetWaitTicks.push_back(rand() % 20);
	}
	for (int i = 0; i < GetNumProjectiles(); i++) {
		GetProjectile(i)->SetPos(sf::Vector2f(cannonAsset.GetPos().x + GetCannonLength(), cannonAsset.GetPos().y));
		if (projectileStatuses[i] == LANDED || projectileStatuses[i] == FIRED) {
			RemoveAsset(GetNumAssets() - 2);
		}
	}
	SetCannonAngle(0);

	for (int i = 0; i < GetNumTargets(); i++) {
		GGSheetAsset* targetAsset = GetTarget(i);
		targetAsset->SetPos(sf::Vector2f(1350, 600));
		targetAsset->SetCurFrame(0);
	}
	first = false;
	curProjectileAsset = 0;

	targetWaitTicks.push_back(0);
	targetWaitTicks.push_back(75);
	targetWaitTicks.push_back(110);

	GetTimer()->RestartTimer();
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

sf::Vector2f GGCannonGameModel::GetVelocity(int index) {
	return velocities[index];
}
void GGCannonGameModel::SetVelocity(int index, sf::Vector2f vel) {
	velocities[index] = vel;
}
GGPROJECTILE_STATUS GGCannonGameModel::GetProjectileStatus(int index) {
	return projectileStatuses[index];
}
void GGCannonGameModel::SetProjectileStatus(int index, GGPROJECTILE_STATUS status) {
	projectileStatuses[index] = status;
}
bool GGCannonGameModel::GetTargetHitStatus(int index) {
	return targetHitStatuses[index];
}
void GGCannonGameModel::SetTargetHitStatus(int index, bool status) {
	targetHitStatuses[index] = status;
}
int GGCannonGameModel::GetProjectileDelay(int index) {
	return projectileDelays[index]--;
}

int GGCannonGameModel::GetCurProjectileAsset() {
	return curProjectileAsset;
}
void GGCannonGameModel::SetCurProjectileAsset(int index) {
	curProjectileAsset = index;
}
int GGCannonGameModel::TargetWaitTick(int index) {
	return targetWaitTicks[index]--;
}
GGSFXAsset* GGCannonGameModel::GetCannonSound() {
	return &cannonSound;
}