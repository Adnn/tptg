//
//  Position.h
//
//  Created by Adrien David.
//
//

#ifndef Component_Position_h
#define Component_Position_h

#include "../Vec2.h"

#include <aunteater/Component.h>
 
namespace TeaParty { namespace Component {

struct Position : public aunteater::Component
{
    Position(Vec2 aCoords, int z = 0) : coords(aCoords), z(z)
    {}

    Position(double x, double y, int z = 0) : coords{x, y}, z(z)
    {}

    Vec2 coords;
    int  z;
private:
    COMP_CLONE(Position)
};

}} // namespace TeaParty::Component

#endif