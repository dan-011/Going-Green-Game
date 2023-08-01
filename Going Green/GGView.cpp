#include "GGView.h"
#include "GGWindow.h"

GGView::GGView(GGAbstractCtrl* controller, int stg) : ctrl(controller), stage(stg), model(NULL) {
	if(ctrl != NULL) model = ctrl->GetModel();
}
GGView::~GGView() {}
bool GGView::Show() {
	sf::RenderWindow& window = GGWindow::Instance().GetWindow();
	ctrl->ResetMdl();
	if (stage > 0) model->StageOne();
	if (stage > 1) model->StageTwo();
	if (stage > 2) model->StageThree();
	GGMusicAsset* backgroundMusic = model->GetBackgroundMusic();
	if (backgroundMusic != NULL) {
		backgroundMusic->Play();
	}
	while (model->GetContinueGame()) {
		bool validEvent = window.pollEvent(GetEvent()); // check to make sure this works as intended
		if (validEvent && GetEvent().type == sf::Event::Closed) {
			window.close();
			exit(0);
		}
		Notify();

		window.clear(sf::Color(255, 255, 255));

		for (auto asset : model->GetAssets()) {
			asset->Draw();
		}
		window.display();
	}
	if (backgroundMusic != NULL) {
		backgroundMusic->Stop();
	}
	return model->GetSuccess();
}
sf::Time GGView::GetElapsedTime() {
	return clock.getElapsedTime();
}
void GGView::SetStage(int stg) {
	stage = stg;
}
void GGView::SetCtrl(GGAbstractCtrl* controller) {
	GGAbstractCtrl* oldCtrl = ctrl;
	ctrl = controller;
	if (oldCtrl != NULL) delete oldCtrl;
}
int GGView::GetLastGame() {
	return -1;
}

GGCompositeView::GGCompositeView(int stg) : GGView(NULL), stage(stg), backgroundMusic(NULL), game(0) {}
GGCompositeView::~GGCompositeView() {}
bool GGCompositeView::Show() {
	if (backgroundMusic != NULL) {
		backgroundMusic->Play();
	}
	for (auto view : views) {
		view->SetStage(stage);
		game++;
		bool res = view->Show();
		if (!res) {
			if (backgroundMusic != NULL) {
				backgroundMusic->Stop();
			}
			return res;
		}
	}
	if (backgroundMusic != NULL) {
		backgroundMusic->Stop();
	}
	return true;
}
void GGCompositeView::AddView(GGView* view) {
	views.push_back(view);
}
void GGCompositeView::SetBackgroundMusic(std::string fileName) {
	GGMusicAsset* oldMusic = backgroundMusic;
	backgroundMusic = new GGMusicAsset(fileName);
	if (oldMusic != NULL) delete oldMusic;
}
int GGCompositeView::GetLastGame() {
	return game;
}