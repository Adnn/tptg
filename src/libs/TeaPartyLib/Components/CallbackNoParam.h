//
//  CallbackNoParam.h
//
//  Created by Adrien David.
//
//

#ifndef Component_CallbackNoParam_h
#define Component_CallbackNoParam_h

#include "../Vec2.h"

#include <aunteater/Component.h>
#include <aunteater/Node.h>

#include <functional>

namespace TeaParty { namespace Component {

struct CallbackNoParam : public aunteater::Component
{
    typedef std::function<void()> Function;

    CallbackNoParam(Function aCallback) :
            callback(aCallback)
    {}

    Function callback;

private:
    COMP_CLONE(CallbackNoParam)
};

}} // namespace TeaParty::Component

#endif
