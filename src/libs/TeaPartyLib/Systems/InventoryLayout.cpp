#include "InventoryLayout.h"

#include "../Components/Inventory.h"
#include "../Components/Position.h"
#include "../Components/HudItem.h"
#include "../Vec2.h"

#include <aunteater/Engine.h>

using namespace TeaParty;
using namespace System;
using aunteater::ArchetypeTypeSet;
using aunteater::Engine;

class NodeInventoryLayout
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodeInventoryLayout::gComponentTypes = {
    &typeid(Component::Inventory)
};

void InventoryLayout::addedToEngine(Engine &aEngine)
{
    mNodeList = &aEngine.getNodes<NodeInventoryLayout>();
}

void InventoryLayout::update(double time) {
	for(aunteater::Node node : *mNodeList)
	{
		const auto inventory = &node.get<Component::Inventory>();

		Vec2 pos(0.0f,0.0f);

		for (auto &item : inventory->mInventoryContent) {
			auto itemPos = item.second.mEntity->get<Component::Position>();
			const auto image = item.second.mEntity->get<Component::HudItem>();

			itemPos->coords = pos;

			pos += Vec2(image->polyImage.get()->getWidth(),0);

		}
	}
}