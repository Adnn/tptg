#include "Level.h"

#include "Components/Extent.h"
#include "Components/Image.h"
#include "Components/Position.h"

#include "globals.h"

#include <aunteater/Engine.h>

using namespace TeaParty;

void makeWall(double aPosition, aunteater::Engine &aEngine)
{
    aunteater::Entity wall;
    wall.addComponent<Component::Extent>(WALL_EXTENT, WALL_EXTENT);
    wall.addComponent<Component::Position>(aPosition, 0);
    aEngine.addEntity(wall);

}

Level::Level(std::istream &aDefinitionStream, aunteater::Engine &aEngine)
{
    std::string roomImageFile;
    double rightOffset = 0.;

    while(aDefinitionStream >> roomImageFile)
    {
        aunteater::Entity room;
        room.addComponent<Component::Image>(roomImageFile);
        double width = room.get<Component::Image>()->polyImage->getWidth();
        room.addComponent<Component::Position>(rightOffset + width/2., 0);
        aEngine.addEntity(room);

        mDefinition.push_back({rightOffset, rightOffset+width});

        makeWall(rightOffset, aEngine);

        rightOffset += width;
    }

    makeWall(rightOffset, aEngine);
}

Level::RoomSize Level::getARoom(double x, double z)
{
    auto foundIt = std::find_if(mDefinition.begin(), mDefinition.end(), [this, x](const RoomSize &aSize)
        {
            return x >= aSize.first && x <= aSize.second;
        });

    return *foundIt;
}