//
//  Pendular.h
//
//  Created by Adrien David.
//
//

#ifndef Component_Pendular_h
#define Component_Pendular_h

#include "../Vec2.h"

#include <Polycode.h>

#include <aunteater/Component.h>

#include <memory>

namespace TeaParty { namespace Component {

struct Pendular : public aunteater::Component
{
    Pendular (double aLength, double aDamping, aunteater::weak_entity point) :
              length(aLength),
              damping(aDamping),
              pointCounter(point)
    {}

    const double length;
    const double damping;
    aunteater::weak_entity pointCounter;

    double theta=0.;
    double thetaSpeed=0.;
    Vec2 pivotPreviousSpeed = {0., 0.};


private:
    COMP_CLONE(Pendular)
};

}} // namespace TeaParty::Component

#endif
