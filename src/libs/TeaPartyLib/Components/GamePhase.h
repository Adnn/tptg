//
//  GamePhase.h
//
//  Created by Adrien David.
//
//

#ifndef Component_GamePhase_h
#define Component_GamePhase_h

#include "../Vec2.h"

#include "../globals.h"

#include <Polycode.h>

#include <aunteater/Component.h>

#include <memory>

namespace TeaParty { namespace Component {

// GamePhase actually stores the clipping rectangle (over the window) in the PolycodeScene (cf. ctor)
// This clipping rectangle plus a displacmenent allow to simulate viewports.
struct GamePhase : public aunteater::Component
{
    GamePhase() :
        phaseRootEntity(std::make_shared<Polycode::SceneEntity>())
    {}

    std::shared_ptr<Polycode::SceneEntity> phaseRootEntity;

private:
    COMP_CLONE(GamePhase)
};

}} // namespace TeaParty::Component

#endif
