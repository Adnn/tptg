//
//  CallbackOnActor.h
//
//  Created by Adrien David.
//
//

#ifndef Component_CallbackOnActor_h
#define Component_CallbackOnActor_h

#include "../Vec2.h"

#include <aunteater/Component.h>
#include <aunteater/Node.h>

#include <functional>

namespace TeaParty { namespace Component {

struct CallbackOnActor : public aunteater::Component
{
    typedef std::function<void(aunteater::Entity &)> Function;

    CallbackOnActor(Function aCallback) :
            callback(aCallback)
    {}

    Function callback;

private:
    COMP_CLONE(CallbackOnActor)
};

}} // namespace TeaParty::Component

#endif