//
//  Displacement.h
//
//  Created by Adrien David.
//
//

#ifndef Component_Displacement_h
#define Component_Displacement_h

#include "../Vec2.h"

#include <aunteater/Component.h>
 
namespace TeaParty { namespace Component {

struct Displacement : public aunteater::Component
{
    Displacement(Vec2 aCoords = {0., 0.}) : coords(aCoords)
    {}

    Displacement(double x, double y) : coords{x, y}
    {}

    Vec2 coords;
private:
    COMP_CLONE(Displacement)
};

//struct ProposedDisplacement : public Displacement
//{
//
//}

}} // namespace TeaParty::Component

#endif