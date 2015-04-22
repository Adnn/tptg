#include "Move.h"

#include "../Archetypes/Colliders.h"

using namespace aunteater;
using namespace TeaParty;
using namespace Archetype;
using namespace System;

void Move::addedToEngine(aunteater::Engine &aEngine)
{
	mNodeList = &aEngine.getNodes<NodeMove>();
}

void Move::update(double time)
{
	for (aunteater::Node node : *mNodeList)
	{
		const auto speed = node.get<Component::Speed>();
        node.get<Component::Displacement>().coords.x = speed.vX /* * time */;
	}
}