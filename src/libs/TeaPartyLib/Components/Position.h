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
    Position(Vec2 aCoords) : coords(aCoords)
    {}

    Position(double x, double y) : coords{x, y}
    {}

    Vec2 coords;
    int  z;
private:
    COMP_CLONE(Position)
};

}} // namespace TeaParty::Component

#endif