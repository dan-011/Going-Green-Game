#include "GGAbstractAsset.h"
#define DEBUG 0
#ifdef DEBUG
#include <iostream>
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


GGSheetAsset::GGSheetAsset(sf::Vector2f pos, const std::string fileName, sf::Vector2u dims, bool animateOnce, int totalFrames) : GGSpriteAsset(pos), dimensions(dims), curFrame(0), animOnce(animateOnce), finishedAnimating(false), numFrames(totalFrames) {
	assetTexture.loadFromFile(fileName);
	assetBlock.width = assetTexture.getSize().x / dims.x;
	assetBlock.height = assetTexture.getSize().y / dims.y;
	assetBlock.top = 0;
	assetBlock.left = 0;
	
	// assetBody.setSize(sf::Vector2f(assetTexture.getSize().x, assetTexture.getSize().y));
	/*
	assetBody.setSize(sf::Vector2f((float)assetBlock.width, (float)assetBlock.height));
	assetBody.setOrigin(assetBody.getSize() / 2.0f);
	assetBody.setPosition(pos);
	assetBody.setTexture(&assetTexture);
	assetBody.setTextureRect(assetBlock);*/

	SetTexture(assetTexture);
	SetAssetBlock(assetBlock);
	SetOrigin((float)assetBlock.width, (float)assetBlock.height);

	if (numFrames == 0) {
		numFrames = dims.x * dims.y;
	}
}
GGSheetAsset::~GGSheetAsset() {}
void GGSheetAsset::Draw() {
	if (finishedAnimating && animOnce) return;
	GGWindow::Instance().GetWindow().draw(GetSprite());
}
void GGSheetAsset::NextAnimation() {
	if (finishedAnimating && animOnce) return;
	curFrame++;
	if (curFrame == numFrames) {
		curFrame = 0;
		finishedAnimating = true;
	}
	int row = curFrame / dimensions.x;
	int col = curFrame % dimensions.x;
	assetBlock.top = row * assetBlock.height;
	assetBlock.left = col * assetBlock.width;

	// assetBody.setTextureRect(assetBlock);
	SetAssetBlock(assetBlock);
}
bool GGSheetAsset::AnimationCompleted() {
	return curFrame == 0;
}
void GGSheetAsset::SetCurFrame(int frame) {
	curFrame = frame;
}
int GGSheetAsset::GetCurFrame() {
	return curFrame;
}
sf::Vector2u GGSheetAsset::GetTextureSize() {
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

GGStaticAsset::GGStaticAsset(sf::Vector2f pos, const std::string fileName) : GGSpriteAsset(pos) {
	assetTexture.loadFromFile(fileName);
	SetOrigin((float)assetTexture.getSize().x, (float)assetTexture.getSize().y);
	SetTexture(assetTexture);
}
GGStaticAsset::~GGStaticAsset() {}
sf::Vector2u GGStaticAsset::GetTextureSize() {
	return assetTexture.getSize();
}

GGTimerAsset::GGTimerAsset(sf::Vector2f pos, unsigned int size, const std::string fontFileName, int sec, int ms, sf::Color clr) : GGAbstractAsset(pos), second(sec), millisecond(ms), startTime(sec, ms), timerStarted(false) {
	timerFont.loadFromFile(fontFileName);
	timerText.setFont(timerFont);
	timerText.setCharacterSize(size);
	timerText.setFillColor(clr);
	sprintf_s(timerStr, "%d.0%d", second, millisecond);
	timerText.setString(timerStr);
	timerText.setPosition(pos);
} // : GGAbstractAsset(pos), timerFont(fontFileName, size), timerStr("", timerFont, size), second(sec), millisecond(ms) {}
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
	}	timerText.setString(timerStr);
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
	timerText.setString(timerStr);
}
void GGTimerAsset::Draw() {
	GGWindow::Instance().GetWindow().draw(timerText);
}
bool GGTimerAsset::TimerCompleted() {
	return second == 0 && millisecond == 0;
}
void GGTimerAsset::SetTimer(sf::Vector2u time) {
	startTime = time;
	RestartTimer();
}
void GGTimerAsset::RestartTimer() {
	second = (int) startTime.x;
	millisecond = (int) startTime.y;
}
void GGTimerAsset::SetPos(sf::Vector2f pos) {
	timerText.setPosition(pos);
	GGAbstractAsset::SetPos(pos);
}
void GGTimerAsset::StartTimer() {
	timerStarted = true;
}
void GGTimerAsset::StopTimer() {
	timerStarted = false;
}
void GGTimerAsset::SetSize(int sz) {
	timerText.setCharacterSize(sz);
}
bool GGTimerAsset::GetTimerStarted() {
	return timerStarted;
}