//
//  PointTarget.h
//  tptg
//
//  Created by Franz on 14/05/15.
//
//

#ifndef _Component_PointTarget_
#define _Component_PointTarget_

#include <Polycode.h>
#include <aunteater/Component.h>

namespace TeaParty { namespace Component {
class PointsTarget : public aunteater::Component
{
public:
    PointsTarget(int aTarget):
        target(aTarget)
    {}

    const int target;

private:
    COMP_CLONE(PointsTarget)
};
}}
#endif 
