#include "GGView.h"
#include "GGWindow.h"

GGView::GGView(GGAbstractCtrl* controller) : ctrl(controller) {
	model = ctrl->GetModel();
}
GGView::~GGView() {}
bool GGView::Show() {
	sf::RenderWindow& window = GGWindow::Instance().GetWindow();
	ctrl->ResetMdl();
	while (model->GetContinueGame()) {
		window.pollEvent(GetEvent()); // check to make sure this works as intended
		Notify();

		window.clear(sf::Color(255, 255, 255));

		int i = 0;
		for (auto asset : model->GetAssets()) {
			asset->Draw();
			i++;
		}
		window.display();
	}
	return model->GetSuccess();
}
sf::Time GGView::GetElapsedTime() {
	return clock.getElapsedTime();
}