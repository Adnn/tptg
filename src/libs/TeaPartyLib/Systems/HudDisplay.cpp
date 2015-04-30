#include "HudDisplay.h"

#include "../globals.h"

#include "../Components/Image.h"
#include "../Components/Position.h"
#include "../Components/HudItem.h"

#include <aunteater/Engine.h>

using namespace TeaParty;
using namespace System;
using aunteater::ArchetypeTypeSet;
using aunteater::Engine;

class NodeHudRenderable
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodeHudRenderable::gComponentTypes = {
    &typeid(Component::Position),
    &typeid(Component::HudItem)
};

HudDisplay::HudDisplay() :
    mScene(Polycode::Scene::SCENE_2D),
    mInventory()
{
    mScene.getActiveCamera()->setProjectionMode(Polycode::Camera::ORTHO_SIZE_LOCK_WIDTH);
    mScene.getActiveCamera()->setOrthoSize(CAM_WIDTH, 540);
    mScene.rootEntity.addChild(&mInventory);
    mInventory.setPosition(0,-100,0);
	Polycode::CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Polycode::Renderer::TEX_FILTERING_NEAREST);
}

void HudDisplay::addedToEngine(Engine &aEngine)
{
    mHudRenderables = &aEngine.getNodes<NodeHudRenderable>();
    aEngine.registerToNodes<NodeHudRenderable>(&mInventoryObserver);
}

void HudDisplay::update(double aTime)
{
    for (aunteater::Node node : *mHudRenderables)
    {
        auto sceneSprite = node.get<Component::HudItem>().polySprite;
        const Vec2 pos = node.get<Component::Position>().coords - mScene.getActiveCamera()->getPosition2D();
        sceneSprite->setPosition(pos.x,pos.y);
    }
}

void InventoryObserver::addedNode(aunteater::Node &aNode)
{
    auto sceneElem = aNode.get<Component::HudItem>().polySprite;
    mInventoryEntity.addChild(sceneElem.get());
    const Vec2 pos = aNode.get<Component::Position>().coords;
    sceneElem->setPosition(pos.x, pos.y);
}

void InventoryObserver::removedNode(aunteater::Node &aNode)
{
    /// \todo
}