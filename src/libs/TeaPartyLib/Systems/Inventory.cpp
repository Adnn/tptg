#include "Inventory.h"

#include "../Components/Inventory.h"
#include "../Components/ActionController.h"

#include <aunteater/Engine.h>

using namespace TeaParty;
using namespace System;
using aunteater::ArchetypeTypeSet;
using aunteater::Engine;

class NodeInventory
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodeInventory::gComponentTypes = {
    &typeid(Component::Inventory),
    &typeid(Component::ActionController)
};

void Inventory::addedToEngine(Engine &aEngine)
{
    mNodeList = &aEngine.getNodes<NodeInventory>();
}

void Inventory::update(double time) {
	for(aunteater::Node node : *mNodeList)
	{
		const auto action = node.get<Component::ActionController>();
		auto inventory = &node.get<Component::Inventory>();

		auto activeItem = inventory->mInventoryContent.find(inventory->mActiveItem);

		//For now toggle inventory action is hard coded
		if (Component::statisfies(Component::Action::T, action))
		{
			if (++activeItem == inventory->mInventoryContent.end())
			{
				inventory->mActiveItem = inventory->mInventoryContent.begin()->first;
			}
			else
			{
				inventory->mActiveItem = activeItem->first;
			}
		}
	}
}