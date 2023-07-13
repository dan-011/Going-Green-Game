#include "GGSubject.h"
GGSubject::~GGSubject() {}
void GGSubject::AddObserver(GGAbstractObserver* obs) {
	observers.push_back(obs);
}
void GGSubject::Notify() {
	for (auto obs : observers) {
		obs->Update();
	}
}

sf::Event& GGSubject::GetEvent() {
	return event;
}
void GGSubject::SetEvent(sf::Event evnt) {
	event = evnt;
}