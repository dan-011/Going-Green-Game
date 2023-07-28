#include <SFML/Graphics.hpp>
#include "GGSubjectManager.h"
#include "GGAbstractAsset.h"
#include "GGIndivObservers.h"

int main()
{
    GGSubjectManager subjMgr;

    GGTitleScreenCtrl titleScreenCtrl;
    GGView titleScreenView(&titleScreenCtrl);
    GGStage titleStage(&titleScreenView);
    GGExitTitleScreenObserver titleScreenObs(titleScreenView, titleScreenCtrl);
    GGStartTextTickObserver startTextTickObs(titleScreenView, titleScreenCtrl);
    subjMgr.AddStage(titleStage);

    // Cannon Game
    GGCannonGameCtrl cannonCtrl;
    GGView cannonView(&cannonCtrl);
    GGClockMSObserver clockMSObs(cannonView, cannonCtrl);
    GGCannonTickObserver cannonClickObs(cannonView, cannonCtrl);
    GGCannonFireObserver cannonFireObs(cannonView, cannonCtrl);
    GGCannonMoveObserver cannonMoveObs(cannonView, cannonCtrl);
    GGProjectileTickObserver projectileTickObs0(cannonView, cannonCtrl, 0, 1);
    GGProjectileTickObserver projectileTickObs1(cannonView, cannonCtrl, 1, 1);
    GGProjectileTickObserver projectileTickObs2(cannonView, cannonCtrl, 2, 1);
    GGProjectileTickObserver projectileTickObs3(cannonView, cannonCtrl, 3, 1);
    GGProjectileTickObserver projectileTickObs4(cannonView, cannonCtrl, 4, 1);
    GGProjectileTickObserver projectileTickObs5(cannonView, cannonCtrl, 5, 1);
    GGProjectileTickObserver projectileTickObs6(cannonView, cannonCtrl, 6, 1);
    GGProjectileTickObserver projectileTickObs7(cannonView, cannonCtrl, 7, 1);
    GGProjectileTickObserver projectileTickObs8(cannonView, cannonCtrl, 8, 1);
    GGProjectileTickObserver projectileTickObs9(cannonView, cannonCtrl, 9, 1);
    GGProjectileTickObserver projectileTickObs10(cannonView, cannonCtrl, 10, 2);
    GGProjectileTickObserver projectileTickObs11(cannonView, cannonCtrl, 11, 2);
    GGProjectileTickObserver projectileTickObs12(cannonView, cannonCtrl, 12, 2);
    GGProjectileTickObserver projectileTickObs13(cannonView, cannonCtrl, 13, 2);
    GGProjectileTickObserver projectileTickObs14(cannonView, cannonCtrl, 14, 2);
    GGProjectileTickObserver projectileTickObs15(cannonView, cannonCtrl, 15, 3);
    GGProjectileTickObserver projectileTickObs16(cannonView, cannonCtrl, 16, 3);
    GGProjectileTickObserver projectileTickObs17(cannonView, cannonCtrl, 17, 3);
    GGProjectileTickObserver projectileTickObs18(cannonView, cannonCtrl, 18, 3);
    GGProjectileTickObserver projectileTickObs19(cannonView, cannonCtrl, 19, 3);
    GGTargetTickObserver targetTickObs0(cannonView, cannonCtrl, 0, 1);
    GGTargetTickObserver targetTickObs1(cannonView, cannonCtrl, 1, 1);
    GGTargetTickObserver targetTickObs2(cannonView, cannonCtrl, 2, 1);
    GGTargetTickObserver targetTickObs3(cannonView, cannonCtrl, 3, 2);
    GGTargetTickObserver targetTickObs4(cannonView, cannonCtrl, 4, 2);
    GGTargetTickObserver targetTickObs5(cannonView, cannonCtrl, 5, 3);
    GGTargetTickObserver targetTickObs6(cannonView, cannonCtrl, 6, 3);
    GGTargetTickObserver targetTickObs7(cannonView, cannonCtrl, 7, 3);
    GGTargetTickObserver targetTickObs8(cannonView, cannonCtrl, 8, 3);
    GGTargetTickObserver targetTickObs9(cannonView, cannonCtrl, 9, 3);

    // Stage One Region
    GGGameOverCtrl gameOverCtrlStageOne;
    gameOverCtrlStageOne.GetModel()->StageOne();
    GGView gameOverStageOneView(&gameOverCtrlStageOne);
    GGRestartGameObserver restartGameObsOne(gameOverStageOneView, gameOverCtrlStageOne);

    GGCompositeView stageOneView(1);
    stageOneView.SetBackgroundMusic("Assets/Music/MainThemeLoop1.wav");
    stageOneView.AddView(&cannonView);
    stageOneView.AddView(&cannonView);
    stageOneView.AddView(&cannonView);

    // Stage One
    GGStage stageOne(&stageOneView, &gameOverStageOneView);
    subjMgr.AddStage(stageOne);


    GGGameOverCtrl gameOverCtrlStageTwo;
    gameOverCtrlStageTwo.GetModel()->StageTwo();
    GGView gameOverStageTwoView(&gameOverCtrlStageTwo);
    GGRestartGameObserver restartGameObsTwo(gameOverStageTwoView, gameOverCtrlStageTwo);

    GGGameOverCtrl gameOverCtrlStageThree;
    gameOverCtrlStageThree.GetModel()->StageThree();
    GGView gameOverStageThreeView(&gameOverCtrlStageThree);
    GGRestartGameObserver restartGameObsThree(gameOverStageThreeView, gameOverCtrlStageThree);


    /* Test Pump Game */

    GGStageFourCtrl stageFourCtrl;
    GGView stageFourView(&stageFourCtrl);
    GGStage stageFour(&stageFourView);
    GGStageFourSwitchObserver stageFourSwitchObs(stageFourView, stageFourCtrl);
    subjMgr.AddStage(stageFour);

    subjMgr.PlayGame();
    return 0;
}