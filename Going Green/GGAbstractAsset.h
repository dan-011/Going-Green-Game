#ifndef __GGABSTRACTASSET_H
#define __GGABSTRACTASSET_H

#include <SFML/Graphics.hpp>
#include "GGWindow.h"
#include <string>

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
	virtual sf::Vector2u GetTextureSize() = 0;
	virtual sf::FloatRect GetGlobalBounds();

protected:
	sf::Sprite& GetSprite();

private:
	sf::Sprite assetSprite;
};

class GGSheetAsset : public GGSpriteAsset {
public:
	GGSheetAsset(sf::Vector2f pos, const std::string fileName, sf::Vector2u dims, bool animateOnce = false, bool start = true, int totalFrames = 0);
	virtual ~GGSheetAsset();
	virtual void Draw() override;
	virtual void NextAnimation() override;
	virtual bool AnimationCompleted();
	virtual void SetCurFrame(int frame);
	virtual int GetCurFrame();
	virtual void SetStart(bool start);
	virtual bool CheckFinishedAnimating();
	virtual void SetFinishedAnimating(bool finished);
	virtual sf::Vector2u GetTextureSize() override;

private:
	sf::Texture assetTexture;
	sf::IntRect assetBlock;
	//sf::RectangleShape assetBody;
	sf::Vector2u dimensions;
	int curFrame;
	bool animOnce;
	bool finishedAnimating;
	bool started;
	int numFrames;
};

class GGListAsset : public GGSpriteAsset {
public:
	GGListAsset(sf::Vector2f pos, std::vector<std::string> fileNames);
	virtual ~GGListAsset();
	virtual void NextAnimation();
	virtual bool AnimationCompleted();
	virtual void SetCurFrame(int frame);
	virtual int GetCurFrame();
	virtual sf::Vector2u GetTextureSize() override;
private:
	std::vector<sf::Texture*> assetTextures;
	sf::Sprite assetSprite;
	int curFrame;
};

class GGMinigameTransition : public GGSpriteAsset {
public:
	GGMinigameTransition(std::string headerText, std::string subtitleText);
	//virtual ~GGMinigameTransition();
	virtual void Draw() override;
	virtual void Scale(sf::Vector2f dims) override;
	virtual void SetDrawing(bool drawing);
	virtual bool GetDrawing();
	virtual sf::Vector2u GetTextureSize() override;
private:
	sf::Font font;
	sf::Text header;
	sf::Text subtitle;
	sf::RectangleShape background;
	bool isDrawing;
};

class GGButton : public GGSpriteAsset {
public:
	GGButton(sf::Vector2f pos, std::string text);
	virtual void Draw() override;
	virtual void SetClicked(bool click);
	virtual void SetText(std::string text);
	virtual void Scale(sf::Vector2f dims) override;
	virtual bool GetClicked();
	virtual sf::Vector2u GetTextureSize() override;
	virtual sf::FloatRect GetGlobalBounds() override;
	virtual void SetCurFrame(int frame);
private:
	sf::Text buttonText;
	sf::Font font;
	bool isClicked;
	GGSheetAsset buttonBody;
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
#endif