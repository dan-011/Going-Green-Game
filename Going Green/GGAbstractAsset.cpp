#include "GGAbstractAsset.h"
#define DEBUG 0
#ifdef DEBUG
#include <iostream>
#include <cmath>
using namespace std;
#endif

GGAbstractAsset::GGAbstractAsset(sf::Vector2f pos): position(pos) {}
GGAbstractAsset::~GGAbstractAsset() {}
void GGAbstractAsset::SetPos(sf::Vector2f pos) {
	position = pos;
}
sf::Vector2f GGAbstractAsset::GetPos() {
	return position;
}

GGSpriteAsset::GGSpriteAsset(sf::Vector2f pos) : GGAbstractAsset(pos) {
	assetSprite.setPosition(pos);
}
GGSpriteAsset::~GGSpriteAsset() {}
void GGSpriteAsset::SetPos(sf::Vector2f pos) {
	GGAbstractAsset::SetPos(pos);
	assetSprite.setPosition(pos);
}
void GGSpriteAsset::Scale(sf::Vector2f dims) {
	assetSprite.setScale(dims);
}
void GGSpriteAsset::SetTexture(sf::Texture& assetTexture) {
	assetSprite.setTexture(assetTexture);
}
void GGSpriteAsset::SetAssetBlock(sf::IntRect& assetBlock) {
	assetSprite.setTextureRect(assetBlock);
}
void GGSpriteAsset::SetOrigin(float width, float height) {
	assetSprite.setOrigin(sf::Vector2f(width, height) / 2.0f);
}
void GGSpriteAsset::SetOrigin(sf::Vector2f origin) {
	assetSprite.setOrigin(origin);
}
sf::Vector2f GGSpriteAsset::GetOrigin() {
	return assetSprite.getOrigin();
}
void GGSpriteAsset::SetRotation(float degrees) {
	assetSprite.setRotation(degrees);
}
float GGSpriteAsset::GetRotation() {
	return assetSprite.getRotation();
}
void GGSpriteAsset::NextAnimation() {}
void GGSpriteAsset::Draw() {
	GGWindow::Instance().GetWindow().draw(assetSprite);
}
sf::Sprite& GGSpriteAsset::GetSprite() {
	return assetSprite;
}

sf::FloatRect GGSpriteAsset::GetGlobalBounds()
{
	return assetSprite.getGlobalBounds();
}

GGSheetAsset::GGSheetAsset(sf::Vector2f pos, const std::string fileName, sf::Vector2u dims, bool animateOnce, bool start, int totalFrames) : GGSpriteAsset(pos), dimensions(dims), curFrame(0), animOnce(animateOnce), finishedAnimating(false), started(start), numFrames(totalFrames) {
	assetTexture.loadFromFile(fileName);
	assetBlock.width = assetTexture.getSize().x / dims.x;
	assetBlock.height = assetTexture.getSize().y / dims.y;
	assetBlock.top = 0;
	assetBlock.left = 0;
	
	// assetBody.setSize(sf::Vector2f(assetTexture.getSize().x, assetTexture.getSize().y));
	//assetBody.setSize(sf::Vector2f((float)assetBlock.width, (float)assetBlock.height));
	//assetBody.setOrigin(assetBody.getSize() / 2.0f);
	//assetBody.setPosition(pos);
	//assetBody.setTexture(&assetTexture);
	//assetBody.setTextureRect(assetBlock);
	SetTexture(assetTexture);
	SetAssetBlock(assetBlock);
	SetOrigin((float)assetBlock.width, (float)assetBlock.height);

	if (numFrames == 0) {
		numFrames = dims.x * dims.y;
	}
}
GGSheetAsset::~GGSheetAsset() {}
void GGSheetAsset::Draw() {
	if (finishedAnimating && animOnce || !started) return;
	GGWindow::Instance().GetWindow().draw(GetSprite());
}
void GGSheetAsset::NextAnimation() {
	if (finishedAnimating && animOnce || !started) return;
	int numFrames = dimensions.x * dimensions.y;
	curFrame++;
	if (curFrame == numFrames) {
		finishedAnimating = true;
		curFrame = 0;
	}
	int row = curFrame / dimensions.x;
	int col = curFrame % dimensions.x;
	assetBlock.top = row * assetBlock.height;
	assetBlock.left = col * assetBlock.width;

	SetAssetBlock(assetBlock);
}

void GGSheetAsset::SetStart(bool start)
{
	started = start;
}
bool GGSheetAsset::AnimationCompleted() {
	return curFrame == 0;
}

