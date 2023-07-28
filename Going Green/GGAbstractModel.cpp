#include "GGAbstractModel.h"
#include <cmath>
#define DEBUG 0
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

#define DELAY 15

GGAbstractModel::GGAbstractModel() : continueGame(true), wasSuccess(true), timer(sf::Vector2f(0, 0), 50, "Assets/Fonts/Minimal5x7.ttf", 0, 0, sf::Color::White), backgroundMusic(NULL), stage(1) {}
GGAbstractModel::~GGAbstractModel() {
	delete backgroundMusic;
}
std::vector<GGAbstractAsset*>& GGAbstractModel::GetAssets() {
	return assets;
}
void GGAbstractModel::ResetData() {
	SetContinueGame(true);
	SetSuccess(true);
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
	GGMusicAsset* oldBackgroundMusic = backgroundMusic;
	backgroundMusic = new GGMusicAsset(fileName);
	if (oldBackgroundMusic != NULL) {
		delete oldBackgroundMusic;
	}
}
int GGAbstractModel::GetStage() {
	return stage;
}
void GGAbstractModel::SetStage(int stg) {
	stage = stg;
}

GGGameOverModel::GGGameOverModel() : gameOverScreen(new GGStaticAsset(sf::Vector2f(0, 0), "Assets/Backgrounds/lose_1.png")) {
	gameOverScreen->Scale(sf::Vector2f(4, 4));
	gameOverScreen->SetOrigin(sf::Vector2f(0, 0));
	gameOverScreen->SetPos(sf::Vector2f(0, 0));
	AddAsset(gameOverScreen);
}
GGGameOverModel::~GGGameOverModel() {
	delete gameOverScreen;
}
GGStaticAsset* GGGameOverModel::GetGameOverAsset() {
	return gameOverScreen;
}
void GGGameOverModel::StageOne() {
	ResetData();
	gameOverScreen->ChangeBitmap("Assets/Backgrounds/lose_1.png");
	SetStage(1);
}
void GGGameOverModel::StageTwo() {
	ResetData();
	gameOverScreen->ChangeBitmap("Assets/Backgrounds/lose_2.png");
	SetStage(2);
}
void GGGameOverModel::StageThree() {
	ResetData();
	gameOverScreen->ChangeBitmap("Assets/Backgrounds/lose_3.png");
	SetStage(3);
}

