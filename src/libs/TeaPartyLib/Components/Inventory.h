//
//  Inventory.h
//  aunteater
//
//  Created by Franz on 05/04/14.
//
//

#ifndef _Component_Inventory_h
#define _Component_Inventory_h

#include "../InventoryStruct.h"
#include <aunteater/Component.h>
#include <map>

namespace TeaParty { namespace Component {
class Inventory : public aunteater::Component
{
public:
	Inventory()
	{
	}

	void addItemToInventory(const std::string aName, aunteater::weak_entity aInventoryItem, int aQuantity = 1)
	{
		if (mInventoryContent.find(aName) != mInventoryContent.end())
		{
			mInventoryContent.at(aName).mQuantity++;
		}
		else
		{
			mInventoryContent.insert(std::pair<std::string,TeaParty::Structure::InventoryStruct>(aName,TeaParty::Structure::InventoryStruct(aInventoryItem, aQuantity)));
		}

		//TODO(franz):Maybe there is a better way to handle the first insertion edge case
		//TODO(franz):At one point we will have to handle removal of the last item
		if (mActiveItem.empty())
		{
			mActiveItem = aName;
		}
	}

	//Maybe map is not ideal but it's seems easier to handle stock quantity
	//with a easily definable name for inventory object
	std::map<std::string, TeaParty::Structure::InventoryStruct> mInventoryContent;
	std::string mActiveItem;
private:
    COMP_CLONE(Inventory)
};
}}
#endif 