//
//  CameraController.h
//
//  Created by Adrien David.
//
//

#ifndef System_CameraController_h
#define System_CameraController_h

#include "../Level.h"

#include <Polycode.h>

#include <aunteater/System.h>
#include <aunteater/Family.h>

namespace TeaParty { namespace System {

class CameraController : public aunteater::System
{
public:
    CameraController(Level *aLevel) :
        mLevel(aLevel)
    {}

    virtual void addedToEngine(aunteater::Engine &aEngine) override;
    virtual void update(double aTime) override;

private:
    aunteater::Nodes mCameras;
    Level *mLevel;
};

}} // namespace TeaParty::System

#endif