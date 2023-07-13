#ifndef __GGSTAGE_H
#define __GGSTAGE_H

#include "GGSubject.h"
#include "GGView.h"

class GGStage {
public:
	GGStage(GGView* gameView, GGView* gameOverView);
	virtual ~GGStage();
	virtual bool Play();
	virtual bool GameOver();

private:
	GGView* game;
	GGView* gameOver;
};

#endif