//
//  PendulumPhysics.h
//
//  Created by Adrien David.
//
//

#ifndef System_PendulumPhysics_h
#define System_PendulumPhysics_h

#include "../Level.h"

#include <Polycode.h>

#include <aunteater/System.h>
#include <aunteater/Family.h>

namespace TeaParty { namespace System {

class PendulumPhysics : public aunteater::System
{
public:
    virtual void addedToEngine(aunteater::Engine &aEngine) override;
    virtual void update(double aTime) override;

private:
    aunteater::Nodes mPendulums;
};

}} // namespace TeaParty::System

#endif
