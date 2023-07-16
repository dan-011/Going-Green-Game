#include "GGStage.h"
GGStage::GGStage(GGView* gameView, GGView* gameOverView) : game(gameView), gameOver(gameOverView) {}
GGStage::~GGStage() {}
bool GGStage::Play() {
	return game->Show();
}
bool GGStage::GameOver() {
	return gameOver->Show();
}