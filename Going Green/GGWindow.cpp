#include "GGWindow.h"

GGWindow::GGWindow() : window(sf::VideoMode(1280, 720), "Going Green", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize) {}
GGWindow::~GGWindow() {}
GGWindow& GGWindow::Instance() {
	static GGWindow instance;
	return instance;
}
sf::RenderWindow& GGWindow::GetWindow() {
	return window;
}