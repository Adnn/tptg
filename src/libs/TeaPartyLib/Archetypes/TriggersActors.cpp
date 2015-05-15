#include "TriggersActors.h"

using namespace TeaParty::Archetype;
using aunteater::ArchetypeTypeSet;

const ArchetypeTypeSet NodeActor::gComponentTypes = {
    &typeid(TeaParty::Component::ActionController),
    &typeid(TeaParty::Component::Extent),
    &typeid(TeaParty::Component::Position)
};

const ArchetypeTypeSet NodeTrigger::gComponentTypes = {
    &typeid(TeaParty::Component::CallbackOnActor),
    &typeid(TeaParty::Component::TriggeringAction),
    &typeid(TeaParty::Component::Extent),
    &typeid(TeaParty::Component::Position)
};
