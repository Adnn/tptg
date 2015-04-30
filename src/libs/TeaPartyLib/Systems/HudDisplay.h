//
//  HudDisplay.h
//
//  Created by Franz.
//
//

#ifndef System_HudDisplay_h
#define System_HudDisplay_h

#include <Polycode.h>

#include <aunteater/System.h>
#include <aunteater/Family.h>

namespace TeaParty { namespace System {

class InventoryObserver : public aunteater::FamilyObserver
{
public:
    InventoryObserver(Polycode::Entity &aInventoryEntity) :
            mInventoryEntity(aInventoryEntity)
    {}

    virtual void addedNode(aunteater::Node &aNode) override;
    virtual void removedNode(aunteater::Node &aNode) override;
    
private:
    Polycode::Entity &mInventoryEntity;
};

class HudDisplay : public aunteater::System
{
public:
    HudDisplay();

    virtual void addedToEngine(aunteater::Engine &aEngine) override;
    virtual void update(double aTime) override;
    
private:
    aunteater::Nodes mHudRenderables;
    Polycode::Entity mInventory;
    Polycode::Scene mScene;
	InventoryObserver mInventoryObserver = InventoryObserver(mInventory);
};

}} // namespace TeaParty::System

#endif