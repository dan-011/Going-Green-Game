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

GGSheetAsset::GGSheetAsset(sf::Vector2f pos, const std::string fileName, sf::Vector2u dims, bool animateOnce) : GGAbstractAsset(pos), dimensions(dims), curFrame(0), animOnce(animateOnce), finishedAnimating(false) {
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
	if (finishedAnimating && animOnce) return;
	GGWindow::Instance().GetWindow().draw(assetBody);
}
void GGSheetAsset::NextAnimation() {
	if (finishedAnimating && animOnce) return;
	int numFrames = dimensions.x * dimensions.y;
	curFrame++;
	if (curFrame == numFrames) {
		curFrame = 0;
		finishedAnimating = true;
	}
	int row = curFrame / dimensions.x;
	int col = curFrame % dimensions.x;
	assetBlock.top = row * assetBlock.height;
	assetBlock.left = col * assetBlock.width;

	assetBody.setTextureRect(assetBlock);
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