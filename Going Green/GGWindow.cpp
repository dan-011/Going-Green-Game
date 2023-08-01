#include "GGWindow.h"

GGWindow::GGWindow() : window(sf::VideoMode(1280, 720), "Going Green", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize) {
	sf::Image iconImage;
	iconImage.loadFromFile("Assets/Animations/cannon_game/money_landed.png");
	window.setIcon(iconImage.getSize().x, iconImage.getSize().y, iconImage.getPixelsPtr());
}
GGWindow::~GGWindow() {}
GGWindow& GGWindow::Instance() {
	static GGWindow instance;
	return instance;
}
sf::RenderWindow& GGWindow::GetWindow() {
	return window;
}