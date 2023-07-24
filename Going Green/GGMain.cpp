#include <SFML/Graphics.hpp>
#include "GGSubjectManager.h"
#include "GGAbstractAsset.h"
#include "GGIndivObservers.h"

int main()
{
    GGSubjectManager subjMgr;

    /* Test Pump Game */
    GGCannonGameCtrl cannonCtrl;
    GGTestGameOverCtrl testGameOverCtrl;
    GGView cannonView(&cannonCtrl);
    GGView testGameOverView(&testGameOverCtrl);
    GGStage testStage(&cannonView, &testGameOverView);

    GGClockMSObserver clockMSObs(cannonView, cannonCtrl);
    GGTestGameOverTick gameOverTickObs(testGameOverView, testGameOverCtrl);
    GGRestartGameObserver restartGameObs(testGameOverView, testGameOverCtrl);
    GGCannonTickObserver cannonClickObs(cannonView, cannonCtrl);
    GGCannonFireObserver cannonFireObs(cannonView, cannonCtrl);
    GGCannonMoveObserver cannonMoveObs(cannonView, cannonCtrl);
    GGProjectileTickObserver projectileTickObs(cannonView, cannonCtrl, 0);
    subjMgr.AddStage(testStage);


    subjMgr.PlayGame();
    return 0;
}