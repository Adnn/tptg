//
//  NodeTriggersActors.h
//
//  Created by Adrien David.
//
//

#ifndef TeaParty_NodeTriggersActors_h
#define TeaParty_NodeTriggersActors_h

#include <aunteater/globals.h>

#include "../Components/ActionController.h"
#include "../Components/CallbackOnActor.h"
#include "../Components/Extent.h"
#include "../Components/Position.h"
#include "../Components/Speed.h"
#include "../Components/TriggeringAction.h"


namespace TeaParty { namespace Archetype {

class NodeActor
{
public:
    static const aunteater::ArchetypeTypeSet gComponentTypes;
};

class NodeTrigger
{
public:
    static const aunteater::ArchetypeTypeSet gComponentTypes;
};

}} // namespace TeaParty::Archetype

#endif