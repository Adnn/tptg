#include "Colliders.h"

using namespace TeaParty::Archetype;
using aunteater::ArchetypeTypeSet;

const ArchetypeTypeSet NodeMove::gComponentTypes = {
    &typeid(TeaParty::Component::Displacement),
    &typeid(TeaParty::Component::Extent),
    &typeid(TeaParty::Component::Speed),
    &typeid(TeaParty::Component::Position)
};


const ArchetypeTypeSet NodeObstacle::gComponentTypes = {
    &typeid(TeaParty::Component::Extent),
    &typeid(TeaParty::Component::Position),
    &typeid(TeaParty::Component::Static)
};