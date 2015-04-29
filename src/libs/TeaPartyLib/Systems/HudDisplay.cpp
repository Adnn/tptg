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
    mScene(Polycode::Scene::SCENE_2D)
{
    mScene.getActiveCamera()->setProjectionMode(Polycode::Camera::ORTHO_SIZE_LOCK_WIDTH);
    mScene.getActiveCamera()->setOrthoSize(CAM_WIDTH, 540);
	Polycode::CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Polycode::Renderer::TEX_FILTERING_NEAREST);
}

void HudDisplay::addedToEngine(Engine &aEngine)
{
    mHudRenderables = &aEngine.getNodes<NodeHudRenderable>();
    aEngine.registerToNodes<NodeHudRenderable>(this);
}

void HudDisplay::update(double aTime)
{
    for (aunteater::Node node : *mHudRenderables)
    {
        auto sceneSprite = node.get<Component::HudItem>().polyImage;
        const Vec2 pos = node.get<Component::Position>().coords - mScene.getActiveCamera()->getPosition2D();
        sceneSprite->setPosition(pos.x,pos.y);
    }
}

void HudDisplay::addedNode(aunteater::Node &aNode)
{
    auto sceneElem = aNode.get<Component::HudItem>().polyImage;
    mScene.addChild(sceneElem.get());
    const Vec2 pos = aNode.get<Component::Position>().coords;
    sceneElem->setPosition(pos.x, pos.y);
}

void HudDisplay::removedNode(aunteater::Node &aNode)
{
    /// \todo
}