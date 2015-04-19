#include "Game.h"

#include "Components/Position.h"
#include "Components/Sprite.h"
#include "Systems/Display.h"

#include <aunteater/Engine.h>

using namespace TeaParty;

Game::Game() :
    mEngine(new aunteater::Engine)
{
    mSystems.push_back(std::make_unique<System::Display>());
    mEngine->addSystem(mSystems.back().get());

    aunteater::Entity sprite;
    sprite.addComponent<Component::Sprite>(
        new Polycode::SpriteSet("/Users/adn/Desktop/sprite_set.xml"));
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