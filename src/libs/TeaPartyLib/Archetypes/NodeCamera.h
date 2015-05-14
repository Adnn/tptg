//
//  NodeCamera.h
//
//  Created by Adrien David.
//
//

#ifndef TeaParty_NodeCamera_h
#define TeaParty_NodeCamera_h

#include <aunteater/globals.h>

#include "../Components/ClippedScene.h"
#include "../Components/PlayerReference.h"
#include "../Components/Position.h"
#include "../Components/SelectedPhase.h"

namespace TeaParty { namespace Archetype {

class NodeCamera
{
public:
    static const aunteater::ArchetypeTypeSet gComponentTypes;
};

}} // namespace TeaParty::Archetype

#endif