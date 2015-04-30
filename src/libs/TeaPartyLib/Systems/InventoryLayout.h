//
//  InventoryLayout.h
//  TeaParty
//
//  Created by Franz on 28/04/15.
//
//

#ifndef _System_InventoryLayout_h
#define _System_InventoryLayout_h

#include <Polycode.h>

#include <aunteater/System.h>
#include <aunteater/Node.h>
#include <aunteater/Engine.h>

namespace TeaParty { namespace System {
class InventoryLayout : public aunteater::System
{
public:
	InventoryLayout()
	{}

	virtual void addedToEngine(aunteater::Engine &aEngine);
	virtual void update(double time);

public:
	aunteater::weak_entity mCurrentIndicator;
	aunteater::Nodes mNodeList;
};
}}

#endif 