#include <SFML/Graphics.hpp>
#include "GGSubjectManager.h"
#include "GGAbstractAsset.h"
#include "GGIndivObservers.h"

int main()
{
    GGSubjectManager subjMgr;

    /* Test Pump Game */
    GGPumpCtrl testCtrl;
    GGNewsCtrl newsCtrl;
    GGTestGameOverCtrl testGameOverCtrl;
    GGView testView(&testCtrl);
    GGView newsView(&newsCtrl);
    GGView testGameOverView(&testGameOverCtrl);
    GGStage testStage(&testView, &testGameOverView);
    GGStage newsStage(&newsView, &testGameOverView);
    GGPumpClickObserver pumpClickObs(testView, testCtrl);
    GGPumpTickObserver pumptickObs(testView, testCtrl, sf::milliseconds(55));
    GGTestGameOverTick gameOberTickObs(testGameOverView, testGameOverCtrl);
    GGEndGameObserver endGameObs(testView, testCtrl);
    GGRestartGameObserver restartGameObs(testGameOverView, testGameOverCtrl);
    GGNewsButtonTickObserver buttonTickObs(newsView, newsCtrl, sf::milliseconds(55));
    GGNewsButtonClickObserver buttonClickObs(newsView, newsCtrl);
    subjMgr.AddStage(newsStage);
    subjMgr.AddStage(testStage);

    subjMgr.PlayGame();
    return 0;
}