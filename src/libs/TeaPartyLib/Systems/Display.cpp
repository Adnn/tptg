#include "Display.h"

#include "../Components/Position.h"
#include "../Components/Sprite.h"

#include <aunteater/Engine.h>

using namespace TeaParty;
using namespace System;
using aunteater::ArchetypeTypeSet;
using aunteater::Engine;

class NodeRenderable
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodeRenderable::gComponentTypes = {
    &typeid(Component::Position),
    &typeid(Component::Sprite)
};

Display::Display() :
    mScene(Polycode::Scene::SCENE_2D)
{
    mScene.getActiveCamera()->setOrthoSize(640, 480);
	Polycode::CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Polycode::Renderer::TEX_FILTERING_NEAREST);
}

void Display::addedToEngine(Engine &aEngine)
{
    mRenderables = &aEngine.getNodes<NodeRenderable>();
    aEngine.registerToNodes<NodeRenderable>(this);
}

void Display::update(double aTime)
{

}

void Display::addedNode(aunteater::Node &aNode)
{
    auto sceneSprite = aNode.get<Component::Sprite>().polySprite;
    mScene.addChild(sceneSprite.get());
    sceneSprite->setSpriteByName("Explosion");
    sceneSprite->setSpriteStateByName("default", 0, false);
    const Vec2 pos = aNode.get<Component::Position>().coords;
    sceneSprite->setPosition(pos.x, pos.y);
}

void Display::removedNode(aunteater::Node &aNode)
{
    /// \todo
}