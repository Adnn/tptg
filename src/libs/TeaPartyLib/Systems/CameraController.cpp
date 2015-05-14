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
        auto pos = camera.get<Component::PlayerReference>().entity->get<Component::Position>();
        Vec2 playerPos = pos->coords;
        int playerZ = pos->z;
        Level::RoomParams room = mLevel->getARoom(playerPos.x, playerZ);
        double x = std::min(room.second - CAM_WIDTH/2., std::max(room.first + CAM_WIDTH/2., playerPos.x));
        camera.get<Component::Position>().coords.x = x;
        camera.get<Component::Position>().z = playerZ;
    }
}