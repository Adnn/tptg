#include "Physics.h"

#include "../Components/Physics.h"
#include "../Components/Speed.h"

#include <aunteater/Engine.h>

using namespace TeaParty;
using namespace System;
using aunteater::ArchetypeTypeSet;
using aunteater::Engine;

class NodePhysics
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodePhysics::gComponentTypes = {
    &typeid(Component::Physics),
    &typeid(Component::Speed)
};

void Physics::addedToEngine(Engine &aEngine)
{
    mNodeList = &aEngine.getNodes<NodePhysics>();
}

void Physics::update(double time) {
	for(aunteater::Node node : *mNodeList)
	{
		auto physics = &node.get<Component::Physics>();
		auto speed = &node.get<Component::Speed>();

		for(Vec2 force : physics->mForces)
		{
			speed->vX += force.x*(1/60.);
		}
        physics->mForces.clear();
	}
}