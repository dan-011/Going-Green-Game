#include "GGStage.h"
GGStage::GGStage(GGView* gameVw, GGView* gameOverVw) : gameView(gameVw), gameOverView(gameOverVw) {}
GGStage::~GGStage() {}
bool GGStage::Play() {
	return gameView->Show();
}
bool GGStage::GameOver() {
	return gameOverView->Show();
}