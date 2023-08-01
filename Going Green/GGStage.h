#ifndef __GGSTAGE_H
#define __GGSTAGE_H

#include "GGSubject.h"
#include "GGView.h"

class GGStage {
public:
	GGStage(GGView* gameVw, GGView* gameOverVw = NULL);
	virtual ~GGStage();
	virtual bool Play();
	virtual bool GameOver();
	int GetLastGame();

private:
	GGView* gameView;
	GGView* gameOverView;
};

#endif