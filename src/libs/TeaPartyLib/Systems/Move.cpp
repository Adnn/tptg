#include "Move.h"

#include "../Components/Speed.h"
#include "../Components/Position.h"

using namespace aunteater;
using namespace TeaParty;
using namespace System;

class NodeMove
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodeMove::gComponentTypes =
    { &typeid(TeaParty::Component::Speed),
      &typeid(TeaParty::Component::Position) };

Move::Move()
{
}

void Move::addedToEngine(aunteater::Engine &aEngine)
{
	mNodeList = &aEngine.getNodes<NodeMove>();
}

void Move::update(double time)
{
	for (aunteater::Node node : *mNodeList)
	{
		const auto speed = node.get<Component::Speed>();
		auto position = &node.get<Component::Position>();
		position->coords.x += speed.vX;
	}
}