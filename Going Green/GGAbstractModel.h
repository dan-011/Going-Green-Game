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
	GGTextAsset* GetQuestionText();
	int GetNumAnswers();
	void SetNumAnswers(int nAnswers);
	bool GoalMet();
	void ResetData();
	GGMinigameTransition* GetTransition();
private:
	GGButton* button1;
	GGButton* button2;
	GGMinigameTransition* transition;
	GGStaticAsset* background;
	GGStaticAsset* frame;
	GGStaticAsset* questionBubble;
	GGTextAsset* questionText;
	int goalReports;
	int numReports;
};

class GGStageTransitionModel : public GGAbstractModel
{
public:
	GGStageTransitionModel(std::string tableSource, std::string envelopeSource, std::string letterSource);
	virtual ~GGStageTransitionModel();
	GGStaticAsset* GetEnvelope();
	GGStaticAsset* GetLetter();
	bool GetLetterMoved();
	void SetLetterMoved(bool moved);
	float GetLetterVelocity();
	void SetLetterVelocity(float velocity);
	float GetLetterDeceleration();
	float GetEnvelopeVelocity();
	void SetEnvelopeVelocity(float velocity);
	float GetEnvelopeDeceleration();
	void ResetData() override;

private:
	GGStaticAsset* table;
	GGStaticAsset* envelope;
	GGStaticAsset* letter;
	float letterVelocity;
	const float letterDeceleration;
	float envelopeVelocity;
	const float envelopeDeceleration;
	bool letterMoved;
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