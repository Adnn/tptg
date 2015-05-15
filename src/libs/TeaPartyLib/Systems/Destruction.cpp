#include "Destruction.h"

#include "../Components/IWantToDie.h"

#include <aunteater/Engine.h>
#include <Polycode.h>

using namespace aunteater;
using namespace TeaParty;
using namespace System;

class NodeDestruction
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodeDestruction::gComponentTypes =
    { &typeid(TeaParty::Component::IWantToDie)};

Destruction::Destruction()
{
}

void Destruction::addedToEngine(aunteater::Engine &aEngine)
{
    mToDestroy = &aEngine.getNodes<NodeDestruction>();
    mEngine = &aEngine;
}

void Destruction::update(double time)
{
	std::vector<aunteater::weak_entity> entitiesToDestroy;
    for (auto & node : *mToDestroy)
    {
    	auto &count = node.get<TeaParty::Component::IWantToDie>().delay;

    	if (count < 0)
    	{
    		entitiesToDestroy.push_back(node.getEntity());
    	}
    	else
    	{
    		count -= 1/60.;
    	}
    }

    for (auto it = entitiesToDestroy.begin(); it != entitiesToDestroy.end();it++)
    {
    	mEngine->removeEntity(*it);
    }
}