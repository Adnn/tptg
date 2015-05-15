//
//  SelectedPhase.h
//
//  Created by Adrien David.
//
//

#ifndef Component_SelectedPhase_h
#define Component_SelectedPhase_h

#include "../Vec2.h"

#include "../globals.h"

#include <Polycode.h>

#include <aunteater/Component.h>

#include <memory>

namespace TeaParty { namespace Component {

// SelectedPhase actually stores the clipping rectangle (over the window) in the PolycodeScene (cf. ctor)
// This clipping rectangle plus a displacmenent allow to simulate viewports.
enum class Phase
{
    DEFAULT,
    DIPPING
};

struct SelectedPhase : public aunteater::Component
{
    Phase phase = Phase::DEFAULT;
    Phase previousPhase = Phase::DEFAULT;

    // Dipping Phase
    aunteater::weak_entity victim = nullptr;

private:
    COMP_CLONE(SelectedPhase)
};

}} // namespace TeaParty::Component

#endif