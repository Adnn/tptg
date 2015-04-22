//
//  Utilities.h
//
//  Created by Adrien David.
//
//

#ifndef System_Utilities_h
#define System_Utilities_h

#include "../Components/Extent.h"
#include "../Components/Position.h"

namespace TeaParty { namespace System {


inline TeaParty::Component::Extent getBounding(const aunteater::Node &aNode)
{
    const auto & pos = aNode.get<Component::Position>().coords;
    const auto & extent = aNode.get<Component::Extent>();
    return {pos.x-extent.left, pos.x+extent.right};
}

inline bool testCollision(const Component::Extent &aLhs, const Component::Extent &aRhs)
{
    return ( (aLhs.right > aRhs.left && aLhs.left < aRhs.right)
          || (aLhs.left < aRhs.right && aLhs.right > aRhs.left));
}



}} // namespace TeaParty::System

#endif
