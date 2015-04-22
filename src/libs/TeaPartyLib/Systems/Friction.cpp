#include "Friction.h"

#include "../Components/Physics.h"
#include "../Components/Speed.h"

#include <aunteater/Engine.h>

using namespace TeaParty;
using namespace System;
using aunteater::ArchetypeTypeSet;
using aunteater::Engine;

class NodeFriction
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodeFriction::gComponentTypes = {
    &typeid(Component::Physics),
    &typeid(Component::Speed)
};

void Friction::addedToEngine(Engine &aEngine)
{
    mNodeList = &aEngine.getNodes<NodeFriction>();
}

void Friction::update(double time) {
	for(aunteater::Node node : *mNodeList)
	{
		auto physics = &node.get<Component::Physics>();
		auto speed = node.get<Component::Speed>();
		physics->mForces.push_back(Vec2(-speed.vX / BASE_FRICTION,0));
	}
}