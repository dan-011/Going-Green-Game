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
	numPumps = 0;
	SetContinueGame(true);
	SetSuccess(true);
	pump->SetCurFrame(0);
	maxedOut = false;
	totalPumps = 0;
	transition->SetDrawing(true);
	oil->SetFinishedAnimating(false);
	oil->SetStart(false);
	timer->RestartTimer();
}

GGNewsModel::GGNewsModel(int maxReports) : goalReports(maxReports), numReports(0)
{
	button1 = new GGButton(sf::Vector2f(275, 550), "b1");
	button2 = new GGButton(sf::Vector2f(1000, 550), "b2");
	background = new GGStaticAsset(sf::Vector2f(0, 0), "Assets/Animations/tv_game/news_minigame_background1.png");
	frame = new GGStaticAsset(sf::Vector2f(0, 0), "Assets/Animations/tv_game/news_frame.png");
	transition = new GGMinigameTransition("Lobby!", "Fill in the sentence with the word\nthat supports corporate interest");
	questionBubble = new GGStaticAsset(sf::Vector2f(640, 135), "Assets/Animations/tv_game/speech_bubble.png");
	questionText = new GGTextAsset(sf::Vector2f(100, 100), 50, "Assets/Fonts/Minimal5x7.ttf", sf::Color(0x24222EFF));
	timer = new GGTimerAsset(sf::Vector2f(540, -50), 100, "Assets/Fonts/Minimal5x7.ttf", 120, 0, sf::Color(0xE6EBD6FF));
	reporter = new GGStaticAsset(sf::Vector2f(-100, 0), "Assets/Animations/tv_game/reporter1.png");
	mouth = new GGSheetAsset(sf::Vector2f(242, 378), "Assets/Animations/tv_game/mouth.png", sf::Vector2u(2, 2));
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
	return (numReports >= goalReports);
}
void GGNewsModel::ResetData()
{
	numReports = 0;
	SetContinueGame(true);
	SetSuccess(true);
	transition->SetDrawing(true);
	timer->RestartTimer();
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

GGStageTransitionModel::GGStageTransitionModel(std::string tableSource, std::string envelopeSource, std::string letterSource) : letterDeceleration(0.1), envelopeDeceleration(-0.1), letterVelocity(0), envelopeVelocity(1), letterMoved(false)
{
	table = new GGStaticAsset(sf::Vector2f(0, 0), tableSource);
	table->SetOrigin(0, 0);
	table->Scale(sf::Vector2f(4, 4));
	envelope = new GGStaticAsset(sf::Vector2f(640, -100), envelopeSource);
	envelope->Scale(sf::Vector2f(4, 4));
	letter = new GGStaticAsset(sf::Vector2f(640, 1075), letterSource);
	letter->Scale(sf::Vector2f(4, 4));
	AddAsset(table);
	AddAsset(envelope);
	AddAsset(letter);
}

GGStageTransitionModel::~GGStageTransitionModel()
{
	delete(table);
	delete(envelope);
	delete(letter);
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