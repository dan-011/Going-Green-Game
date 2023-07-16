#include <SFML/Graphics.hpp>
#include "GGSubjectManager.h"
#include "GGAbstractAsset.h"
#include "GGIndivObservers.h"

int main()
{
    GGSubjectManager subjMgr;

    /* Test Pump Game */
    GGPumpCtrl testCtrl;
    GGTestGameOverCtrl testGameOverCtrl;
    GGView testView(&testCtrl);
    GGView testGameOverView(&testGameOverCtrl);
    GGStage testStage(&testView, &testGameOverView);
    GGPumpClickObserver pumpClickObs(testView, testCtrl);
    GGPumpTickObserver pumptickObs(testView, testCtrl, sf::milliseconds(55));
    GGTestGameOverTick gameOberTickObs(testGameOverView, testGameOverCtrl);
    GGEndGameObserver endGameObs(testView, testCtrl);
    GGRestartGameObserver restartGameObs(testGameOverView, testGameOverCtrl);
    subjMgr.AddStage(testStage);


    subjMgr.PlayGame();
    return 0;
}