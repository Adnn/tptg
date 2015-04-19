#include "Level.h"

#include "Components/Image.h"
#include "Components/Position.h"

#include <aunteater/Engine.h>

using namespace TeaParty;

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

        rightOffset += width;
    }
}

Level::RoomSize Level::getARoom(double x, double z)
{
    auto foundIt = std::find_if(mDefinition.begin(), mDefinition.end(), [this, x](const RoomSize &aSize)
        {
            return x >= aSize.first && x <= aSize.second;
        });

    return *foundIt;
}