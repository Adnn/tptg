#include "Game.h"

#include "Components/Image.h"
#include "Components/Position.h"
#include "Components/Sprite.h"
#include "Components/Keyboard.h"
#include "Components/Speed.h"
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

Game::Game() :
    mEngine(new aunteater::Engine)
{
	STFU(Display);
	STFU(KeyboardController);
	STFU(Input);
	STFU(Move)

    Polycode::CoreServices::getInstance()->getResourceManager()->addArchive(gResourcesRoot+"/Archive.zip");

    constexpr double ROOM_WIDTH = 960/2;

    aunteater::Entity room_0_0;
    room_0_0.addComponent<Component::Image>("room_red.png");
    room_0_0.addComponent<Component::Position>(0, 0);
    mEngine->addEntity(room_0_0);

    aunteater::Entity room_0_1;
    room_0_1.addComponent<Component::Image>("room_brown.png");
    room_0_1.addComponent<Component::Position>(ROOM_WIDTH, 0);
    mEngine->addEntity(room_0_1);

    aunteater::Entity sprite;
    sprite.addComponent<Component::Sprite>(new Polycode::SpriteSet("explosion.xml"));
    sprite.addComponent<Component::Position>(10, 10);
	sprite.addComponent<Component::Speed>();
	sprite.addComponent<Component::Keyboard>();
    mEngine->addEntity(sprite);

}

Game::~Game()
{

}

void Game::update()
{
    mEngine->update(0.);
}