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
        player(aRefered)
    {}

    aunteater::weak_entity player;
private:
    COMP_CLONE(PlayerReference)
};

}} // namespace TeaParty::Component

#endif