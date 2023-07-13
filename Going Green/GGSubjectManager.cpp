#include "GGSubjectManager.h"
#include "TESTStage1.h"

GGSubjectManager::GGSubjectManager() {
	// add the views once implemented

}
GGSubjectManager::~GGSubjectManager() {}
void GGSubjectManager::PlayGame() {
	bool success;
	bool restart;
	int i = 0;
	while (i < stages.size()) { // we'll need to pass the window somehow
		success = true;
		restart = false;
		auto stage = stages[i];
		success = stage.Play();
		if (!success) {
			restart = stage.GameOver();
		}
		if (!restart) {
			i++;
		}
	}
}