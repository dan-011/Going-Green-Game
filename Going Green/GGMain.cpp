#include <SFML/Graphics.hpp>
#include "GGSubjectManager.h"
#include "GGAbstractAsset.h"
#include "GGIndivObservers.h"

int main()
{
    srand(time(NULL));
    GGSubjectManager subjMgr;

    /* Test Pump Game */
    GGPumpCtrl testCtrl;
    GGNewsCtrl newsCtrl;
    GGStageTransitionCtrl stageTransitionCtrl("Assets/Animations/stage_transition/table_1.png", "Assets/Animations/stage_transition/env1.png", "Assets/Animations/stage_transition/letter_1.png");
    GGTestGameOverCtrl testGameOverCtrl;

    GGView testView(&testCtrl);
    GGView newsView(&newsCtrl);
    GGView stageTransitionView(&stageTransitionCtrl);
    GGView testGameOverView(&testGameOverCtrl);

    GGStage testStage(&testView, &testGameOverView);
    GGStage newsStage(&newsView, &testGameOverView);
    GGStage stageTransition(&stageTransitionView, &testGameOverView);

    GGPumpClickObserver pumpClickObs(testView, testCtrl);
    GGPumpTickObserver pumptickObs(testView, testCtrl, sf::milliseconds(55));
    GGTestGameOverTick gameOberTickObs(testGameOverView, testGameOverCtrl);
    GGEndGameObserver endGameObs(testView, testCtrl);
    GGRestartGameObserver restartGameObs(testGameOverView, testGameOverCtrl);
    GGNewsTickObserver buttonTickObs(newsView, newsCtrl, sf::milliseconds(55));
    GGNewsButtonClickObserver buttonClickObs(newsView, newsCtrl);
    GGNewsTimerObserver newsTimerObs(newsView, newsCtrl);
    GGPumpTimerObserver pumpTimerObs(testView, testCtrl);
    GGStageTransitionClickObserver stageTransitionClickObs(stageTransitionView, stageTransitionCtrl);
    GGStageTransitionTickObserver stageTransitionTickObs(stageTransitionView, stageTransitionCtrl, sf::milliseconds(10));

    subjMgr.AddStage(stageTransition);
    subjMgr.AddStage(newsStage);
    subjMgr.AddStage(testStage);

    subjMgr.PlayGame();
    return 0;
}