//
//  Static.h
//
//  Created by Adrien David.
//
//

#ifndef Component_Static_h
#define Component_Static_h

#include "../Vec2.h"

#include <aunteater/Component.h>
#include <aunteater/Node.h>

#include <functional>

namespace TeaParty { namespace Component {

struct Static : public aunteater::Component
{
private:
    COMP_CLONE(Static)
};

}} // namespace TeaParty::Component

#endif