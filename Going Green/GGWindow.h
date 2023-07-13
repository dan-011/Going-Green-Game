#ifndef __GGWINDOW_H
#define __GGWINDOW_H

#include <SFML/Graphics.hpp>

class GGWindow {
public:
	~GGWindow();
	static GGWindow& Instance();
	sf::RenderWindow& GetWindow();

private:
	GGWindow();
	sf::RenderWindow window;
};

#endif