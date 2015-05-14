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

    struct RoomParams
    {
        double first; //xmin
        double second; //xmax
        int z;
    };

    RoomParams getARoom(double x, double z);

protected:
    void makeWall(double aPosition, aunteater::Engine &aEngine);
    void makePortal(double aPosition, double aOutputPosition, aunteater::Engine &aEngine);
    void makePortalZ(double aPosition, int aInputZ, int aOutputZ, aunteater::Engine &aEngine);

    void nextLayer();
    
private:
    std::vector<RoomParams> mDefinition;
    int mCurrentZIndex = 0;
    double mRightOffset = 0.;
};

} // namespace TeaParty

#endif
