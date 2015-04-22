#include "CollisionSolver.h"

#include "Utilities.h"

#include "../Archetypes/Colliders.h"

using namespace TeaParty;
using namespace Archetype;
using namespace System;


void CollisionSolver::addedToEngine(aunteater::Engine &aEngine)
{
    mMovers = &aEngine.getNodes<NodeMove>();
    mObstacles = &aEngine.getNodes<NodeObstacle>();
}

void CollisionSolver::update(double time)
{
    for (aunteater::Node mover : *mMovers)
    {
        const auto & moverDisplacement = mover.get<Component::Displacement>().coords;
        auto expectedPos = mover.get<Component::Position>().coords + moverDisplacement;
        const auto &moverExtent = mover.get<Component::Extent>();
        const Component::Extent moverLimits = {expectedPos.x-moverExtent.left, expectedPos.x+moverExtent.right};

        for (aunteater::Node obstacle : *mObstacles)
        {
            if( ! obstacle.getEntity()->has<Component::Displacement>()) // static objects first
            {
                const Component::Extent obstacleLimits = getBounding(obstacle);
                if(testCollision(moverLimits, obstacleLimits))
                {
                    expectedPos.x +=  moverDisplacement.x > 0 ?
                                        -1 * (moverLimits.right - obstacleLimits.left) :
                                        obstacleLimits.right - moverLimits.left ;
                }
            }
        }

        mover.get<Component::Position>().coords = expectedPos;
    }
}