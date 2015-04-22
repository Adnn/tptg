//
//  TriggeringAction.h
//
//  Created by Adrien David.
//
//

#ifndef Component_TriggeringAction_h
#define Component_TriggeringAction_h

#include "../Vec2.h"
#include "ActionController.h" /// \todo there is a dependency to another Component, is that ok ?

#include <aunteater/Component.h>
 
namespace TeaParty { namespace Component {

struct TriggeringAction : public aunteater::Component
{
    TriggeringAction(Action aAction) :
            expected(aAction)
    {}

    Action expected;

private:
    COMP_CLONE(TriggeringAction)
};

}} // namespace TeaParty::Component

#endif