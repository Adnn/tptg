#include "Game.h"

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