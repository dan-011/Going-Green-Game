#ifndef __GGABSTRACTASSET_H
#define __GGABSTRACTASSET_H

#include <SFML/Graphics.hpp>
#include "GGWindow.h"
#include <string>

class GGAbstractAsset {
public:
	GGAbstractAsset(sf::Vector2f pos);
	virtual ~GGAbstractAsset();
	void SetPos(sf::Vector2f pos);
	sf::Vector2f GetPos();
	virtual void Draw() = 0; // TODO: refactor
	virtual void NextAnimation();
	virtual void SetScale(sf::Vector2f scale) = 0;

private:
	sf::Vector2f position;
};

class GGSheetAsset : public GGAbstractAsset {
public:
	GGSheetAsset(sf::Vector2f pos, const std::string fileName, sf::Vector2u dims, bool animateOnce = false, bool start = true);
	virtual ~GGSheetAsset();
	virtual void Draw() override;
	virtual void NextAnimation() override;
	virtual bool AnimationCompleted();
	virtual void SetCurFrame(int frame);
	virtual int GetCurFrame();
	virtual void SetScale(sf::Vector2f scale) override;
	virtual void SetStart(bool start);
	virtual bool CheckFinishedAnimating();
	virtual void SetFinishedAnimating(bool finished);
	virtual sf::RectangleShape GetRect();

private:
	sf::Texture assetTexture;
	sf::IntRect assetBlock;
	sf::RectangleShape assetBody;
	sf::Vector2u dimensions;
	int curFrame;
	bool animOnce;
	bool finishedAnimating;
	bool started;
};

class GGListAsset : public GGAbstractAsset {
public:
	GGListAsset(sf::Vector2f pos, std::vector<std::string> fileNames);
	virtual ~GGListAsset();
	virtual void Draw() override;
	virtual void NextAnimation() override;
	virtual bool AnimationCompleted();
	virtual void SetCurFrame(int frame);
	virtual int GetCurFrame();
	virtual void SetScale(sf::Vector2f scale) override;
private:
	std::vector<sf::Texture*> assetTextures;
	sf::RectangleShape assetBody;
	int curFrame;
};

class GGMinigameTransition : public GGAbstractAsset {
public:
	GGMinigameTransition(std::string headerText, std::string subtitleText);
	//virtual ~GGMinigameTransition();
	virtual void Draw() override;
	virtual void SetScale(sf::Vector2f scale) override;
	virtual void SetDrawing(bool drawing);
	virtual bool GetDrawing();
private:
	sf::Font font;
	sf::Text header;
	sf::Text subtitle;
	sf::RectangleShape background;
	bool isDrawing;
};

class GGButton : public GGAbstractAsset {
public:
	GGButton(sf::Vector2f pos, std::string text);
	virtual void Draw() override;
	virtual void SetScale(sf::Vector2f scale) override;
	virtual void SetClicked(bool click);
	virtual bool GetClicked();
	virtual sf::RectangleShape GetRect();
	//virtual bool SetText();
private:
	sf::Text buttonText;
	sf::Font font;
	bool isClicked;
	GGSheetAsset buttonBody;
};
#endif