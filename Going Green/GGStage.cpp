#include "GGStage.h"
GGStage::GGStage(GGView* gameView, GGView* gameOverView) : game(gameView), gameOver(gameOverView) {}
GGStage::~GGStage() {
	delete game;
	delete gameOver;
}
bool GGStage::Play() {
	game->Show();
}
bool GGStage::GameOver() {
	gameOver->Show();
}