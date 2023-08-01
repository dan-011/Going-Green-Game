#ifndef __GGSUBJECTMANAGER_H
#define __GGSUBJECTMANAGER_H

#include "GGStage.h"

class GGSubjectManager {
public:
	GGSubjectManager();
	~GGSubjectManager();
	void PlayGame();
	void AddStage(GGStage stage);

private:
	std::vector<GGStage> stages;
	GGSFXAsset loseJingle;
	GGSFXAsset winJingle;
	GGSecretEndingCtrl secretEndingCtrl;
	GGView secretEndingView;
};

#endif