#include "Game.h"

#include "Components/Image.h"
#include "Components/Position.h"
#include "Components/Sprite.h"
#include "Systems/Display.h"

#include <ResourcesPath.h>

#include <aunteater/Engine.h>

using namespace TeaParty;

Game::Game() :
    mEngine(new aunteater::Engine)
{
    mSystems.push_back(std::make_unique<System::Display>());
    mEngine->addSystem(mSystems.back().get());

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
    mEngine->addEntity(sprite);

}

Game::~Game()
{

}

void Game::update()
{
    mEngine->update(0.);
}