#include "Level.h"

#include "Components/CallbackOnActor.h"
#include "Components/Extent.h"
#include "Components/Image.h"
#include "Components/Position.h"
#include "Components/Static.h"
#include "Components/TriggeringAction.h"

#include "globals.h"

#include <aunteater/Engine.h>

using namespace TeaParty;

void Level::makeWall(double aPosition, aunteater::Engine &aEngine)
{
    aunteater::Entity wall;
    wall.addComponent<Component::Extent>(WALL_EXTENT, WALL_EXTENT);
    wall.addComponent<Component::Position>(Vec2{aPosition, 0}, mCurrentZIndex);
    wall.addComponent<Component::Static>();
    aEngine.addEntity(wall);

}

void Level::makePortal(double aPosition, double aOutputPosition, aunteater::Engine &aEngine)
{
    aunteater::Entity doorPortal;
    doorPortal.addComponent<Component::CallbackOnActor>([aOutputPosition](aunteater::Node &aActor)
                                                        {aActor.get<Component::Position>().coords.x = aOutputPosition;});
    doorPortal.addComponent<Component::TriggeringAction>(Component::Action::A);
    doorPortal.addComponent<Component::Position>(Vec2{aPosition, 0}, mCurrentZIndex);
    doorPortal.addComponent<Component::Extent>(PORTAL_EXTENT, PORTAL_EXTENT);
    aEngine.addEntity(doorPortal);
}

void Level::makePortalZ(double aPosition, int aInputZ, int aOutputZ, aunteater::Engine &aEngine)
{
    aunteater::Entity doorPortal;
    doorPortal.addComponent<Component::CallbackOnActor>([aOutputZ](aunteater::Node &aActor)
                                                        {aActor.get<Component::Position>().z = aOutputZ;});
    doorPortal.addComponent<Component::TriggeringAction>(Component::Action::A);
    doorPortal.addComponent<Component::Position>(Vec2{aPosition, 0}, aInputZ);
    doorPortal.addComponent<Component::Extent>(PORTAL_EXTENT, PORTAL_EXTENT);
    aEngine.addEntity(doorPortal);
}


void Level::nextLayer()
{
    mRightOffset = 0.;
    ++mCurrentZIndex;
}

Level::Level(std::istream &aDefinitionStream, aunteater::Engine &aEngine)
{
    std::string roomImageFile;

    while(aDefinitionStream >> roomImageFile)
    {
        if(roomImageFile == "ZUP")
        {
            makeWall(mRightOffset, aEngine);
            nextLayer();
            continue;
        }

        if(mRightOffset)
        {
            double positionA = mRightOffset - WALL_EXTENT - PORTAL_EXTENT/2.;
            double positionB = mRightOffset + WALL_EXTENT + PORTAL_EXTENT/2.;
            makePortal(positionA, positionB, aEngine);
            makePortal(positionB, positionA, aEngine);
        }

        if(mCurrentZIndex)
        {
            makePortalZ(mRightOffset + X_ROOM/2., mCurrentZIndex, mCurrentZIndex-1, aEngine);
            makePortalZ(mRightOffset + X_ROOM/2., mCurrentZIndex-1, mCurrentZIndex, aEngine);
        }

        aunteater::Entity room;
        room.addComponent<Component::Image>(roomImageFile);
        double width = room.get<Component::Image>()->polyImage->getWidth();
        room.addComponent<Component::Position>(Vec2{mRightOffset + width/2., 0}, mCurrentZIndex);
        aEngine.addEntity(room);

        mDefinition.push_back({mRightOffset, mRightOffset+width, mCurrentZIndex});

        makeWall(mRightOffset, aEngine);

        mRightOffset += width;
    }

    makeWall(mRightOffset, aEngine);
}

Level::RoomParams Level::getARoom(double x, double z)
{
    auto foundIt = std::find_if(mDefinition.begin(), mDefinition.end(), [this, x, z](const RoomParams &aSize)
        {
            return (z == aSize.z) && (x >= aSize.first && x <= aSize.second);
        });

    return *foundIt;
}