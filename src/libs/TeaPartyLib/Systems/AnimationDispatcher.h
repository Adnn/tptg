//
//  AnimationDispatcher.h
//
//  Created by FranzP.
//
//

#ifndef System_AnimationDispatcher_h
#define System_AnimationDispatcher_h

#include <Polycode.h>

#include <aunteater/System.h>
#include <aunteater/Family.h>

namespace TeaParty { namespace System {

class AnimationDispatcher : public aunteater::System
{
public:
    AnimationDispatcher()
    {}

    virtual void addedToEngine(aunteater::Engine &aEngine) override;
    virtual void update(double aTime) override;
    
private:
    aunteater::Nodes mAnimationables;
    aunteater::Nodes mStatefulAnimationables;
};

}} // namespace TeaParty::System

#endif