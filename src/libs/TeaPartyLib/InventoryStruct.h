#ifndef TeaParty_InventoryStruct_h
#define TeaParty_InventoryStruct_h

#include <aunteater/Component.h>

namespace TeaParty { namespace Structure {
struct InventoryStruct {
	InventoryStruct(aunteater::weak_entity aEntity, int aQuantity = 1) :
		mEntity(aEntity),
		mQuantity(aQuantity)
	{}
	const aunteater::weak_entity mEntity;
	int mQuantity;
};

}}
#endif