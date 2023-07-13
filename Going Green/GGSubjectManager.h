#ifndef __GGSUBJECTMANAGER_H
#define __GGSUBJECTMANAGER_H

#include "GGStage.h"

class GGSubjectManager {
public:
	GGSubjectManager();
	~GGSubjectManager();
	void PlayGame();

private:
	std::vector<GGStage> stages;
};

#endif