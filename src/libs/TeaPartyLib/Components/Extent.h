//
//  Extent.h
//
//  Created by Adrien David.
//
//

#ifndef Component_Extent_h
#define Component_Extent_h

#include "../Vec2.h"

#include <aunteater/Component.h>
 
namespace TeaParty { namespace Component {

struct Extent : public aunteater::Component
{
    Extent(Vec2 aCoords = {0., 0.}) :
            left(aCoords.x),
            right(aCoords.y)
    {}

    Extent(double left, double right) :
            left(left),
            right(right)
    {}

    double left;
    double right;

private:
    COMP_CLONE(Extent)
};

}} // namespace TeaParty::Component

#endif