#include "PhaseController.h"

#include "../Archetypes/NodeCamera.h"

#include "../Components/GamePhase.h"
#include "../Components/PlayerReference.h"
#include "../Components/Position.h"

#include "../globals.h"

#include <aunteater/Engine.h>


using namespace TeaParty;
using namespace System;
using namespace Archetype;
using aunteater::ArchetypeTypeSet;
using aunteater::Engine;

void PhaseController::addedToEngine(Engine &aEngine)
{
    mCameras = &aEngine.getNodes<NodeCamera>();
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
        auto phase = camera.get<Component::SelectedPhase>().phase;
        if(phase == Component::Phase::DIPPING)
        {
            replaceCameraRoot(camera, camera.get<Component::PlayerReference>().entity->get<Component::GamePhase>()->phaseRootEntity.get());
        }
    }
}
