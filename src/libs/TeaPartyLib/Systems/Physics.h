//
//  Physics.h
//
//  Created by FranzP.
//
//

#ifndef System_Physics_h
#define System_Physics_h

#include <Polycode.h>

#include <aunteater/System.h>
#include <aunteater/Family.h>

namespace TeaParty { namespace System {

class Physics : public aunteater::System
{
public:
    Physics()
    {}

    virtual void addedToEngine(aunteater::Engine &aEngine) override;
    virtual void update(double aTime) override;
    
private:
    aunteater::Nodes mNodeList;
};

}} // namespace TeaParty::System

#endif