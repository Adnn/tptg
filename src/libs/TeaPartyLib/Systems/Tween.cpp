#include "Tween.h"

#include "../Components/Tween.h"
#include "../Components/Position.h"

#include <aunteater/Engine.h>

using namespace TeaParty;
using namespace System;
using aunteater::ArchetypeTypeSet;


class NodeTween
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodeTween::gComponentTypes = {
    &typeid(Component::Tween),
    &typeid(Component::Position)
};

void Tween::addedToEngine(aunteater::Engine &aEngine)
{
    mNodeList = &aEngine.getNodes<NodeTween>();
}

void Tween::update(double time)
{
	auto node = mNodeList->begin();
	while(node != mNodeList->end()) {
		auto &pos = node->get<Component::Position>();
		auto &tween = node->get<Component::Tween>();

		pos.coords += tween.mTweenTable[tween.mIndex++];

		if (tween.mIndex == tween.mTweenTable.size())
		{
			node++->getEntity()->removeComponent<Component::Tween>(); 
		}
		else
		{
			node++;
		}
	}
}