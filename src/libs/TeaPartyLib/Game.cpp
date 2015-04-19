#include "Game.h"

#include "Components/Position.h"
#include "Components/Sprite.h"
#include "Components/Keyboard.h"
#include "Components/Speed.h"
#include "Components/AnimationList.h"
#include "Systems/Display.h"
#include "Systems/Input.h"
#include "Systems/Move.h"
#include "Systems/KeyboardController.h"
#include "Systems/AnimationDispatcher.h"

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
	STFU(Move);
    STFU(AnimationDispatcher);

    mAnimations.push_back(std::make_unique<Structure::Animation>("run_left",2,30.0f));
    mAnimations.push_back(std::make_unique<Structure::Animation>("run_right",2,30.0f));
    mAnimations.push_back(std::make_unique<Structure::Animation>("idle",0,30.0f));


    Polycode::CoreServices::getInstance()->getResourceManager()->addArchive(gResourcesRoot+"/Archive.zip");
    aunteater::Entity sprite;
    sprite.addComponent<Component::Sprite>(new Polycode::SpriteSet("runningChamp.xml"));
    sprite.addComponent<Component::Position>(10, 10);
	sprite.addComponent<Component::Speed>();
	sprite.addComponent<Component::Keyboard>();
    sprite.addComponent<Component::AnimationList>("idle");

    sprite.get<Component::AnimationList>()->addAnimation(*mAnimations[0].get());
	sprite.get<Component::AnimationList>()->addAnimation(*mAnimations[1].get());
	sprite.get<Component::AnimationList>()->addAnimation(*mAnimations[2].get());
    mEngine->addEntity(sprite);
}

Game::~Game()
{

}

void Game::update()
{
    mEngine->update(0.);
}