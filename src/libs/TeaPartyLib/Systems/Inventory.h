//
//  Inventory.h
//  TeaParty
//
//  Created by Franz on 28/04/15.
//
//

#ifndef _System_Inventory_h
#define _System_Inventory_h

#include <Polycode.h>

#include <aunteater/System.h>
#include <aunteater/Node.h>
#include <aunteater/Engine.h>

namespace TeaParty { namespace System {
class Inventory : public aunteater::System
{
public:
	Inventory()
	{}
	virtual void addedToEngine(aunteater::Engine &aEngine);
	virtual void update(double time);

public:
	aunteater::Nodes mNodeList;
};
}}

#endif 