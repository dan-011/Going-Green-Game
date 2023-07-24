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

    GGProjectileTickObserver projectileTickObs0(cannonView, cannonCtrl, 0);
    GGProjectileTickObserver projectileTickObs1(cannonView, cannonCtrl, 1);
    GGProjectileTickObserver projectileTickObs2(cannonView, cannonCtrl, 2);
    GGProjectileTickObserver projectileTickObs3(cannonView, cannonCtrl, 3);
    GGProjectileTickObserver projectileTickObs4(cannonView, cannonCtrl, 4);
    GGProjectileTickObserver projectileTickObs5(cannonView, cannonCtrl, 5);
    GGProjectileTickObserver projectileTickObs6(cannonView, cannonCtrl, 6);
    GGProjectileTickObserver projectileTickObs7(cannonView, cannonCtrl, 7);
    GGProjectileTickObserver projectileTickObs8(cannonView, cannonCtrl, 8);
    GGProjectileTickObserver projectileTickObs9(cannonView, cannonCtrl, 9);
    subjMgr.AddStage(testStage);


    subjMgr.PlayGame();
    return 0;
}