#ifndef __GGABSTRACTASSET_H
#define __GGABSTRACTASSET_H

#include <SFML/Graphics.hpp>

class GGAbstractAsset {
public:
	GGAbstractAsset(sf::Vector2f pos);
	virtual ~GGAbstractAsset();
	void SetPos(sf::Vector2f pos);
	virtual void Draw() = 0;

private:
	sf::Vector2f position;
};

#endif