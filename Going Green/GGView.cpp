#include "GGView.h"
#include "GGWindow.h"

GGView::GGView(GGAbstractCtrl* controller) : ctrl(controller) {
	model = ctrl->GetModel();
}
GGView::~GGView() {}
bool GGView::Show() {
	sf::RenderWindow& window = GGWindow::Instance().GetWindow();
	ctrl->ResetMdl();
	model->StageOne();
	// model->StageTwo();
	// model->StageThree();
	GGMusicAsset* backgroundMusic = model->GetBackgroundMusic();
	if (backgroundMusic != NULL) {
		backgroundMusic->Play();
	}
	model->GetTimer()->StartTimer();
	while (model->GetContinueGame()) {
		window.pollEvent(GetEvent()); // check to make sure this works as intended
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