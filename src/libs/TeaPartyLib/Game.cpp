#include "Game.h"

#include "Level.h"

#include "Components/ActionController.h"
#include "Components/AnimationList.h"
#include "Components/AnimationStillFrame.h"
#include "Components/BallsPoint.h"
#include "Components/CallbackOnActor.h"
#include "Components/ClippedScene.h"
#include "Components/Controller.h"
#include "Components/Displacement.h"
#include "Components/Extent.h"
#include "Components/Index.h"
#include "Components/Keyboard.h"
#include "Components/GamePhase.h"
#include "Components/Image.h"
#include "Components/IWantToDie.h"
#include "Components/Pendular.h"
#include "Components/PlayerReference.h"
#include "Components/PointsTarget.h"
#include "Components/Position.h"
#include "Components/SelectedPhase.h"
#include "Components/Sprite.h"
#include "Components/Speed.h"
#include "Components/TriggeringAction.h"
#include "Components/HudItem.h"
#include "Components/Inventory.h"
#include "Components/Physics.h"
#include "Components/Score.h"
#include "Components/Static.h"

#include "Systems/CameraController.h"
#include "Systems/CollisionSolver.h"
#include "Systems/Destruction.h"
#include "Systems/Display.h"
#include "Systems/Input.h"
#include "Systems/AnimationDispatcher.h"
#include "Systems/KeyboardController.h"
#include "Systems/ControllerController.h"
#include "Systems/Move.h"
#include "Systems/Trigger.h"
#include "Systems/PendulumPhysics.h"
#include "Systems/PhaseController.h"
#include "Systems/Physics.h"
#include "Systems/PointCounter.h"
#include "Systems/PointsTrigger.h"
#include "Systems/PointVisualisation.h"
#include "Systems/Friction.h"
#include "Systems/Inventory.h"
#include "Systems/InventoryLayout.h"
#include "Systems/HudDisplay.h"
#include "Systems/ScoreDisplay.h"
#include "Systems/Tween.h"

#include <ResourcesPath.h>

#include <aunteater/Engine.h>
#include <sstream>

using namespace TeaParty;

#define STFU(systemType) \
    mSystems.push_back(std::make_unique<System:: systemType>()); \
    mEngine->addSystem(mSystems.back().get());

#define STFU1(systemType, arg_1) \
    mSystems.push_back(std::make_unique<System:: systemType>(arg_1)); \
    mEngine->addSystem(mSystems.back().get());

const std::string gLevelDefinition = R"#(
		room_double_mandala_alt.png
        room_green_small.png
        room_brown.png
        room_double_mandala.png
        room_mandala_small.png
        ZUP
        room_mandala_small.png
        room_green_small.png
        room_green_small_alt.png
        room_mandala_small.png
        room_brown.png
		room_double_mandala_alt.png
    )#";


