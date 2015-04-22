//
//  Trigger.h
//  aunteater
//

#ifndef __aunteater__SytemTrigger__
#define __aunteater__SytemTrigger__

#include <aunteater/System.h>
#include <aunteater/Engine.h>
#include <aunteater/Node.h>


namespace TeaParty { namespace System {

class Trigger : public aunteater::System
{
public:
	virtual void addedToEngine(aunteater::Engine &aEngine);
	virtual void update(double time);

public:
	aunteater::Nodes mTriggers;
	aunteater::Nodes mActors;
};

}} //namespace TeaParty::System

#endif /* defined(__aunteater__SytemTrigger) */