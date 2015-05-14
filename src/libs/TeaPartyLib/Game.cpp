#include "Game.h"

#include "Level.h"

#include "Components/ActionController.h"
#include "Components/AnimationList.h"
#include "Components/CallbackOnActor.h"
#include "Components/ClippedScene.h"
#include "Components/Displacement.h"
#include "Components/Extent.h"
#include "Components/Keyboard.h"
#include "Components/Image.h"
#include "Components/PlayerReference.h"
#include "Components/Position.h"
#include "Components/Sprite.h"
#include "Components/Speed.h"
#include "Components/TriggeringAction.h"
#include "Components/HudItem.h"
#include "Components/Inventory.h"
#include "Systems/CameraController.h"
#include "Systems/CollisionSolver.h"
#include "Components/AnimationList.h"
#include "Components/Physics.h"
#include "Systems/Display.h"
#include "Systems/Input.h"
#include "Systems/KeyboardController.h"
#include "Systems/Move.h"
#include "Systems/Trigger.h"
#include "Systems/AnimationDispatcher.h"
#include "Systems/Physics.h"
#include "Systems/Friction.h"
#include "Systems/Inventory.h"
#include "Systems/InventoryLayout.h"
#include "Systems/HudDisplay.h"
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
        room_red.png
        room_brown.png
        room_double_mandala.png
        room_green.png
        ZUP
        room_green.png
        room_brown.png
        room_brown.png
        room_brown.png
        room_red.png
    )#";


Game::Game() :
    mEngine(new aunteater::Engine)
{
    Polycode::CoreServices::getInstance()->getResourceManager()->addArchive(gResourcesRoot+"/Archive.zip");

    std::istringstream defStream(gLevelDefinition);
    mLevel = std::make_unique<Level>(defStream, *mEngine);
    //initLevel();

    STFU(Display);
    STFU(InventoryLayout);
    STFU(Inventory);

    /**/STFU(KeyboardController); // not changing anything at the moment...
    STFU(Input);
    STFU(Friction);
    STFU(Physics);
    STFU(Move);
    STFU(CollisionSolver);
    STFU(Tween);
    // From here, everything have its position assigned for the next frame to display
    STFU1(CameraController, mLevel.get());
    STFU(AnimationDispatcher);
    STFU(Trigger);
	STFU(Display);

    //Everything depending on falling edge should be put before KeayboardController
//STFU(KeyboardController);
//STFU(Input);
//STFU(Move);
STFU(HudDisplay);

    mAnimations.push_back(std::make_unique<Structure::Animation>("run_left",2,30.0f));
    mAnimations.push_back(std::make_unique<Structure::Animation>("run_right",2,30.0f));
    mAnimations.push_back(std::make_unique<Structure::Animation>("idle",0,30.0f));

    aunteater::Entity player1;

    //*** Player Entity setup ***//
    player1.addComponent<Component::ActionController>();
    player1.addComponent<Component::Sprite>(new Polycode::SpriteSet("runningChamp.xml"));
    player1.addComponent<Component::Position>(150, -50);
    player1.addComponent<Component::Displacement>();
    player1.addComponent<Component::Extent>();
    player1.addComponent<Component::Speed>();
    player1.addComponent<Component::Keyboard>();
    player1.addComponent<Component::AnimationList>("idle");
    player1.addComponent<Component::Physics>();
    player1.addComponent<Component::Inventory>();

    aunteater::Entity itemYo;
    itemYo.addComponent<Component::HudItem>(new Polycode::SpriteSet("items.sprites"));
    itemYo.get<Component::HudItem>()->polySprite.get()->setSpriteByName("item1");
    itemYo.get<Component::HudItem>()->polySprite.get()->setSpriteStateByName("default",0,false);
    itemYo.addComponent<Component::Position>(0,0);
    mEngine->addEntity("penis-like-sword",itemYo);

    player1.get<Component::Inventory>()->addItemToInventory("penis-like-sword",mEngine->getEntity("penis-like-sword"));

    aunteater::Entity item;
    item.addComponent<Component::HudItem>(new Polycode::SpriteSet("items.sprites"));
    item.get<Component::HudItem>()->polySprite.get()->setSpriteByName("item2");
    item.get<Component::HudItem>()->polySprite.get()->setSpriteStateByName("default",0,false);
	item.addComponent<Component::Position>(0, 0);
    mEngine->addEntity("penis",item);

    player1.get<Component::Inventory>()->addItemToInventory("penis",mEngine->getEntity("penis"));

    player1.get<Component::AnimationList>()->addAnimation(*mAnimations[0].get());
    player1.get<Component::AnimationList>()->addAnimation(*mAnimations[1].get());
    player1.get<Component::AnimationList>()->addAnimation(*mAnimations[2].get());
    mEngine->addEntity("player1", player1);
    //*** End Player ***//

	aunteater::Entity player2;

	//*** Player Entity setup ***//
	player2.addComponent<Component::ActionController>();
	player2.addComponent<Component::Sprite>(new Polycode::SpriteSet("runningChamp.xml"));
	player2.addComponent<Component::Position>(500, -50, 1);
	player2.addComponent<Component::Displacement>();
	player2.addComponent<Component::Extent>();
	player2.addComponent<Component::Speed>();
	player2.addComponent<Component::Keyboard>();
	player2.addComponent<Component::AnimationList>("idle");
	player2.addComponent<Component::Physics>();

	player2.get<Component::AnimationList>()->addAnimation(*mAnimations[0].get());
	player2.get<Component::AnimationList>()->addAnimation(*mAnimations[1].get());
	player2.get<Component::AnimationList>()->addAnimation(*mAnimations[2].get());
	mEngine->addEntity("player2", player2);
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
            
            mEngine->addEntity(camera);
        }
    }
    //*** End Camera ***//
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