#include <SFML/Graphics.hpp>
#include "GGSubjectManager.h"
#include "GGAbstractAsset.h"
#include "GGIndivObservers.h"

void SetRandomGameOrder(GGCompositeView& compView, std::vector<GGView*> views) {
    srand((unsigned int) time(NULL));
    while (views.size() > 0) {
        int index = rand() % views.size();
        compView.AddView(views[index]);
        views.erase(views.begin() + index);
    }
}

int main()
{
    GGSubjectManager subjMgr;

    GGTitleScreenModel titleScreenModel;
    GGBookendsCtrl titleScreenCtrl(&titleScreenModel);
    GGView titleScreenView(&titleScreenCtrl);
    GGStage titleStage(&titleScreenView);
    GGContinueGameObserver titleScreenObs(titleScreenView, titleScreenCtrl, sf::Keyboard::Enter);
    GGBookendsTextTickObserver startTextTickObs(titleScreenView, titleScreenCtrl);
    subjMgr.AddStage(titleStage);

    // Letter Cutscene
    GGStageTransitionCtrl stageTransitionCtrl;
    GGView stageTransitionView(&stageTransitionCtrl);

    GGStageTransitionClickObserver stageTransitionClickObs(stageTransitionView, stageTransitionCtrl);
    GGStageTransitionTickObserver stageTransitionTickObs(stageTransitionView, stageTransitionCtrl, sf::milliseconds(10));

    // Pump Game
    GGPumpCtrl pumpCtrl;
    GGView pumpView(&pumpCtrl);

    GGPumpClickObserver pumpClickObs(pumpView, pumpCtrl);
    GGPumpTickObserver pumptickObs(pumpView, pumpCtrl, sf::milliseconds(55));
    GGPumpTimerObserver pumpTimerObs(pumpView, pumpCtrl);

    // News Game
    GGNewsCtrl newsCtrl;
    GGView newsView(&newsCtrl);

    GGNewsTickObserver buttonTickObs(newsView, newsCtrl, sf::milliseconds(55));
    GGNewsButtonClickObserver buttonClickObs(newsView, newsCtrl);
    GGNewsTimerObserver newsTimerObs(newsView, newsCtrl);

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

    // Views Vector
    std::vector<GGView*> views;
    views.push_back(&newsView);
    views.push_back(&cannonView);

    // Stage One Region
    GGGameOverModel gameOverModelStageOne;
    gameOverModelStageOne.StageOne();
    GGBookendsCtrl gameOverCtrlStageOne(&gameOverModelStageOne);
    GGView gameOverStageOneView(&gameOverCtrlStageOne);
    GGContinueGameObserver restartGameObsOne(gameOverStageOneView, gameOverCtrlStageOne, sf::Keyboard::R);
    GGBookendsTextTickObserver gameOverTextStageOneObs(gameOverStageOneView, gameOverCtrlStageOne);

    GGCompositeView stageOneView(1);
    stageOneView.SetBackgroundMusic("Assets/Music/MainThemeLoop1.wav");
    stageOneView.AddView(&stageTransitionView);
    stageOneView.AddView(&pumpView);
    SetRandomGameOrder(stageOneView, views);
    views.push_back(&pumpView);

    GGStage stageOne(&stageOneView, &gameOverStageOneView);
    subjMgr.AddStage(stageOne);

    // Stage Two Region
    GGCompositeView stageTwoView(2);
    stageTwoView.SetBackgroundMusic("Assets/Music/MainThemeLoop2.wav");
    stageTwoView.AddView(&stageTransitionView);
    SetRandomGameOrder(stageTwoView, views);

    GGGameOverModel gameOverModelStageTwo;
    // gameOverModelStageTwo.StageTwo();
    GGBookendsCtrl gameOverCtrlStageTwo(&gameOverModelStageTwo);
    GGView gameOverStageTwoView(&gameOverCtrlStageTwo);
    GGContinueGameObserver restartGameObsTwo(gameOverStageTwoView, gameOverCtrlStageTwo, sf::Keyboard::R);
    GGBookendsTextTickObserver gameOverTextStageTwoObs(gameOverStageTwoView, gameOverCtrlStageTwo);

    GGStage stageTwo(&stageTwoView, &gameOverStageTwoView);
    subjMgr.AddStage(stageTwo);

    // Stage Three Region
    GGCompositeView stageThreeView(3);
    stageThreeView.SetBackgroundMusic("Assets/Music/MainThemeLoop3.wav");
    stageThreeView.AddView(&stageTransitionView);
    SetRandomGameOrder(stageThreeView, views);

    GGGameOverModel gameOverModelStageThree;
    gameOverModelStageThree.StageThree();
    GGBookendsCtrl gameOverCtrlStageThree(&gameOverModelStageThree);
    GGView gameOverStageThreeView(&gameOverCtrlStageThree);
    GGContinueGameObserver restartGameObsThree(gameOverStageThreeView, gameOverCtrlStageThree, sf::Keyboard::R);
    GGBookendsTextTickObserver gameOverTextStageThreeObs(gameOverStageThreeView, gameOverCtrlStageThree);

    GGStage stageThree(&stageThreeView, &gameOverStageThreeView);
    subjMgr.AddStage(stageThree);

    // Stage Four Region
    GGStageFourCtrl stageFourCtrl;
    GGView stageFourView(&stageFourCtrl);
    GGStage stageFour(&stageFourView);
    GGStageFourSwitchObserver stageFourSwitchObs(stageFourView, stageFourCtrl);
    subjMgr.AddStage(stageFour);

    subjMgr.PlayGame();
    return 0;
}