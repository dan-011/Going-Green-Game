#ifndef __GGABSTRACTMODEL_H
#define __GGABSTRACTMODEL_H

#include "GGAbstractAsset.h"
#include <vector>

class GGAbstractModel {
public:
	GGAbstractModel();
	virtual ~GGAbstractModel();
	std::vector<GGAbstractAsset*>& GetAssets();
	void AddAsset(GGAbstractAsset* asset);
	bool GetContinueGame();
	void SetContinueGame(bool isContinuing);
	bool GetSuccess();
	void SetSuccess(bool success);
	virtual void ResetData() = 0;

private:
	std::vector<GGAbstractAsset*> assets;
	bool continueGame;
	bool wasSuccess;
};

class GGPumpModel : public GGAbstractModel {
public:
	GGPumpModel();
	virtual ~GGPumpModel();
	GGSheetAsset* GetPump();
	GGSheetAsset* GetOil();
	GGMinigameTransition* GetTransition();
	int GetNumPumps();
	void SetNumPumps(int nPumps);
	virtual void ResetData() override;
	bool PumpMaxReached();
	void IncrementPumps();

private:
	GGSheetAsset* pump; // change to object
	GGSheetAsset* oil;
	GGMinigameTransition* transition;
	GGStaticAsset* background;
	int maxPumps;
	int numPumps;
	int goalPumps;
	int totalPumps;
	bool maxedOut;
};

class GGNewsModel : public GGAbstractModel {
public:
	GGNewsModel(int maxReports);
	virtual ~GGNewsModel();
	GGButton* GetButton(int index);
	void ResetData();
private:
	GGButton* button1;
	GGButton* button2;
	int goalReports;
	int numReports;
};

class GGTestGameOverModel : public GGAbstractModel {
public:
	GGTestGameOverModel();
	~GGTestGameOverModel();
	GGListAsset* GetGameOverAsset();
	virtual void ResetData() override;

private:
	GGListAsset* gameOverScreen; // change to object
};
#endif