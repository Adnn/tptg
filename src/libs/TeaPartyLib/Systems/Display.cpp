#include "Display.h"

#include "../globals.h"

#include "../Archetypes/NodeCamera.h"

#include "../Components/Image.h"
#include "../Components/Position.h"
#include "../Components/Sprite.h"

#include <aunteater/Engine.h>

using namespace TeaParty;
using namespace Archetype;
using namespace System;
using aunteater::ArchetypeTypeSet;
using aunteater::Engine;

class NodeRenderable
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

class NodeImage
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodeRenderable::gComponentTypes = {
    &typeid(Component::Position),
    &typeid(Component::Sprite)
};

const ArchetypeTypeSet NodeImage::gComponentTypes = {
    &typeid(Component::Position),
    &typeid(Component::Image)
};

void ImageObserver::addedNode(aunteater::Node &aNode)
{
    auto sceneElem = aNode.get<Component::Image>().polyImage;
    mScene.addChild(sceneElem.get());
    const Vec2 pos = aNode.get<Component::Position>().coords;
    sceneElem->setPosition(pos.x, pos.y);
    //sceneElem->setScale(4, 2);
}

void ImageObserver::removedNode(aunteater::Node &aNode)
{
    /// \todo
}

Display::Display() :
    mScene(Polycode::Scene::SCENE_2D)
{
    mScene.getActiveCamera()->setProjectionMode(Polycode::Camera::ORTHO_SIZE_LOCK_WIDTH);
    mScene.getActiveCamera()->setOrthoSize(CAM_WIDTH, 540);
	Polycode::CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Polycode::Renderer::TEX_FILTERING_NEAREST);
}

void Display::addedToEngine(Engine &aEngine)
{
    mRenderables = &aEngine.getNodes<NodeRenderable>();
    mCameras = &aEngine.getNodes<NodeCamera>();
    aEngine.registerToNodes<NodeRenderable>(this);
    aEngine.registerToNodes<NodeImage>(&mImageObserver);
}

void Display::update(double aTime)
{
    for (aunteater::Node node : *mRenderables)
    {
        auto sceneSprite = node.get<Component::Sprite>().polySprite;
        const Vec2 pos = node.get<Component::Position>().coords;
        sceneSprite->setPosition(pos.x,pos.y);
    }

    for (aunteater::Node node : *mCameras)
    {
        const Vec2 pos = node.get<Component::Position>().coords;
        mScene.getActiveCamera()->setPosition(pos.x, pos.y);
    }
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