#ifndef __GGABSTRACTASSET_H
#define __GGABSTRACTASSET_H

#include <SFML/Graphics.hpp>
#include "GGWindow.h"
#include <string>
#include <stdio.h>

class GGAbstractAsset {
public:
	GGAbstractAsset(sf::Vector2f pos);
	virtual ~GGAbstractAsset();
	virtual void SetPos(sf::Vector2f pos);
	sf::Vector2f GetPos();
	virtual void Draw() = 0; // TODO: refactor

private:
	sf::Vector2f position;

};

class GGSpriteAsset : public GGAbstractAsset {
public:
	GGSpriteAsset(sf::Vector2f pos);
	~GGSpriteAsset();
	virtual void SetPos(sf::Vector2f pos) override;
	virtual void Scale(sf::Vector2f dims); // refactor
	virtual void SetTexture(sf::Texture& assetTexture);
	virtual void SetAssetBlock(sf::IntRect& assetBlock);
	virtual void SetOrigin(float width, float height);
	virtual void SetOrigin(sf::Vector2f origin);
	virtual sf::Vector2f GetOrigin();
	virtual void SetRotation(float degrees);
	virtual float GetRotation();
	virtual void NextAnimation();
	virtual void Draw() override;
	virtual sf::FloatRect GetBoundingBox();
	virtual sf::Vector2u GetTextureSize() = 0;

protected:
	sf::Sprite& GetSprite();

private:
	sf::Sprite assetSprite;
};

class GGSheetAsset : public GGSpriteAsset {
public:
	GGSheetAsset(sf::Vector2f pos, const std::string fileName, sf::Vector2u dims, bool animateOnce = false, int totalFrames = 0);
	virtual ~GGSheetAsset();
	virtual void Draw() override;
	virtual void NextAnimation() override;
	virtual bool AnimationCompleted();
	virtual void SetCurFrame(int frame);
	virtual int GetCurFrame();
	virtual sf::Vector2u GetTextureSize() override;

private:
	sf::Texture assetTexture;
	sf::IntRect assetBlock;
	// sf::RectangleShape assetBody;
	sf::Vector2u dimensions;
	int curFrame;
	bool animOnce;
	bool finishedAnimating;
	int numFrames;
};

class GGListAsset : public GGSpriteAsset {
public:
	GGListAsset(sf::Vector2f pos, std::vector<std::string> fileNames);
	virtual ~GGListAsset();
	virtual void NextAnimation() override;
	virtual bool AnimationCompleted();
	virtual void SetCurFrame(int frame);
	virtual int GetCurFrame();
	virtual sf::Vector2u GetTextureSize() override;
private:
	std::vector<sf::Texture*> assetTextures;
	// sf::RectangleShape assetBody;
	sf::Sprite assetSprite;
	int curFrame;
};

class GGStaticAsset : public GGSpriteAsset {
public:
	GGStaticAsset(sf::Vector2f pos, const std::string fileName);
	virtual ~GGStaticAsset();
	virtual sf::Vector2u GetTextureSize() override;

private:
	sf::Texture assetTexture;
	// sf::RectangleShape assetBody;
};

class GGTextAsset : public GGAbstractAsset {
public:
	GGTextAsset(sf::Vector2f pos, unsigned int size, const std::string fontFileName, sf::Color clr);
	~GGTextAsset();
	void SetText(std::string txt);
	virtual void Draw() override;
	virtual void SetPos(sf::Vector2f pos) override;
	void SetSize(int sz);

private:
	sf::Font assetFont;
	sf::Text assetText;

};

class GGTimerAsset : public GGTextAsset {
public:
	GGTimerAsset(sf::Vector2f pos, unsigned int size, const std::string fontFileName, int sec, int ms, sf::Color clr); // Minimal3x5.ttf
	~GGTimerAsset();
	void TickSec();
	void TickMS();
	bool TimerCompleted();
	void RestartTimer();
	void SetTimer(sf::Vector2u time);
	void StartTimer();
	void StopTimer();
	bool GetTimerStarted();

private:
	char timerStr[128];
	int second;
	int millisecond;
	sf::Vector2u startTime;
	bool timerStarted;

};

class GGAudioAsset : public GGAbstractAsset {
};
#endif