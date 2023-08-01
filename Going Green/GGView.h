#ifndef __GGVIEW_H
#define __GGVIEW_H

#include "GGSubject.h"
#include "GGAbstractCtrl.h"
#include "GGAbstractModel.h"

class GGView : public GGSubject {
public:
	GGView(GGAbstractCtrl* controller, int stg = 0);
	virtual ~GGView();
	virtual bool Show(); /* unique controls and models for each game/stage - control creates the model */
	sf::Time GetElapsedTime();
	void SetStage(int stg);
	void SetCtrl(GGAbstractCtrl* controller);
	virtual int GetLastGame();

private:
	GGAbstractCtrl* ctrl;
	GGAbstractModel* model; // model has components that the view draws
	sf::Clock clock;
	int stage;
};

class GGCompositeView : public GGView {
public:
	GGCompositeView(int stg);
	virtual ~GGCompositeView();
	virtual bool Show() override;
	void AddView(GGView* view);
	void SetBackgroundMusic(std::string fileName);
	int GetLastGame() override;

private:
	std::vector<GGView*> views;
	GGMusicAsset* backgroundMusic;
	int stage;
	int game;
};
#endif