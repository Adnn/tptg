//
//  Display.h
//
//  Created by Adrien David.
//
//

#ifndef System_Display_h
#define System_Display_h

#include <Polycode.h>

#include <aunteater/System.h>
#include <aunteater/Family.h>

namespace TeaParty { namespace System {

class Display : public aunteater::System, public aunteater::FamilyObserver
{
public:
    Display();

    virtual void addedToEngine(aunteater::Engine &aEngine) override;
    virtual void update(double aTime) override;

    virtual void addedNode(aunteater::Node &aNode) override;
    virtual void removedNode(aunteater::Node &aNode) override;
    
private:
    aunteater::Nodes mRenderables;
    Polycode::Scene mScene;
};

}} // namespace TeaParty::System

#endif
