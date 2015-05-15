//
//  PointsTrigger.h
//  aunteater
//

#ifndef __aunteater__SytemPointsTrigger__
#define __aunteater__SytemPointsTrigger__

#include <aunteater/System.h>
#include <aunteater/Engine.h>
#include <aunteater/Node.h>


namespace TeaParty { namespace System {

class PointsTrigger : public aunteater::System
{
public:
	virtual void addedToEngine(aunteater::Engine &aEngine);
	virtual void update(double time);

public:
	aunteater::Nodes mPointsTriggers;
};

}} //namespace TeaParty::System

#endif /* defined(__aunteater__SytemPointsTrigger) */
