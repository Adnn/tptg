//
//  PlayerReference.h
//
//  Created by Adrien David.
//
//

#ifndef Component_PlayerReference_h
#define Component_PlayerReference_h

#include "../Vec2.h"

#include <Polycode.h>

#include <aunteater/Component.h>

#include <memory>

namespace TeaParty { namespace Component {

struct PlayerReference : public aunteater::Component
{
    PlayerReference(aunteater::weak_entity aRefered) :
        entity(aRefered)
    {}

    aunteater::weak_entity entity;
private:
    COMP_CLONE(PlayerReference)
};

typedef PlayerReference PivotReference;

}} // namespace TeaParty::Component

#endif