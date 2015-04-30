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
    )#";


Game::Game() :
    mEngine(new aunteater::Engine)
{
    Polycode::CoreServices::getInstance()->getResourceManager()->addArchive(gResourcesRoot+"/Archive.zip");

    std::istringstream defStream(gLevelDefinition);
    mLevel = std::make_unique<Level>(defStream, *mEngine);
    //initLevel();

    STFU(Display);
    /**/STFU(KeyboardController); // not changing anything at the moment...
    STFU(Input);
    STFU(Move);
    STFU(CollisionSolver);
    STFU(Tween);
    // From here, everything have its position assigned for the next frame to display
    STFU1(CameraController, mLevel.get());
    STFU(AnimationDispatcher);
    STFU(Trigger);
	STFU(Display);
    STFU(InventoryLayout);
    STFU(Inventory);

    //Everything depending on falling edge should be put before KeayboardController
	STFU(KeyboardController);
	STFU(Input);
    STFU(Friction);
    STFU(Physics);
    STFU(Move);
    STFU(HudDisplay);

    mAnimations.push_back(std::make_unique<Structure::Animation>("run_left",2,30.0f));
    mAnimations.push_back(std::make_unique<Structure::Animation>("run_right",2,30.0f));
    mAnimations.push_back(std::make_unique<Structure::Animation>("idle",0,30.0f));

    aunteater::Entity sprite;

    //*** Player Entity setup ***//
    sprite.addComponent<Component::ActionController>();
    sprite.addComponent<Component::Sprite>(new Polycode::SpriteSet("runningChamp.xml"));
    sprite.addComponent<Component::Position>(150, -50);
    sprite.addComponent<Component::Displacement>();
    sprite.addComponent<Component::Extent>();
    sprite.addComponent<Component::Speed>();
    sprite.addComponent<Component::Keyboard>();
    sprite.addComponent<Component::AnimationList>("idle");
    sprite.addComponent<Component::Physics>();
    sprite.addComponent<Component::Inventory>();

    aunteater::Entity itemYo;
    itemYo.addComponent<Component::HudItem>(new Polycode::SpriteSet("items.sprites"));
    itemYo.get<Component::HudItem>()->polySprite.get()->setSpriteByName("item1");
    itemYo.get<Component::HudItem>()->polySprite.get()->setSpriteStateByName("default",0,false);
    itemYo.addComponent<Component::Position>(0,0);
    mEngine->addEntity("penis-like-sword",itemYo);

    sprite.get<Component::Inventory>()->addItemToInventory("penis-like-sword",mEngine->getEntity("penis-like-sword"));

    aunteater::Entity item;
    item.addComponent<Component::HudItem>(new Polycode::SpriteSet("items.sprites"));
    item.get<Component::HudItem>()->polySprite.get()->setSpriteByName("item2");
    item.get<Component::HudItem>()->polySprite.get()->setSpriteStateByName("default",0,false);
	item.addComponent<Component::Position>(0, 0);
    mEngine->addEntity("penis",item);

    sprite.get<Component::Inventory>()->addItemToInventory("penis",mEngine->getEntity("penis"));

    sprite.get<Component::AnimationList>()->addAnimation(*mAnimations[0].get());
    sprite.get<Component::AnimationList>()->addAnimation(*mAnimations[1].get());
    sprite.get<Component::AnimationList>()->addAnimation(*mAnimations[2].get());
    mEngine->addEntity("player", sprite);
    //*** End Player ***//

	aunteater::Entity caca;

	//*** Player Entity setup ***//
	caca.addComponent<Component::ActionController>();
	caca.addComponent<Component::Sprite>(new Polycode::SpriteSet("runningChamp.xml"));
	caca.addComponent<Component::Position>(500, -50);
	caca.addComponent<Component::Displacement>();
	caca.addComponent<Component::Extent>();
	caca.addComponent<Component::Speed>();
	caca.addComponent<Component::Keyboard>();
	caca.addComponent<Component::AnimationList>("idle");
	caca.addComponent<Component::Physics>();

	caca.get<Component::AnimationList>()->addAnimation(*mAnimations[0].get());
	caca.get<Component::AnimationList>()->addAnimation(*mAnimations[1].get());
	caca.get<Component::AnimationList>()->addAnimation(*mAnimations[2].get());
	mEngine->addEntity("caca", caca);
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
				camera.addComponent<Component::PlayerReference>(mEngine->getEntity("player"));
				camera.addComponent<Component::ClippedScene>(rowId, colId);
			}
			else 
			{
				camera.addComponent<Component::PlayerReference>(mEngine->getEntity("caca"));
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