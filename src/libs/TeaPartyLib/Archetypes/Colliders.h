//
//  NodeMoving.h
//
//  Created by Adrien David.
//
//

#ifndef TeaParty_NodeMoving_h
#define TeaParty_NodeMoving_h

#include <aunteater/globals.h>

#include "../Components/Displacement.h"
#include "../Components/Extent.h"
#include "../Components/Speed.h"
#include "../Components/Position.h"


namespace TeaParty { namespace Archetype {

class NodeMove
{
public:
    static const aunteater::ArchetypeTypeSet gComponentTypes;
};

class NodeObstacle
{
public:
    static const aunteater::ArchetypeTypeSet gComponentTypes;
};

}} // namespace TeaParty::Archetype

#endif