void createPlayer(aunteater::Engine &mEngine, std::vector<std::unique_ptr<Structure::Animation>> &mAnimations, std::string spriteSet, int index)
{
    aunteater::Entity player1;

    //*** Player Entity setup ***//
    player1.addComponent<Component::Index>(index);
    player1.addComponent<Component::Score>();
    player1.addComponent<Component::ActionController>();
    player1.addComponent<Component::Sprite>(new Polycode::SpriteSet(spriteSet));
    player1.addComponent<Component::Position>(150, -50);
    player1.addComponent<Component::Displacement>();
    player1.addComponent<Component::Extent>();
    player1.addComponent<Component::Speed>();
    if (Polycode::CoreServices::getInstance()->getCore()->getInput()->getNumJoysticks() > index - 1)
    {
        player1.addComponent<Component::Controller>(Polycode::CoreServices::getInstance()->getCore()->getInput()->getJoystickInfoByIndex(index - 1));
    }
    else
    {
        player1.addComponent<Component::Keyboard>();
    }
    player1.addComponent<Component::AnimationList>("idle");
    player1.addComponent<Component::Physics>();

    player1.addComponent<Component::SelectedPhase>();
    //aunteater::Entity itemYo;
    //itemYo.addComponent<Component::HudItem>(new Polycode::SpriteSet("items.sprites"));
    //itemYo.get<Component::HudItem>()->polySprite.get()->setSpriteByName("item1");
    //itemYo.get<Component::HudItem>()->polySprite.get()->setSpriteStateByName("default",0,false);
    //itemYo.addComponent<Component::Position>(0,0);
    //mEngine->addEntity("penis-like-sword",itemYo);

    //player1.get<Component::Inventory>()->addItemToInventory("penis-like-sword",mEngine->getEntity("penis-like-sword"));


    player1.get<Component::AnimationList>()->addAnimation(*mAnimations[0].get());
    player1.get<Component::AnimationList>()->addAnimation(*mAnimations[1].get());
    player1.get<Component::AnimationList>()->addAnimation(*mAnimations[2].get());
    player1.get<Component::AnimationList>()->addAnimation(*mAnimations[3].get());

    player1.addComponent<Component::GamePhase>();
    mEngine.addEntity("player" + std::to_string(index), player1);

    //*** End Player ***//

    //*** Bagging mini game ***//
    aunteater::Entity sleepyFace;
    sleepyFace.addComponent<Component::Sprite>(new Polycode::SpriteSet("balls_deep.sprites"));
    sleepyFace.addComponent<Component::Position>(X_ROOM / 2., 0, LAYERS - 1); // last layer, never displayed by the main phase
    sleepyFace.addComponent<Component::AnimationList>("default");
    sleepyFace.get<Component::AnimationList>()->addAnimation(*mAnimations[4].get());
    mEngine.addEntity("face" + std::to_string(index), sleepyFace);

    sleepyFace.get<Component::Sprite>()->polySprite->setSpriteByName("balls_deep");
    sleepyFace.get<Component::Sprite>()->polySprite->setSpriteStateByName("default", 0, false);
    sleepyFace.get<Component::Sprite>()->polySprite->setScale(11, 11);
    player1.get<Component::GamePhase>()->phaseRootEntity->addChild(sleepyFace.get<Component::Sprite>()->polySprite.get());

    //*** Pivot ***//
    aunteater::Entity pivot;
    pivot.addComponent<Component::Sprite>(new Polycode::SpriteSet("cross.sprites"));
    pivot.addComponent<Component::Position>(150, -20, LAYERS - 1); // last layer, never displayed by the main phase
    pivot.addComponent<Component::ActionController>();
    pivot.addComponent<Component::Displacement>();
    pivot.addComponent<Component::Extent>(50, 50);
    pivot.addComponent<Component::Physics>();
    pivot.addComponent<Component::Speed>();
    pivot.addComponent<Component::AnimationList>("default");
    if (Polycode::CoreServices::getInstance()->getCore()->getInput()->getNumJoysticks() > index - 1)
    {
        pivot.addComponent<Component::Controller>(Polycode::CoreServices::getInstance()->getCore()->getInput()->getJoystickInfoByIndex(index - 1));
    }
    else
    {
        pivot.addComponent<Component::Keyboard>();
    }
    pivot.get<Component::AnimationList>()->addAnimation(*mAnimations[4].get());

    mEngine.addEntity("pivot" + std::to_string(index), pivot);
    pivot.get<Component::Sprite>()->polySprite->setSpriteByName("cross");
    pivot.get<Component::Sprite>()->polySprite->setSpriteStateByName("default", 0, false);
    //pivot.get<Component::Sprite>()->polySprite->setScale(10, 10);
    player1.get<Component::GamePhase>()->phaseRootEntity->addChild(pivot.get<Component::Sprite>()->polySprite.get());

    //*** Balls Point ***//
    aunteater::Entity point;
    point.addComponent<Component::Sprite>(new Polycode::SpriteSet("balls_deep_counter.sprites"));
    point.addComponent<Component::Position>(X_ROOM - 50, Y_ROOM / 2 - 50, LAYERS - 1); // last layer, never displayed by the main phase
    point.addComponent<Component::AnimationStillFrame>();
    //point.addComponent<Component::BallsPoint>(); // Now added when the game phase changes to DIPPING
    point.get<Component::Sprite>()->polySprite->setSpriteByName("balls_deep_counter");
    point.get<Component::Sprite>()->polySprite->setSpriteStateByName("default", 0, false);
    mEngine.addEntity("pointCounter" + std::to_string(index), point);
    point.get<Component::Sprite>()->polySprite->setScale(3, 3);
    player1.get<Component::GamePhase>()->phaseRootEntity->addChild(point.get<Component::Sprite>()->polySprite.get());

    //*** Crosshair ***//
    aunteater::Entity hairyCross;
    hairyCross.addComponent<Component::Pendular>(.5, 0.5, mEngine.getEntity("pointCounter" + std::to_string(index)));
    hairyCross.addComponent<Component::PivotReference>(mEngine.getEntity("pivot" + std::to_string(index)));

    hairyCross.addComponent<Component::Sprite>(new Polycode::SpriteSet("balls_crosshair.sprites"));
    hairyCross.addComponent<Component::Position>(0, -20, LAYERS - 1); // last layer, never displayed by the main phase
    hairyCross.addComponent<Component::Physics>(100.2);

    mEngine.addEntity("cross" + std::to_string(index), hairyCross);
    hairyCross.get<Component::Sprite>()->polySprite->setSpriteByName("balls_crosshair");
    hairyCross.get<Component::Sprite>()->polySprite->setSpriteStateByName("default", 0, false);

    player1.get<Component::GamePhase>()->phaseRootEntity->addChild(hairyCross.get<Component::Sprite>()->polySprite.get());

};

