#include "PhaseController.h"

#include "../Archetypes/NodeCamera.h"

#include "../Components/ActionController.h"
#include "../Components/BallsPoint.h"
#include "../Components/CallbackOnActor.h"
#include "../Components/CallbackNoParam.h"
#include "../Components/GamePhase.h"
#include "../Components/Index.h"
#include "../Components/IWantToDie.h"
#include "../Components/PlayerReference.h"
#include "../Components/PointsTarget.h"
#include "../Components/Position.h"
#include "../Components/Score.h"
#include "../Components/Speed.h"
#include "../Components/Sprite.h"
#include "../Components/Image.h"
#include "../Components/Tween.h"

#include "../globals.h"

#include <aunteater/Engine.h>
#include <sstream>

using namespace TeaParty;
using namespace Archetype;
using namespace Component;
using namespace System;
using aunteater::ArchetypeTypeSet;
using aunteater::Engine;

void PhaseController::addedToEngine(Engine &aEngine)
{
    mCameras = &aEngine.getNodes<NodeCamera>();
    mEngine = &aEngine;
}

void replaceCameraRoot(aunteater::Node &aCamera, Polycode::Entity *aRoot)
{
    auto clippedScene = aCamera.get<Component::ClippedScene>().polyScene;
    clippedScene->removeEntity(clippedScene->rootEntity.getChildAtIndex(0)); // Clear
    clippedScene->addChild(aRoot);
}

void PhaseController::update(double aTime)
{
    for (aunteater::Node &camera : *mCameras)
    {
        auto assignedPlayer = camera.get<Component::PlayerReference>().entity;
        auto phase = assignedPlayer->get<Component::SelectedPhase>()->phase;
        auto & prevPhase = assignedPlayer->get<Component::SelectedPhase>()->previousPhase;

        if(phase == prevPhase)
        {
            if(phase == Component::Phase::DIPPING)
            {
                replaceCameraRoot(camera, assignedPlayer->get<Component::GamePhase>()->phaseRootEntity.get());
            }

            continue;
        }

        if(phase == Component::Phase::DIPPING)
        {
            std::ostringstream oss;
            oss << "pointCounter" << assignedPlayer->get<Index>()->index;
            aunteater::Entity &pointCounter = *(mEngine->getEntity(oss.str()));

            pointCounter.addComponent<BallsPoint>();
            pointCounter.addComponent<PointsTarget>(MAX_POINT);

            assignedPlayer->removeComponent<ActionController>();
            assignedPlayer->get<Speed>()->vX = 0.;

            aunteater::weak_entity victim = assignedPlayer->get<SelectedPhase>()->victim;
            pointCounter.addComponent<CallbackNoParam>([assignedPlayer, victim, &pointCounter]()
            {
                assignedPlayer->get<SelectedPhase>()->phase = Phase::DEFAULT;
                //pointCounter.get<BallsPoint>()->point = 0;
                pointCounter.removeComponent<BallsPoint>();
                pointCounter.removeComponent<PointsTarget>();
                pointCounter.removeComponent<CallbackNoParam>();
                assignedPlayer->addComponent<ActionController>();
                assignedPlayer->get<Score>()->score += 1;
                victim->removeComponent<CallbackOnActor>();
                victim->addComponent<IWantToDie>(3.);
                victim->get<Component::Sprite>()->polySprite->setSpriteStateByName("dying",0,false);
            });

            aunteater::Entity title;
            title.addComponent<Image>("dip_screen.png");
            title.addComponent<Position>(0., 0.);
            title.addComponent<IWantToDie>(3.);
            mEngine->addEntity(title);

            aunteater::Entity ballPaint;
            ballPaint.addComponent<Sprite>(new Polycode::SpriteSet("ball_paint.sprites"));
            ballPaint.get<Sprite>()->polySprite->setSpriteByName("ball_paint");
            ballPaint.get<Sprite>()->polySprite->setSpriteStateByName("default",0,false);
            ballPaint.addComponent<Position>(0., Y_ROOM / 2. + 30);
            ballPaint.addComponent<Component::Tween>(Vec2(0., -Y_ROOM / 2. + 30), Vec2(0., Y_ROOM / 2. - 30), 3.);
            ballPaint.addComponent<IWantToDie>(3.);
            mEngine->addEntity(ballPaint);
        }

        prevPhase = phase;
    }
}
