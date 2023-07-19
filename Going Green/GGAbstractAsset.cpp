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
void GGAbstractAsset::NextAnimation() {}

void GGAbstractAsset::SetScale(sf::Vector2f scale)
{
	
}
GGSheetAsset::GGSheetAsset(sf::Vector2f pos, const std::string fileName, sf::Vector2u dims, bool animateOnce, bool start) : GGAbstractAsset(pos), dimensions(dims), curFrame(0), animOnce(animateOnce), finishedAnimating(false), started(start) {
	assetTexture.loadFromFile(fileName);
	assetBlock.width = assetTexture.getSize().x / dims.x;
	assetBlock.height = assetTexture.getSize().y / dims.y;
	assetBlock.top = 0;
	assetBlock.left = 0;
	
	// assetBody.setSize(sf::Vector2f(assetTexture.getSize().x, assetTexture.getSize().y));
	assetBody.setSize(sf::Vector2f((float)assetBlock.width, (float)assetBlock.height));
	assetBody.setOrigin(assetBody.getSize() / 2.0f);
	assetBody.setPosition(pos);
	assetBody.setTexture(&assetTexture);
	assetBody.setTextureRect(assetBlock);
}
GGSheetAsset::~GGSheetAsset() {}
void GGSheetAsset::Draw() {
	if (finishedAnimating && animOnce || !started) return;
	GGWindow::Instance().GetWindow().draw(assetBody);
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

	assetBody.setTextureRect(assetBlock);
}

void GGSheetAsset::Start()
{
	started = true;
}
bool GGSheetAsset::AnimationCompleted() {
	return curFrame == 0;
}

bool GGSheetAsset::CheckFinishedAnimating()
{
	return finishedAnimating;
	return finishedAnimating;
}
void GGSheetAsset::SetCurFrame(int frame) {
	curFrame = frame;
}
int GGSheetAsset::GetCurFrame() {
	return curFrame;
}

void GGSheetAsset::SetScale(sf::Vector2f scale)
{
	assetBody.setScale(scale);
}

GGListAsset::GGListAsset(sf::Vector2f pos, std::vector<std::string> fileNames) : GGAbstractAsset(pos), curFrame(0) {
	for (auto fileName : fileNames) {
		sf::Texture* assetTexture = new sf::Texture();
		assetTexture->loadFromFile(fileName);
		assetTextures.push_back(assetTexture);
	}
	if (assetTextures.size() == 0) throw "No textures loaded";
	assetBody.setSize(sf::Vector2f((float)assetTextures[curFrame]->getSize().x, (float)assetTextures[curFrame]->getSize().y));
	assetBody.setOrigin(assetBody.getSize() / 2.0f);
	assetBody.setPosition(pos);
}
GGListAsset::~GGListAsset() {
	for (auto texture : assetTextures) {
		delete texture;
	}
}
void GGListAsset::Draw() {
	assetBody.setTexture(assetTextures[curFrame]);
	GGWindow::Instance().GetWindow().draw(assetBody);
}
void GGListAsset::NextAnimation() {
	curFrame++;
	if (curFrame == assetTextures.size()) {
		curFrame = 0;
	}
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

void GGListAsset::SetScale(sf::Vector2f scale)
{
	assetBody.setScale(scale);
}

GGMinigameTransition::GGMinigameTransition(std::string headerText, std::string subtitleText) : GGAbstractAsset(sf::Vector2f(0, 0)), isDrawing(true)
{
	if (!font.loadFromFile("Assets/Fonts/Minimal5x7.ttf"))
	{
		std::cout << "Font load from file failure!" << endl;
	}
	header.setFont(font);
	subtitle.setFont(font);

	header.setString(headerText);
	header.setOrigin(header.getGlobalBounds().width / 2, header.getGlobalBounds().height / 2);
	header.setPosition(640, 275);
	header.setScale(2.5, 2.5);
	header.setFillColor(sf::Color(0xE6EBD6FF));

	subtitle.setString(subtitleText);
	subtitle.setOrigin(subtitle.getGlobalBounds().width / 2, subtitle.getGlobalBounds().height / 2);
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

void GGMinigameTransition::SetScale(sf::Vector2f scale)
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