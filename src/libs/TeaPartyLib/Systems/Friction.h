//
//  Friction.h
//
//  Created by FranzP.
//
//

#ifndef System_Friction_h
#define System_Friction_h

#include <Polycode.h>

#include <aunteater/System.h>
#include <aunteater/Family.h>

#define BASE_FRICTION 0.10

namespace TeaParty { namespace System {

class Friction : public aunteater::System
{
public:
    Friction()
    {}

    virtual void addedToEngine(aunteater::Engine &aEngine) override;
    virtual void update(double aTime) override;
    
private:
    aunteater::Nodes mNodeList;
};

}} // namespace TeaParty::System

#endif