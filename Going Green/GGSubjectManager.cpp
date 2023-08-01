#include "GGSubjectManager.h"

GGSubjectManager::GGSubjectManager(): loseJingle("Assets/Music/Losejingle.wav"), winJingle("Assets/Music/WinJingle.wav"), secretEndingView(&secretEndingCtrl) {}
GGSubjectManager::~GGSubjectManager() {}
void GGSubjectManager::PlayGame() {
	bool success;
	bool restart;
	int i = 0;
	while (i < stages.size()) {
		success = true;
		restart = false;
		auto stage = stages[i];
		success = stage.Play();
		if (!success) {
			loseJingle.Play();
			while (loseJingle.IsPlaying()) {}
			int lastGame = stage.GetLastGame();
			if (lastGame == 2 && i == 1) {
				secretEndingView.Show();
				break;
			}
			else {
				restart = stage.GameOver();
			}
		}
		if (!restart) {
			i++;
		}
		if (i > 1 && success) {
			winJingle.Play();
			while (winJingle.IsPlaying()) {}
		}
	}
}
void GGSubjectManager::AddStage(GGStage stage) {
	stages.push_back(stage);
}