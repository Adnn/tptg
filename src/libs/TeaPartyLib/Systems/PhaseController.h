//
//  PhaseController.h
//
//  Created by Adrien David.
//
//

#ifndef System_PhaseController_h
#define System_PhaseController_h

#include "../Level.h"

#include <Polycode.h>

#include <aunteater/System.h>
#include <aunteater/Family.h>

namespace TeaParty { namespace System {

class PhaseController : public aunteater::System
{
public:
    virtual void addedToEngine(aunteater::Engine &aEngine) override;
    virtual void update(double aTime) override;

private:
    aunteater::Nodes mCameras;
};

}} // namespace TeaParty::System

#endif
