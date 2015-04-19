#include "CameraController.h"

#include "../Archetypes/NodeCamera.h"

#include "../Components/PlayerReference.h"
#include "../Components/Position.h"

#include "../globals.h"

#include <aunteater/Engine.h>


using namespace TeaParty;
using namespace System;
using namespace Archetype;
using aunteater::ArchetypeTypeSet;
using aunteater::Engine;

void CameraController::addedToEngine(Engine &aEngine)
{
    mCameras = &aEngine.getNodes<NodeCamera>();
}

void CameraController::update(double aTime)
{
    for (aunteater::Node &camera : *mCameras)
    {
        Vec2 playerPos = camera.get<Component::PlayerReference>().player->get<Component::Position>()->coords;
        Level::RoomSize size = mLevel->getARoom(playerPos.x);
        double x = std::min(size.second - CAM_WIDTH/2., std::max(size.first + CAM_WIDTH/2., playerPos.x));
        camera.get<Component::Position>().coords.x = x;
    }
}