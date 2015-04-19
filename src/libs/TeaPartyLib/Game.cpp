#include "Game.h"

#include "Level.h"

#include "Components/Keyboard.h"
#include "Components/Image.h"
#include "Components/PlayerReference.h"
#include "Components/Position.h"
#include "Components/Sprite.h"
#include "Components/Speed.h"
#include "Systems/CameraController.h"
#include "Systems/Display.h"
#include "Systems/Input.h"
#include "Systems/Move.h"
#include "Systems/KeyboardController.h"

#include <ResourcesPath.h>

#include <aunteater/Engine.h>

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
    STFU(KeyboardController);
    STFU(Input);
    STFU(Move)
    STFU1(CameraController, mLevel.get())

    aunteater::Entity sprite;
    sprite.addComponent<Component::Sprite>(new Polycode::SpriteSet("explosion.xml"));
    sprite.addComponent<Component::Position>(200, 0);
	sprite.addComponent<Component::Speed>();
	sprite.addComponent<Component::Keyboard>();
    mEngine->addEntity("player", sprite);

    aunteater::Entity camera;
    camera.addComponent<Component::Position>(0., 0);
    camera.addComponent<Component::PlayerReference>(mEngine->getEntity("player"));
    mEngine->addEntity("camera", camera);

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