bool GGSheetAsset::CheckFinishedAnimating()
{
	return finishedAnimating;
}

void GGSheetAsset::SetFinishedAnimating(bool finished)
{
	finishedAnimating = finished;
}

void GGSheetAsset::SetCurFrame(int frame) {
	curFrame = frame;
}
int GGSheetAsset::GetCurFrame() {
	return curFrame;
}

//void GGSheetAsset::SetScale(sf::Vector2f scale)
//{
//	GetSprite().setScale(scale);
//}


sf::Vector2u GGSheetAsset::GetTextureSize()
{
	return sf::Vector2u(assetTexture.getSize().x / dimensions.x, assetTexture.getSize().y / dimensions.y);
}

GGListAsset::GGListAsset(sf::Vector2f pos, std::vector<std::string> fileNames) : GGSpriteAsset(pos), curFrame(0) {
	for (auto fileName : fileNames) {
		sf::Texture* assetTexture = new sf::Texture();
		assetTexture->loadFromFile(fileName);
		assetTextures.push_back(assetTexture);
	}
	if (assetTextures.size() == 0) throw "No textures loaded";
	// assetBody.setSize(sf::Vector2f((float)assetTextures[curFrame]->getSize().x, (float)assetTextures[curFrame]->getSize().y));
	// assetBody.setOrigin(assetBody.getSize() / 2.0f);
	// assetBody.setPosition(pos);
	SetOrigin((float)assetTextures[curFrame]->getSize().x, (float)assetTextures[curFrame]->getSize().y);
}
GGListAsset::~GGListAsset() {
	for (auto texture : assetTextures) {
		delete texture;
	}
}
void GGListAsset::NextAnimation() {
	curFrame++;
	if (curFrame == assetTextures.size()) {
		curFrame = 0;
	}
	SetTexture(*assetTextures[curFrame]);
}
bool GGListAsset::AnimationCompleted() {
	return curFrame == 0;
}
void GGListAsset::SetCurFrame(int frame) {
	curFrame = frame;
}
int GGListAsset::GetCurFrame() {
	return curFrame;
}
sf::Vector2u GGListAsset::GetTextureSize() {
	return (*assetTextures[curFrame]).getSize();
}

GGMinigameTransition::GGMinigameTransition(std::string headerText, std::string subtitleText) : GGSpriteAsset(sf::Vector2f(0, 0)), isDrawing(true)
{
	if (!font.loadFromFile("Assets/Fonts/Minimal5x7.ttf"))
	{
		std::cout << "Font load from file failure!" << endl;
	}
	header.setFont(font);
	subtitle.setFont(font);

	header.setString(headerText);
	header.setOrigin(round(header.getGlobalBounds().width / 2), round(header.getGlobalBounds().height / 2));
	header.setPosition(640, 275);
	header.setScale(2.5, 2.5);
	header.setFillColor(sf::Color(0xE6EBD6FF));

	subtitle.setString(subtitleText);
	subtitle.setOrigin(round(subtitle.getGlobalBounds().width / 2), round(subtitle.getGlobalBounds().height / 2) );
	subtitle.setPosition(640, 375);
	subtitle.setScale(2, 2);
	subtitle.setFillColor(sf::Color(0xE6EBD6FF));

	background.setFillColor(sf::Color(0x24222EDD));
	background.setPosition(sf::Vector2f(0, 0));
	background.setSize(sf::Vector2f(2000, 1000));
}

void GGMinigameTransition::Draw()
{
	if (isDrawing)
	{
		GGWindow::Instance().GetWindow().draw(background);
		GGWindow::Instance().GetWindow().draw(header);
		GGWindow::Instance().GetWindow().draw(subtitle);
	}
}

void GGMinigameTransition::Scale(sf::Vector2f scale)
{
	header.setScale(scale);
	subtitle.setScale(scale);
}

void GGMinigameTransition::SetDrawing(bool drawing)
{
	isDrawing = drawing;
}

bool GGMinigameTransition::GetDrawing()
{
	return isDrawing;
}

sf::Vector2u GGMinigameTransition::GetTextureSize()
{
	return sf::Vector2u(background.getTextureRect().width, background.getTextureRect().height);
}

