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

struct CollisionBox
{
    Component::Extent extent;
    int z;
};

inline CollisionBox getBounding(aunteater::Node &aNode)
{
    const auto & pos = aNode.get<Component::Position>().coords;
    const auto & extent = aNode.get<Component::Extent>();
    return {TeaParty::Component::Extent(pos.x-extent.left, pos.x+extent.right),
            aNode.get<Component::Position>().z};
}

inline bool testCollision_extent(const Component::Extent &aLhs, const Component::Extent &aRhs)
{
    return ( (aLhs.right > aRhs.left && aLhs.left < aRhs.right)
          || (aLhs.left < aRhs.right && aLhs.right > aRhs.left));
}

inline bool testCollision(const CollisionBox &aLhs, const CollisionBox &aRhs)
{
    return (aLhs.z == aRhs.z) && (testCollision_extent(aLhs.extent, aRhs.extent));
}



}} // namespace TeaParty::System

#endif
