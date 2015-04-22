#include "CollisionSolver.h"

#include "../Archetypes/Colliders.h"

using namespace aunteater;
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
                const auto & obstaclePos = obstacle.get<Component::Position>().coords;
                const auto & obstacleExtent = obstacle.get<Component::Extent>();
                const Component::Extent obstacleLimits = {obstaclePos.x-obstacleExtent.left, obstaclePos.x+obstacleExtent.right};

                if( (moverLimits.right > obstacleLimits.left && moverLimits.left < obstacleLimits.right)
                   || (moverLimits.left < obstacleLimits.right && moverLimits.right > obstacleLimits.left))
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