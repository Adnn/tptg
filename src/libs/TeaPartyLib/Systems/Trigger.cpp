#include "Trigger.h"

#include "Utilities.h"

#include "../Archetypes/TriggersActors.h"

using namespace TeaParty;
using namespace Archetype;
using namespace System;


void Trigger::addedToEngine(aunteater::Engine &aEngine)
{
    mActors = &aEngine.getNodes<NodeActor>();
    mTriggers = &aEngine.getNodes<NodeTrigger>();
}

void Trigger::update(double time)
{
    for (aunteater::Node actor : *mActors)
    {
        const CollisionBox actorLimits = getBounding(actor);
        for (aunteater::Node trigger : *mTriggers)
        {
            const CollisionBox triggerLimits = getBounding(trigger);
            if(testCollision(actorLimits, triggerLimits))
            {
                const auto &actorActions = actor.get<Component::ActionController>();
                const auto &triggerSetOff = trigger.get<Component::TriggeringAction>().expected;
                if(Component::statisfies(triggerSetOff, actorActions))
                {
                    trigger.get<Component::CallbackOnActor>().callback(actor);
                    break; // One portal a frame, or you're gonna have a baaaad time.
                }
            }
        }
    }
}