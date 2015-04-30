#include "InventoryLayout.h"

#include "../Components/Inventory.h"
#include "../Components/Position.h"
#include "../Components/HudItem.h"
#include "../Components/Tween.h"
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
	aunteater::Entity currentIndicator;
    currentIndicator.addComponent<Component::HudItem>(new Polycode::SpriteSet("inventoryIndex.sprites"));
    currentIndicator.get<Component::HudItem>()->polySprite.get()->setSpriteByName("index");
    currentIndicator.get<Component::HudItem>()->polySprite.get()->setSpriteStateByName("default",0,false);
    currentIndicator.addComponent<Component::Position>(0,0);
    mCurrentIndicator = aEngine.addEntity("indicator",currentIndicator);
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

			pos += Vec2(image->polySprite.get()->getWidth(),0);

		}

		auto itemPos = inventory->mInventoryContent.find(inventory->mActiveItem)->second.mEntity->get<Component::Position>();
		
		if (mCurrentIndicator->get<Component::Position>()->coords != itemPos->coords
			&& !mCurrentIndicator->has<Component::Tween>())
		{
			mCurrentIndicator->addComponent<Component::Tween>(
				mCurrentIndicator->get<Component::Position>()->coords,
				itemPos->coords,
				0.2);
		}
	}
}