Game::Game() :
    mEngine(new aunteater::Engine)
{
    Polycode::CoreServices::getInstance()->getResourceManager()->addArchive(gResourcesRoot+"/Archive.zip");
    Polycode::CoreServices::getInstance()->getFontManager()->registerFont("sans", "sans.ttf");

    std::istringstream defStream(gLevelDefinition);
    mLevel = std::make_unique<Level>(defStream, *mEngine);
    //initLevel();

    STFU(Input);
    STFU(Friction);
    STFU(PendulumPhysics)
    STFU(Physics);
    STFU(Move);
    STFU(HudDisplay);
    STFU(CollisionSolver);
    STFU(Tween);
    // From here, everything have its position assigned for the next frame to display
    STFU1(CameraController, mLevel.get());
    STFU(AnimationDispatcher);
    STFU(Trigger);
    STFU(Display);
    STFU(PhaseController); // must come after display...
    STFU(PointVisualisation);
    STFU(PointCounter);
    STFU(PointsTrigger)
    STFU(ScoreDisplay)
    STFU(Destruction);
    
    STFU(KeyboardController);
    STFU(ControllerController);

    mAnimations.push_back(std::make_unique<Structure::Animation>("run_left",2,30.0f));
    mAnimations.push_back(std::make_unique<Structure::Animation>("run_right",2,30.0f));
    mAnimations.push_back(std::make_unique<Structure::Animation>("idle_left",0,30.0f));
	mAnimations.push_back(std::make_unique<Structure::Animation>("idle_right", 0, 30.0f));
	mAnimations.push_back(std::make_unique<Structure::Animation>("default", 0, 4.0f));

    
    //pivot.get<Component::Sprite>()->polySprite->addChild(hairyCross.get<Component::Sprite>()->polySprite.get());
    createPlayer(*mEngine.get(), mAnimations, "runningChamp.sprites", 1);
    createPlayer(*mEngine.get(), mAnimations, "runningChamp2.sprites", 2);

    //*** Victim ***//
    aunteater::Entity &victim = *mEngine->addEntity("target",aunteater::Entity());
    // Graphics
    victim.addComponent<Component::Sprite>(new Polycode::SpriteSet("sleeping_guy.sprites"));
    victim.get<Component::Sprite>()->polySprite->setSpriteByName("sleeping_guy");
    victim.get<Component::Sprite>()->polySprite->setSpriteStateByName("default", 0, false);
    victim.addComponent<Component::Position>(100, -115, 0); // last layer, never displayed by the main phase
    // Trigger
    victim.addComponent<Component::Extent>(VICTIM_EXTENT, VICTIM_EXTENT);
    victim.addComponent<Component::TriggeringAction>(Component::Action::A);
    victim.addComponent<Component::CallbackOnActor>([&victim](aunteater::Entity &aPlayer)
                                                    {
                                                        aPlayer.get<Component::SelectedPhase>()->phase = Component::Phase::DIPPING;
                                                        aPlayer.get<Component::SelectedPhase>()->victim = &victim;
                                                    });



    // CAN BE SHARED BY ALL ONE SCREEN GAMES
    aunteater::Entity leftBorder;
    leftBorder.addComponent<Component::Extent>(10., 10.);// because we do not want to be able to cross in less than 1 frame
    leftBorder.addComponent<Component::Position>(0., 0., LAYERS-1);
    leftBorder.addComponent<Component::Static>();
    mEngine->addEntity(leftBorder);

    aunteater::Entity rightBorder;
    rightBorder.addComponent<Component::Extent>(10., 10.);// because we do not want to be able to cross in less than 1 frame
    rightBorder.addComponent<Component::Position>(X_ROOM, 0., LAYERS-1);
    rightBorder.addComponent<Component::Static>();
    mEngine->addEntity(rightBorder);

	//*** End Player ***//


    //*** Player Camera setup ***//
    for(int rowId = 0; rowId != VP_ROWS; ++rowId)
    {
        for(int colId = 0; colId != VP_COLS; ++colId)
        {
            aunteater::Entity camera;
            camera.addComponent<Component::Position>(0., 0.);
			if (rowId % 2 == 0)
			{
				camera.addComponent<Component::PlayerReference>(mEngine->getEntity("player1"));
				camera.addComponent<Component::ClippedScene>(rowId, colId);
			}
			else 
			{
				camera.addComponent<Component::PlayerReference>(mEngine->getEntity("player2"));
				camera.addComponent<Component::ClippedScene>(rowId, colId);
			}
            
            mEngine->addEntity("camera" + std::to_string(rowId),camera);
        }
    }
    //*** End Camera ***//

    STFU(ScoreDisplay) // Needs to display OVER the camera
}

Game::~Game()
{

}

void Game::initLevel()
{
}

void Game::update()
{
    mEngine->update(0.);
}