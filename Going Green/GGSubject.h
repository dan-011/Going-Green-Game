#ifndef __GGSUBJECT_H
#define __GGSUBJECT_H

#include "GGAbstractObserver.h"
#include <vector>
#include <SFML/Graphics.hpp>

class GGSubject {
public:
	virtual ~GGSubject();
	void AddObserver(GGAbstractObserver* obs);
	void Notify();
	sf::Event& GetEvent();
	void SetEvent(sf::Event evnt);

private:
	std::vector<GGAbstractObserver*> observers;
	sf::Event event;
};

#endif