GGCannonGameModel::GGCannonGameModel() : cannonAsset(sf::Vector2f(0, 0), "Assets/Animations/cannon_game/cannon.png", 
										 sf::Vector2u(4, 3), false, 10),
										 backgroundAsset(sf::Vector2f(0,0), "Assets/Backgrounds/court_1.png"),
										 cannonFiring(false),
										 cannonAngle(0),
										 moneyAssetIcon(sf::Vector2f(0, 0), "Assets/Animations/cannon_game/money_flying.png"),
										 ammunitionCountAsset(sf::Vector2f(0, 0), 70, "Assets/Fonts/Minimal5x7.ttf", sf::Color::White),
										 first(true),
										 cannonSound("Assets/Music/CannonFire.wav"),
										 totalProjectiles(10),
										 totalTargets(3),
										 targetSpeed(sf::milliseconds(90)),
										 hitCount(0) {
	AddAsset(&backgroundAsset);
	backgroundAsset.Scale(sf::Vector2f(4, 4));
	backgroundAsset.SetOrigin(0, 0);

	float scale = 5.0f;
	cannonAsset.Scale(sf::Vector2f(scale, scale));
	cannonAsset.SetOrigin(sf::Vector2f(cannonAsset.GetTextureSize().x / 3.75f, ceil(cannonAsset.GetTextureSize().y / 1.67f)));
	cannonAsset.SetPos(sf::Vector2f(50, 675));
	cannonAsset.SetRotation(18.5);
	// AddAsset(GetTimer());
	GetTimer()->SetTimer(sf::Vector2u(10, 0));
	GetTimer()->SetPos(sf::Vector2f(1175, 5));
	GetTimer()->StartTimer();

	moneyAssetIcon.SetPos(sf::Vector2f(50, 50));
	moneyAssetIcon.Scale(sf::Vector2f(4, 4));
	AddAsset(&moneyAssetIcon);
	ammunitionCountAsset.SetPos(sf::Vector2f(90, 5));
	ammunitionCountAsset.SetText("x 10");
	AddAsset(&ammunitionCountAsset);

	StageOne();
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
	GGAbstractModel::ResetData();
	hitCount = 0;
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
	return totalProjectiles;
}
int GGCannonGameModel::GetNumTargets() {
	return totalTargets;
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
sf::Time GGCannonGameModel::GetTagetSpeed() {
	return targetSpeed;
}
void GGCannonGameModel::StageOne() {
	totalProjectiles = 10;
	totalTargets = 3;
	targetSpeed = sf::milliseconds(90);
	// AssignBackgroundMusic("Assets/Music/MainThemeLoop1.wav");
	UpdateAmmunitionCount(GetNumProjectiles());
	backgroundAsset.ChangeBitmap("Assets/Backgrounds/court_1.png");
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

	for (int i = 0; i < GetNumProjectiles(); i++) {
		moneyAssets[i]->Scale(sf::Vector2f(4, 4));
		moneyAssets[i]->SetPos(sf::Vector2f(cannonAsset.GetPos().x + GetCannonLength(), cannonAsset.GetPos().y));
	}

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
	SetStage(1);
	AddAsset(&cannonAsset);
}
void GGCannonGameModel::StageTwo() {
	ResetData();
	RemoveAsset(GetNumAssets() - 1);

	int oldNumTargets = GetNumTargets();
	int oldNumProjectiles = GetNumProjectiles();
	totalProjectiles = 15;
	totalTargets = 5;
	targetSpeed = sf::milliseconds(50);
	UpdateAmmunitionCount(GetNumProjectiles());
	// AssignBackgroundMusic("Assets/Music/MainThemeLoop2.wav");
	backgroundAsset.ChangeBitmap("Assets/Backgrounds/court_2.png");

	for (auto target : targetAssets) {
		target->ChangeBitmap("Assets/Animations/cannon_game/money_catch2.png");
	}

	for (int i = oldNumProjectiles; i < GetNumProjectiles(); i++) {
		GGStaticAsset* moneyAsset = new GGStaticAsset(sf::Vector2f(0, 0), "Assets/Animations/cannon_game/money_flying.png");
		moneyAssets.push_back(moneyAsset);
		// AddAsset(moneyAsset);
	}
	for (int i = oldNumTargets; i < GetNumTargets(); i++) {
		GGSheetAsset* targetAsset = new GGSheetAsset(sf::Vector2f(0, 0), "Assets/Animations/cannon_game/money_catch2.png", sf::Vector2u(5, 1), false, 4);
		targetAsset->Scale(sf::Vector2f(5, 5));
		targetAsset->SetPos(sf::Vector2f(1350, 600));
		targetAssets.push_back(targetAsset);
		AddAsset(targetAsset);
	}

	for (int i = oldNumProjectiles; i < GetNumProjectiles(); i++) {
		moneyAssets[i]->Scale(sf::Vector2f(4, 4));
		moneyAssets[i]->SetPos(sf::Vector2f(cannonAsset.GetPos().x + GetCannonLength(), cannonAsset.GetPos().y));
		velocities.push_back(sf::Vector2f(0, 0));
		projectileStatuses.push_back(LOADED);
		projectileDelays.push_back(DELAY);
	}

	srand((unsigned int)time(NULL));
	for (int i = oldNumTargets; i < GetNumTargets(); i++) {
		targetHitStatuses.push_back(false);
		// targetWaitTicks.push_back(rand() % 20);
	}

	int startDelay = 150;
	for (int i = oldNumTargets; i < GetNumTargets(); i++) {
		targetWaitTicks.push_back(startDelay);
		startDelay += 30;
	}
	SetStage(2);
	AddAsset(&cannonAsset);
}
void GGCannonGameModel::StageThree() {
	ResetData();
	RemoveAsset(GetNumAssets() - 1);

	int oldNumTargets = GetNumTargets();
	int oldNumProjectiles = GetNumProjectiles();
	totalProjectiles = 20;
	totalTargets = 10;
	targetSpeed = sf::milliseconds(30);
	UpdateAmmunitionCount(GetNumProjectiles());
	// AssignBackgroundMusic("Assets/Music/MainThemeLoop3.wav");
	backgroundAsset.ChangeBitmap("Assets/Backgrounds/court_3.png");

	for (auto target : targetAssets) {
		target->ChangeBitmap("Assets/Animations/cannon_game/money_catch3.png");
	}

	for (int i = oldNumProjectiles; i < GetNumProjectiles(); i++) {
		GGStaticAsset* moneyAsset = new GGStaticAsset(sf::Vector2f(0, 0), "Assets/Animations/cannon_game/money_flying.png");
		moneyAssets.push_back(moneyAsset);
		// AddAsset(moneyAsset);
	}
	for (int i = oldNumTargets; i < GetNumTargets(); i++) {
		GGSheetAsset* targetAsset = new GGSheetAsset(sf::Vector2f(0, 0), "Assets/Animations/cannon_game/money_catch3.png", sf::Vector2u(5, 1), false, 4);
		targetAsset->Scale(sf::Vector2f(5, 5));
		targetAsset->SetPos(sf::Vector2f(1350, 600));
		targetAssets.push_back(targetAsset);
		AddAsset(targetAsset);
	}

	for (int i = oldNumProjectiles; i < GetNumProjectiles(); i++) {
		moneyAssets[i]->Scale(sf::Vector2f(4, 4));
		moneyAssets[i]->SetPos(sf::Vector2f(cannonAsset.GetPos().x + GetCannonLength(), cannonAsset.GetPos().y));
		velocities.push_back(sf::Vector2f(0, 0));
		projectileStatuses.push_back(LOADED);
		projectileDelays.push_back(DELAY);
	}

	srand((unsigned int)time(NULL));
	for (int i = oldNumTargets; i < GetNumTargets(); i++) {
		targetHitStatuses.push_back(false);
		// targetWaitTicks.push_back(rand() % 20);
	}

	targetWaitTicks.clear();
	int startDelay = 0;
	for (int i = 0; i < GetNumTargets(); i++) {
		targetWaitTicks.push_back(startDelay);
		startDelay += 30;
	}
	SetStage(3);
	AddAsset(&cannonAsset);
}
int GGCannonGameModel::GetHitCount() {
	return hitCount;
}
void GGCannonGameModel::IncrementHitCount() {
	hitCount++;
}
GGStageFourModel::GGStageFourModel() : screenIndex(0), background(sf::Vector2f(0, 0), "Assets/Backgrounds/forest_4.png") {
	background.Scale(sf::Vector2f(4, 4));
	background.SetOrigin(sf::Vector2f(0, 0));
	background.SetPos(sf::Vector2f(0, 0));
	AssignBackgroundMusic("Assets/Music/wind.ogg");
	screenFileNames.push_back("Assets/Backgrounds/forest_4.png");
	screenFileNames.push_back("Assets/Backgrounds/court_4.png");
	screenFileNames.push_back("Assets/Backgrounds/desert_4.png");
	screenFileNames.push_back("Assets/Backgrounds/lose_4.png");

	AddAsset(&background);
}
GGStageFourModel::~GGStageFourModel() {}
int GGStageFourModel::GetScreenNumber() {
	return screenIndex;
}
void GGStageFourModel::NextScreen() {
	background.ChangeBitmap(screenFileNames[++screenIndex]);
}
void GGStageFourModel::ResetData() {
	GGAbstractModel::ResetData();
	screenIndex = 0;
	background.ChangeBitmap(screenFileNames[screenIndex]);
}
void GGStageFourModel::StageOne() {}
void GGStageFourModel::StageTwo() {}
void GGStageFourModel::StageThree() {}

GGTitleScreenModel::GGTitleScreenModel() : background(sf::Vector2f(0, 0), "Assets/Backgrounds/title.png"), pressStartText(sf::Vector2f(0,0), 50, "Assets/Fonts/Minimal5x5Monospaced.ttf", sf::Color::Black) {
	background.SetOrigin(sf::Vector2f(0, 0));
	background.SetPos(sf::Vector2f(0, 0));
	background.Scale(sf::Vector2f(4, 4));
	AddAsset(&background);
	AssignBackgroundMusic("Assets/Music/TitleScreenLoop.wav");
	pressStartText.SetText("Press ENTER to Start");
	pressStartText.SetPos(sf::Vector2f(320, 650));
	AddAsset(&pressStartText);
}
GGTitleScreenModel::~GGTitleScreenModel() {}
void GGTitleScreenModel::StageOne() {}
void GGTitleScreenModel::StageTwo() {}
void GGTitleScreenModel::StageThree() {}
void GGTitleScreenModel::SetTextVisibility(bool isVisible) {
	pressStartText.SetVisibility(isVisible);
}
bool GGTitleScreenModel::GetTextVisibility() {
	return pressStartText.GetVisibility();
}