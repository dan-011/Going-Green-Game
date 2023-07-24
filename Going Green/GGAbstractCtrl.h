#ifndef __GGABSTRACTCTRL_H
#define __GGABSTRACTCTRL_H

#include "GGAbstractModel.h"

class GGAbstractCtrl {
public:
	GGAbstractCtrl();
	virtual ~GGAbstractCtrl();
	virtual GGAbstractModel* GetModel() = 0;
	virtual void ResetMdl();
};

class GGPumpCtrl : public GGAbstractCtrl {
public:
	GGPumpCtrl();
	virtual ~GGPumpCtrl();
	virtual GGAbstractModel* GetModel() override;
	virtual void AnimatePump();
	virtual void AnimateOil();
	virtual void PumpClicked();
	virtual bool IsAnimatingPump();
	virtual void CheckGameWon();
	virtual void EndGame();
	virtual void WinGame();
	virtual int GetQueuedPumps();

private:
	GGPumpModel pumpMdl;

};

class GGNewsCtrl : public GGAbstractCtrl {
public:
	GGNewsCtrl();
	virtual ~GGNewsCtrl();
	virtual GGAbstractModel* GetModel() override;
	virtual void EndGame();
	virtual void WinGame();
	virtual bool IsAnimatingButton();
	virtual void ClearButtonAnim();
	virtual void PressButton(int button);
	virtual void ProcessClick(sf::Vector2f mousePos);
private:
	GGNewsModel newsMdl;
};
class GGTestGameOverCtrl : public GGAbstractCtrl {
public:
	GGTestGameOverCtrl();
	~GGTestGameOverCtrl();
	virtual GGAbstractModel* GetModel() override;
	virtual void AnimateScreen();
	virtual void RestartGame();

private:
	GGTestGameOverModel gOMdl;
};

#endif
