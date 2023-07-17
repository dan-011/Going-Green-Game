AbstractAsset
- All Asset types subclass from this. These may be static images, animations, backgrounds, etc.
- Currently implemented:
    > Sprite sheet animated assets
        * Constructor requires:
            ~ position of asset
            ~ filename of sprite sheet
            ~ dimensions of sprite sheet (rows of frames, columns of frames)
    > Collection of images animated assets
        * Constructor requires:
            ~ position of asset
            ~ vector of file names (in order)
- Additional subclasses needed for certain features

AbstractCtrl
- The controller changes the data in the model
- observers interact with the controller to change the model data
- For each view there is a unique controller
- Each controller contains a model (privately)
- Each controller creates the model in its constructor
- Each controller must provide a definition for "GetModel()"
- Controller will change the continueGame and wasSuccess status bits in it's model to control ending the game and moving to game over
- Additional subclasses needed which are specific to the game/screen/cutscene

AbstractModel
- The model holds the data specific to a game/screen/cutscene
- In the constructor, create all assets for that model and call AddAsset to add it to the game
- For assets that will be changed by the controller, preserve a reference to that asset and create a getter to provide access to the ctrl
- Each model must provide a definition for the "ResetData()" method, which defines how the data will reset when starting a game over
- Contains status bits for whether the game was a success (game win) and whether to stop the game/screen/cutscene
- Additional subclasses needed which are specific to the game/screen/cutscene

AbstractObserver
- Contract for observer subclasses
- All observers support an Update function, which is called when they're notified by the Subject
- Code does NOT require any changes

IndivObservers
- Each observer is a subclass of the AbstractObserver
- Obsevers usually contain a reference to their view and to their controller
- In the constructor for each observer, include the line "view.AddObserver(this);" to add it to the view subject
- An observer is needed for any event, for instance
    > Clicking the pump
    > Dragging the cannon
    > A fixed change in time for an animations
    > Pressing "ENTER" to start
- Additional IndivObserver classes are necessary for each event interaction

Main
- Wiring up the stage occurs in main
- When adding a stage:
    > Instantiate the controller(s)
    > Instantiate the view(s)
        * Pass in the controllers as an argument for each view in the stage
    > Instantiate the stage with the views
    > Instantiate the observers for the stage
    > Add the stage to the subject manager
        * subjMgr.AddStage(...);
- Addition code needed as additional models and views are implemented

Stage
- Each stage contains the game view and the game over view
- Stages represents the broken up parts of the game, each of the following is a single stage
    > Game start screen
    > Letter scenes
    > Collection of micro games at a single difficulty level
- For things like the letter and game start screen which don't have game overs, do not include a view for that parameter
- Constructor requires:
    > Pointer to main view
    > Pointer to game over view
        * Do not specify if not apply
- Code does NOT require any changes

Subject
- This is the superclass of view
- Handles adding and notifying observers
- Code does NOT require any changes

Subject Manager
- Handles moving between stages
- Holds logic for launching game over screen and restarting current game
- Code does NOT require any changes

View
- Displays the assets from within the model
- The first line of interaction with the user
- Notifies observers
- Code does NOT require any changes

Window
- Houses the static reference to the window that can be accessed throughout the program
- Code does NOT require any changes

Job Flow:
- Each stage consists of a game view and a game over view
- The stage starts the game view (goes in order)
- View enters a loop
- Observers listen for events occuring in the view
- Observers tell the controller to change the model based on events
- Controller changes data in model
- Model contain assets which experience change
- Loop ends when the controller sets the continueGame status bit in the model to false
- If the wasSuccess bit is true, the next game view plays
    > If the wasSuccess bit is false, the game over view associated with that stage plays