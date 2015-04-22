//
//  CollisionSolver.h
//  aunteater
//

#ifndef __aunteater__SytemCollisionSolver__
#define __aunteater__SytemCollisionSolver__

#include <aunteater/System.h>
#include <aunteater/Engine.h>
#include <aunteater/Node.h>


namespace TeaParty { namespace System {

class CollisionSolver : public aunteater::System
{
public:
	virtual void addedToEngine(aunteater::Engine &aEngine);
	virtual void update(double time);

public:
	aunteater::Nodes mMovers;
	aunteater::Nodes mObstacles;
};

}} //namespace TeaParty::System

#endif /* defined(__aunteater__SytemCollisionSolver) */