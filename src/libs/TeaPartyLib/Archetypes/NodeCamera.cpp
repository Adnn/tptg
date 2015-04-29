#include "NodeCamera.h"


using namespace TeaParty::Archetype;
using aunteater::ArchetypeTypeSet;
using namespace TeaParty;

const ArchetypeTypeSet NodeCamera::gComponentTypes = {
    &typeid(Component::ClippedScene),
    &typeid(Component::Position),
    &typeid(Component::PlayerReference)
};


