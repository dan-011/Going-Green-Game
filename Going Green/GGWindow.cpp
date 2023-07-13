#include "GGWindow.h"

GGWindow::GGWindow() : window(sf::VideoMode(720, 1280), "Going Green", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize) {}
GGWindow::~GGWindow() {}
GGWindow& GGWindow::Instance() {
	static GGWindow instance;
	return instance;
}
sf::RenderWindow& GGWindow::GetWindow() {
	return window;
}