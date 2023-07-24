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

void GGSheetAsset::SetScale(sf::Vector2f scale)
{
	assetBody.setScale(scale);
}

sf::RectangleShape GGSheetAsset::GetRect()
{
	return assetBody;
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

GGButton::GGButton(sf::Vector2f pos, std::string text) : GGAbstractAsset(pos), isClicked(false), buttonBody(pos, "Assets/Animations/tv_game/button.png", sf::Vector2u(1, 1))
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
	buttonBody.SetScale(sf::Vector2f(4, 4));
	//buttonText.setScale(sf::Vector2f(4, 4));
	buttonText.setFillColor(sf::Color(0x000000FF));
}
void GGButton::Draw()
{
	buttonBody.Draw();
	GGWindow::Instance().GetWindow().draw(buttonText);
}
void GGButton::SetScale(sf::Vector2f scale)
{
	buttonBody.SetScale(scale);
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

sf::RectangleShape GGButton::GetRect()
{
	return buttonBody.GetRect();
}