GGButton::GGButton(sf::Vector2f pos, std::string text) : GGSpriteAsset(pos), isClicked(false), buttonBody(pos, "Assets/Animations/tv_game/button.png", sf::Vector2u(1, 1))
{
	buttonText.setString(text);
	buttonText.setOrigin(round(buttonText.getGlobalBounds().width / 2), round(buttonText.getGlobalBounds().height / 2));
	buttonText.setScale(2, 2);
	if (!font.loadFromFile("Assets/Fonts/Minimal5x7.ttf"))
	{
		std::cout << "Font load from file failure!" << endl;
	}
	buttonText.setFont(font);
	buttonText.setPosition(buttonBody.GetPos());
	buttonText.move(buttonText.getLocalBounds().width * -1, -50);
	buttonBody.Scale(sf::Vector2f(4, 4));
	//buttonText.setScale(sf::Vector2f(4, 4));
	buttonText.setFillColor(sf::Color(0x000000FF));
}
void GGButton::Draw()
{
	buttonBody.Draw();
	GGWindow::Instance().GetWindow().draw(buttonText);
}
void GGButton::Scale(sf::Vector2f scale)
{
	buttonBody.Scale(scale);
	buttonText.setScale(sf::Vector2f(1, 1) + scale);
}
void GGButton::SetClicked(bool click)
{
	if (click)
	{
		cout << "button clicked!" << endl;
	}
	isClicked = click;
}
bool GGButton::GetClicked()
{
	return isClicked;
}

sf::Vector2u GGButton::GetTextureSize()
{
	return buttonBody.GetTextureSize();
}
sf::FloatRect GGButton::GetGlobalBounds()
{
	return buttonBody.GetGlobalBounds();
}

GGStaticAsset::GGStaticAsset(sf::Vector2f pos, const std::string fileName) : GGSpriteAsset(pos) {
	assetTexture.loadFromFile(fileName);
	SetOrigin((float)assetTexture.getSize().x, (float)assetTexture.getSize().y);
	SetTexture(assetTexture);
}
GGStaticAsset::~GGStaticAsset() {}
sf::Vector2u GGStaticAsset::GetTextureSize() {
	return assetTexture.getSize();
}

GGTextAsset::GGTextAsset(sf::Vector2f pos, unsigned int size, const std::string fontFileName, sf::Color clr) : GGAbstractAsset(pos) {
	assetFont.loadFromFile(fontFileName);
	assetText.setFont(assetFont);
	assetText.setCharacterSize(size);
	assetText.setFillColor(clr);
	assetText.setPosition(pos);
}
GGTextAsset::~GGTextAsset() {}
void GGTextAsset::SetText(std::string txt) {
	assetText.setString(txt);
}
void GGTextAsset::Draw() {
	GGWindow::Instance().GetWindow().draw(assetText);
}
void GGTextAsset::SetPos(sf::Vector2f pos) {
	assetText.setPosition(pos);
	GGAbstractAsset::SetPos(pos);
}
void GGTextAsset::SetSize(int sz) {
	assetText.setCharacterSize(sz);
}

GGTimerAsset::GGTimerAsset(sf::Vector2f pos, unsigned int size, const std::string fontFileName, int sec, int ms, sf::Color clr) : GGTextAsset(pos, size, fontFileName, clr), second(sec), millisecond(ms), startTime(sec, ms), timerStarted(false) {
	sprintf_s(timerStr, "%d.0%d", second, millisecond);
	SetText(timerStr);
}
GGTimerAsset::~GGTimerAsset() {}
void GGTimerAsset::TickSec() {
	second--;
	if (second < 0) {
		StopTimer();
	}
	if (millisecond < 10) {
		sprintf_s(timerStr, "%d.0%d", second, millisecond);
	}
	else {
		sprintf_s(timerStr, "%d.%d", second, millisecond);
	}	SetText(timerStr);
}
void GGTimerAsset::TickMS() {
	millisecond--;
	if (millisecond == 0 && second == 0) {
		StopTimer();
	}
	else if (millisecond < 0) {
		TickSec();
		millisecond = 99;
	}
	if (millisecond < 10) {
		sprintf_s(timerStr, "%d.0%d", second, millisecond);
	}
	else {
		sprintf_s(timerStr, "%d.%d", second, millisecond);
	}
	SetText(timerStr);
}
bool GGTimerAsset::TimerCompleted() {
	return second == 0 && millisecond == 0;
}
void GGTimerAsset::SetTimer(sf::Vector2u time) {
	startTime = time;
	RestartTimer();
}
void GGTimerAsset::RestartTimer() {
	second = (int)startTime.x;
	millisecond = (int)startTime.y;
}
void GGTimerAsset::StartTimer() {
	timerStarted = true;
}
void GGTimerAsset::StopTimer() {
	timerStarted = false;
}
bool GGTimerAsset::GetTimerStarted() {
	return timerStarted;
}