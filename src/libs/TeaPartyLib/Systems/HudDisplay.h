//
//  HudDisplay.h
//
//  Created by Franz.
//
//

#ifndef System_HudDisplay_h
#define System_HudDisplay_h

#include <Polycode.h>

#include <aunteater/System.h>
#include <aunteater/Family.h>

namespace TeaParty { namespace System {

class HudDisplay : public aunteater::System, public aunteater::FamilyObserver
{
public:
    HudDisplay();

    virtual void addedToEngine(aunteater::Engine &aEngine) override;
    virtual void update(double aTime) override;

    virtual void addedNode(aunteater::Node &aNode) override;
    virtual void removedNode(aunteater::Node &aNode) override;
    
private:
    aunteater::Nodes mHudRenderables;
    Polycode::Scene mScene;
};

}} // namespace TeaParty::System

#endif