#include "GGAbstractModel.h"
#include <cmath>
#define DEBUG 0
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

#define DELAY 15

GGAbstractModel::GGAbstractModel() : continueGame(true), wasSuccess(true), timer(sf::Vector2f(0, 0), 50, "Assets/Fonts/Minimal5x7.ttf", 0, 0, sf::Color::White), backgroundMusic(NULL), stage(1), clickSwitch(false) {}
GGAbstractModel::~GGAbstractModel() {
	if(backgroundMusic != NULL){
		delete backgroundMusic;
	}
}
std::vector<GGAbstractAsset*>& GGAbstractModel::GetAssets() {
	return assets;
}
void GGAbstractModel::ResetData() {
	SetContinueGame(true);
	SetSuccess(true);
	SetClickSwitch(false);
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
void GGAbstractModel::AssignBackgroundMusic(std::string fileName, bool repeat) {
	GGMusicAsset* oldBackgroundMusic = backgroundMusic;
	backgroundMusic = new GGMusicAsset(fileName);
	if (oldBackgroundMusic != NULL) {
		delete oldBackgroundMusic;
	}
	backgroundMusic->SetRepeat(repeat);
}
int GGAbstractModel::GetStage() {
	return stage;
}
void GGAbstractModel::SetStage(int stg) {
	stage = stg;
}
bool GGAbstractModel::GetClickSwitch() {
	return clickSwitch;
}
void GGAbstractModel::SetClickSwitch(bool clckSwtch) {
	clickSwitch = clckSwtch;
}

GGPumpModel::GGPumpModel() : pump(new GGSheetAsset(sf::Vector2f(650, 292), "Assets/Animations/oil_game/oil_drill_sprite_sheet.png", sf::Vector2u(4, 3))), maxPumps(10), numPumps(0), maxedOut(false), goalPumps(25), totalPumps(0), oil(new GGSheetAsset(sf::Vector2f(590, 360), "Assets/Animations/oil_game/oil_sprite_sheet.png", sf::Vector2u(3, 3), true, false)),
background(new GGStaticAsset(sf::Vector2f(640, 360), "Assets/Animations/oil_game/oil_minigame_background.png")), transition(new GGMinigameTransition("Drill!", "Click as fast as you can!")), timer(new GGTimerAsset(sf::Vector2f(540, -50), 100, "Assets/Fonts/Minimal5x7.ttf", 120, 0, sf::Color(0xE6EBD6FF))) {
	AddAsset(background);
	AddAsset(oil);
	AddAsset(pump);
	AddAsset(timer);
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
	delete timer;
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
GGTimerAsset* GGPumpModel::GetTimer()
{
	return timer;
}
bool GGPumpModel::PumpMaxReached()
{
	return (totalPumps >= goalPumps);
}
void GGPumpModel::ResetData() {
	GGAbstractModel::ResetData();
	numPumps = 0;
	SetContinueGame(true);
	SetSuccess(true);
	pump->SetCurFrame(0);
	maxedOut = false;
	totalPumps = 0;
	transition->SetDrawing(true);
	oil->SetFinishedAnimating(false);
	oil->SetStart(false);
	timer->StopTimer();
	timer->RestartTimer();
}

void GGPumpModel::StageOne()
{
	ResetData();
	background->ChangeBitmap("Assets/Animations/oil_game/oil_minigame_background.png");
	goalPumps = 30;
	timer->SetTimer(sf::Vector2u(60, 0));
}

void GGPumpModel::StageTwo()
{
	ResetData();
	background->ChangeBitmap("Assets/Animations/oil_game/oil_minigame_background2.png");
	goalPumps = 60;
	timer->SetTimer(sf::Vector2u(20, 0));
}

void GGPumpModel::StageThree()
{
	ResetData();
	background->ChangeBitmap("Assets/Animations/oil_game/oil_minigame_background3.png");
	goalPumps = 60;
	timer->SetTimer(sf::Vector2u(10, 0));
}

GGNewsModel::GGNewsModel(int maxReports) : goalReports(maxReports), numReports(0)
{
	button1 = new GGButton(sf::Vector2f(275, 550), "b1");
	button2 = new GGButton(sf::Vector2f(1000, 550), "b2");
	background = new GGStaticAsset(sf::Vector2f(0, 0), "Assets/Animations/tv_game/news_minigame_background1.png");
	frame = new GGStaticAsset(sf::Vector2f(0, 0), "Assets/Animations/tv_game/news_frame.png");
	transition = new GGMinigameTransition("Censor!", "Fill in the sentence with the word\nthat supports corporate interest");
	questionBubble = new GGStaticAsset(sf::Vector2f(640, 135), "Assets/Animations/tv_game/speech_bubble.png");
	questionText = new GGTextAsset(sf::Vector2f(100, 100), 50, "Assets/Fonts/Minimal5x7.ttf", sf::Color(0x24222EFF));
	timer = new GGTimerAsset(sf::Vector2f(540, -50), 100, "Assets/Fonts/Minimal5x7.ttf", 120, 0, sf::Color(0xE6EBD6FF));
	reporter = new GGStaticAsset(sf::Vector2f(-100, 0), "Assets/Animations/tv_game/reporter1.png");
	mouth = new GGSheetAsset(sf::Vector2f(242, 378), "Assets/Animations/tv_game/mouth.png", sf::Vector2u(2, 2));
	for (int i = 1; i < 9; i++)
	{
		voicelines.push_back(new GGSFXAsset("Assets/Music/holynews" + to_string(i) + ".ogg"));
	}
	currentSound = rand() % voicelines.size();
	reporter->SetOrigin(0, 0);
	mouth->Scale(sf::Vector2f(4, 4));
	mouth->SetCurFrame(0);
	reporter->Scale(sf::Vector2f(4,4));
	questionText->SetText("q");
	background->SetOrigin(0, 0);
	frame->SetOrigin(0, 0);
	background->Scale(sf::Vector2f(4, 4));
	frame->Scale(sf::Vector2f(4, 4));
	questionBubble->Scale(sf::Vector2f(4, 4));
	AddAsset(background);
	AddAsset(reporter);
	AddAsset(mouth);
	AddAsset(frame);
	AddAsset(button1);
	AddAsset(button2);
	AddAsset(questionBubble);
	AddAsset(questionText);
	AddAsset(timer);
	AddAsset(transition);
	goalReports = maxReports;
}

GGNewsModel::~GGNewsModel()
{
	delete(button1);
	delete(button2);
	delete(background);
	delete(frame);
	delete(transition);
	delete(questionText);
	delete(questionBubble);
	delete(timer);
	delete(reporter);
	delete(mouth);
	for (int i = 0; i < voicelines.size(); i++)
	{
		delete(voicelines[i]);
	}
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

int GGNewsModel::GetNumAnswers()
{
	return numReports;
}

void GGNewsModel::SetNumAnswers(int nAnswers)
{
	numReports = nAnswers;
}

bool GGNewsModel::GoalMet()
{
	if (numReports >= goalReports)
	{
		voicelines[currentSound]->Stop();
		return true;
	}
	else
	{
		return false;
	}
}
void GGNewsModel::ResetData()
{
	GGAbstractModel::ResetData();
	numReports = 0;
	SetContinueGame(true);
	SetSuccess(true);
	transition->SetDrawing(true);
	timer->StopTimer();
	timer->RestartTimer();
	currentSound = rand() % voicelines.size();
	mouth->SetCurFrame(0);
}

void GGNewsModel::StageOne()
{
	ResetData();
	background->ChangeBitmap("Assets/Animations/tv_game/news_minigame_background1.png");
	reporter->ChangeBitmap("Assets/Animations/tv_game/reporter1.png");
	goalReports = 6;
	for (int i = 0; i < 8; i++)
	{
		voicelines[i]->ChangeSource("Assets/Music/holynews" + to_string(i + 1) + ".ogg");
	}
	timer->SetTimer(sf::Vector2u(45, 0));
}

void GGNewsModel::StageTwo()
{
	ResetData();
	background->ChangeBitmap("Assets/Animations/tv_game/news_minigame_background2.png");
	reporter->ChangeBitmap("Assets/Animations/tv_game/reporter2.png");
	goalReports = 8;
	for (int i = 0; i < 8; i++)
	{
		voicelines[i]->ChangeSource("Assets/Music/sadnews" + to_string(i + 1) + ".ogg");
	}
	timer->SetTimer(sf::Vector2u(30, 0));
}

void GGNewsModel::StageThree()
{
	ResetData();
	background->ChangeBitmap("Assets/Animations/tv_game/news_minigame_background3.png");
	reporter->ChangeBitmap("Assets/Animations/tv_game/reporter3.png");
	goalReports = 10;
	for (int i = 0; i < 8; i++)
	{
		voicelines[i]->ChangeSource("Assets/Music/saddernews" + to_string(i + 1) + ".ogg");
	}
	timer->SetTimer(sf::Vector2u(15, 0));
}

GGTimerAsset* GGNewsModel::GetTimer()
{
	return timer;
}

void GGNewsModel::ChangeMouth()
{
	mouth->SetCurFrame(rand() % 2 + 1);
}

void GGNewsModel::ResetMouth()
{
	mouth->SetCurFrame(0);
}

GGMinigameTransition* GGNewsModel::GetTransition()
{
	return transition;
}

GGTextAsset* GGNewsModel::GetQuestionText()
{
	return questionText;
}

void GGNewsModel::PlayVoiceSFX()
{
	if (transition->GetDrawing())
		return;
	StopAllVoices();
	voicelines[currentSound]->Play();
	currentSound = rand() % voicelines.size();
}
void GGNewsModel::StopAllVoices() {
	for (auto voiceLine : voicelines) {
		voiceLine->Stop();
	}
}
GGStageTransitionModel::GGStageTransitionModel() : letterDeceleration(0.1f), envelopeDeceleration(-0.1f), letterVelocity(0), envelopeVelocity(1), letterMoved(false)
{
	table = new GGStaticAsset(sf::Vector2f(0, 0), "Assets/Animations/stage_transition/table_1.png");
	table->SetOrigin(0, 0);
	table->Scale(sf::Vector2f(4, 4));
	envelope = new GGStaticAsset(sf::Vector2f(640, -100), "Assets/Animations/stage_transition/env1.png");
	envelope->Scale(sf::Vector2f(4, 4));
	letter = new GGStaticAsset(sf::Vector2f(640, 1075), "Assets/Animations/stage_transition/letter_1.png");
	letter->Scale(sf::Vector2f(4, 4));
	crinkle = new GGSFXAsset("Assets/Music/PaperCrinkle.ogg");
	AddAsset(table);
	AddAsset(envelope);
	AddAsset(letter);
	StageOne();
}

GGStageTransitionModel::~GGStageTransitionModel()
{
	delete(table);
	delete(envelope);
	delete(letter);
	delete(crinkle);
}

GGStaticAsset* GGStageTransitionModel::GetEnvelope()
{
	return envelope;
}

GGStaticAsset* GGStageTransitionModel::GetLetter()
{
	return letter;
}

bool GGStageTransitionModel::GetLetterMoved()
{
	return letterMoved;
}
void GGStageTransitionModel::SetLetterMoved(bool moved)
{
	letterMoved = moved;
}
float GGStageTransitionModel::GetLetterVelocity()
{
	return letterVelocity;
}
void GGStageTransitionModel::SetLetterVelocity(float velocity)
{
	letterVelocity = velocity;
}
float GGStageTransitionModel::GetLetterDeceleration()
{
	return letterDeceleration;
}

float GGStageTransitionModel::GetEnvelopeVelocity()
{
	return envelopeVelocity;
}
void GGStageTransitionModel::SetEnvelopeVelocity(float velocity)
{
	envelopeVelocity = velocity;
}
float GGStageTransitionModel::GetEnvelopeDeceleration()
{
	return envelopeDeceleration;
}

void GGStageTransitionModel::ResetData()
{
	GGAbstractModel::ResetData();
	letterMoved = false;
	envelope->SetPos(sf::Vector2f(640, -100));
	letter->SetPos(sf::Vector2f(640, 1075));
	letterVelocity = 0;
	envelopeVelocity = 9.5;
}

void GGStageTransitionModel::PlayLetterSound()
{
	crinkle->Play();
}

void GGStageTransitionModel::StageOne()
{
	ResetData();
	table->ChangeBitmap("Assets/Animations/stage_transition/table_1.png");
	//envelope->ChangeBitmap("Assets/Animations/stage_transition/env1.png");
	letter->ChangeBitmap("Assets/Animations/stage_transition/letter_1.png");
	for (int i = 0; i < 3; i++)
	{
		RemoveAsset(0);
	}
	GGStaticAsset* tmpEnv = envelope;
	envelope = new GGStaticAsset(sf::Vector2f(640, -100), "Assets/Animations/stage_transition/env1.png");
	if (tmpEnv != NULL)
	{
		delete(tmpEnv);
	}
	envelope->Scale(sf::Vector2f(4, 4));
	AddAsset(table);
	AddAsset(envelope);
	AddAsset(letter);
}

void GGStageTransitionModel::StageTwo()
{
	ResetData();
	table->ChangeBitmap("Assets/Animations/stage_transition/table_2.png");
	letter->ChangeBitmap("Assets/Animations/stage_transition/letter_2.png");

	for (int i = 0; i < 3; i++)
	{
		RemoveAsset(0);
	}
	GGStaticAsset* tmpEnv = envelope;
	envelope = new GGStaticAsset(sf::Vector2f(640, -100), "Assets/Animations/stage_transition/env2.png");
	if (tmpEnv != NULL)
	{
		delete(tmpEnv);
	}
	envelope->Scale(sf::Vector2f(4, 4));
	AddAsset(table);
	AddAsset(envelope);
	AddAsset(letter);
}

void GGStageTransitionModel::StageThree()
{
	ResetData();
	table->ChangeBitmap("Assets/Animations/stage_transition/table_3.png");
	letter->ChangeBitmap("Assets/Animations/stage_transition/letter_3.png");
	for (int i = 0; i < 3; i++)
	{
		RemoveAsset(0);
	}
	GGStaticAsset* tmpEnv = envelope;
	envelope = new GGStaticAsset(sf::Vector2f(640, -100), "Assets/Animations/stage_transition/env3.png");
	if (tmpEnv != NULL)
	{
		delete(tmpEnv);
	}
	envelope->Scale(sf::Vector2f(4, 4));
	AddAsset(table);
	AddAsset(envelope);
	AddAsset(letter);
}

GGCannonGameModel::GGCannonGameModel() : cannonAsset(sf::Vector2f(0, 0), "Assets/Animations/cannon_game/cannon.png", 
										 sf::Vector2u(4, 3), false, true, 10),
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
										 hitCount(0),
										 transitionAsset("Lobby!", "Fire money to pay\nthe lobbyists"),
										 gameStarted(false) {
	AddAsset(&backgroundAsset);
	backgroundAsset.Scale(sf::Vector2f(4, 4));
	backgroundAsset.SetOrigin(0, 0);
	AddAsset(&transitionAsset);
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
	cannonAsset.SetCurFrame(0);
	cannonFiring = false;
	transitionAsset.SetDrawing(true);
	SetGameStarted(false);
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

	for (auto projectile : moneyAssets) {
		projectile->SetVisibility(false);
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
	UpdateAmmunitionCount(GetNumProjectiles());
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
	moneyAssets[index]->SetVisibility(true);
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
	targetSpeed = sf::milliseconds(60);
	// AssignBackgroundMusic("Assets/Music/MainThemeLoop1.wav");
	UpdateAmmunitionCount(GetNumProjectiles());
	backgroundAsset.ChangeBitmap("Assets/Backgrounds/court_1.png");
	for (int i = 0; i < GetNumProjectiles(); i++) {
		GGStaticAsset* moneyAsset = new GGStaticAsset(sf::Vector2f(0, 0), "Assets/Animations/cannon_game/money_flying.png");
		moneyAssets.push_back(moneyAsset);
		AddAsset(moneyAsset);
		moneyAsset->SetVisibility(false);
	}
	for (int i = 0; i < GetNumTargets(); i++) {
		GGSheetAsset* targetAsset = new GGSheetAsset(sf::Vector2f(0, 0), "Assets/Animations/cannon_game/money_catch.png", sf::Vector2u(5, 1), false, true, 4);
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
	targetSpeed = sf::milliseconds(40);
	UpdateAmmunitionCount(GetNumProjectiles());
	// AssignBackgroundMusic("Assets/Music/MainThemeLoop2.wav");
	backgroundAsset.ChangeBitmap("Assets/Backgrounds/court_2.png");

	for (auto target : targetAssets) {
		target->ChangeBitmap("Assets/Animations/cannon_game/money_catch2.png");
	}

	for (int i = oldNumProjectiles; i < GetNumProjectiles(); i++) {
		GGStaticAsset* moneyAsset = new GGStaticAsset(sf::Vector2f(0, 0), "Assets/Animations/cannon_game/money_flying.png");
		moneyAssets.push_back(moneyAsset);
		AddAsset(moneyAsset);
		moneyAsset->SetVisibility(false);
	}
	for (int i = oldNumTargets; i < GetNumTargets(); i++) {
		GGSheetAsset* targetAsset = new GGSheetAsset(sf::Vector2f(0, 0), "Assets/Animations/cannon_game/money_catch2.png", sf::Vector2u(5, 1), false, true, 4);
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
		GGSheetAsset* targetAsset = new GGSheetAsset(sf::Vector2f(0, 0), "Assets/Animations/cannon_game/money_catch3.png", sf::Vector2u(5, 1), false, true, 4);
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
GGMinigameTransition* GGCannonGameModel::GetTransition() {
	return &transitionAsset;
}
bool GGCannonGameModel::GetGameStarted() {
	return gameStarted;
}
void GGCannonGameModel::SetGameStarted(bool startGame) {
	gameStarted = startGame;
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

GGBookendsModel::~GGBookendsModel() {}
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

GGGameOverModel::GGGameOverModel() : gameOverScreen(new GGStaticAsset(sf::Vector2f(0, 0), "Assets/Backgrounds/lose_1.png")), gameOverText(sf::Vector2f(0, 0), 150, "Assets/Fonts/Minimal3x5.ttf", sf::Color::Black), restartGameText(sf::Vector2f(0, 0), 50, "Assets/Fonts/Minimal5x5Monospaced.ttf", sf::Color::White) {
	gameOverScreen->Scale(sf::Vector2f(4, 4));
	gameOverScreen->SetOrigin(sf::Vector2f(0, 0));
	gameOverScreen->SetPos(sf::Vector2f(0, 0));
	AddAsset(gameOverScreen);

	gameOverText.SetText("GAME OVER");
	gameOverText.SetPos(sf::Vector2f(325, 80));
	AddAsset(&gameOverText);

	restartGameText.SetText("Press R to Restart Stage");
	// restartGameText.SetPos(sf::Vector2f(360, 650));
	restartGameText.SetPos(sf::Vector2f(260, 650));
	AddAsset(&restartGameText);
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
void GGGameOverModel::SetTextVisibility(bool isVisible) {
	restartGameText.SetVisibility(isVisible);
}
bool GGGameOverModel::GetTextVisibility() {
	return restartGameText.GetVisibility();
}

GGSecretEndingModel::GGSecretEndingModel() : backgroundAsset(sf::Vector2f(0, 0), "Assets/Backgrounds/secret_ending.png") {
	backgroundAsset.Scale(sf::Vector2f(4, 4));
	backgroundAsset.SetOrigin(sf::Vector2f(0, 0));
	AddAsset(&backgroundAsset);
	AssignBackgroundMusic("Assets/Music/WinJingle.wav", false);
}
GGSecretEndingModel::~GGSecretEndingModel() {}
void GGSecretEndingModel::StageOne() {}
void GGSecretEndingModel::StageTwo() {}
void GGSecretEndingModel::StageThree() {}