//
//  Level.h
//
//  Created by Adrien David.
//
//

#ifndef TeaParty_Level_h
#define TeaParty_Level_h

#include <vector>

namespace aunteater
{
    class Engine;
}

namespace TeaParty {

class Level
{
public:
    Level(std::istream &aDefinitionStream, aunteater::Engine &aEngine);

    typedef std::pair<double, double> RoomSize;

    RoomSize getARoom(double x, double z=0);

private:
    std::vector<RoomSize> mDefinition;
};

} // namespace TeaParty

#endif
