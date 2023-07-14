#ifndef __GGABSTRACTASSET_H
#define __GGABSTRACTASSET_H

#include <SFML/Graphics.hpp>
#include "GGWindow.h"

class GGAbstractAsset {
public:
	GGAbstractAsset(sf::Vector2f pos);
	virtual ~GGAbstractAsset();
	void SetPos(sf::Vector2f pos);
	virtual void Draw() = 0;
	virtual void NextAnimation();

private:
	sf::Vector2f position;
};


class TestCharacter : public GGAbstractAsset {
public:
	TestCharacter(sf::Vector2f pos);
	virtual ~TestCharacter();
	virtual void Draw() override;
	virtual void NextAnimation() override;

private:

};

#endif