#include "PhaseController.h"

#include "../Archetypes/NodeCamera.h"

#include "../Components/CallbackNoParam.h"
#include "../Components/GamePhase.h"
#include "../Components/Index.h"
#include "../Components/PlayerReference.h"
#include "../Components/PointsTarget.h"
#include "../Components/Position.h"

#include "../globals.h"

#include <aunteater/Engine.h>


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
        if(phase == Component::Phase::DIPPING)
        {
            replaceCameraRoot(camera, assignedPlayer->get<Component::GamePhase>()->phaseRootEntity.get());
            std::ostringstream oss;

            //oss << "pointCounter" << assignedPlayer->get<Index>()->index;
            //std::cout << oss.str() << std::endl;
            //aunteater::Entity &pointCounter = *(mEngine->getEntity(oss.str()));
            aunteater::weak_entity pointCounter = assignedPlayer->get<Index>()->ballsCounter;

            pointCounter->addComponent<PointsTarget>(MAX_POINT);
            
            pointCounter->addComponent<CallbackNoParam>([assignedPlayer]()
            {
                assignedPlayer->get<SelectedPhase>()->phase = Phase::DEFAULT;
            });
        }
    }
}
