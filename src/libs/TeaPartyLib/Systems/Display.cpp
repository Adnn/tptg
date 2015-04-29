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
//    mScene.getActiveCamera()->setProjectionMode(Polycode::Camera::ORTHO_SIZE_LOCK_WIDTH);
    mScene.getActiveCamera()->setProjectionMode(Polycode::Camera::ORTHO_SIZE_MANUAL);

    // The camera will map the dimensions given here (in pixels) to the total size of the window.
    mScene.getActiveCamera()->setOrthoSize(CAM_WIDTH*VP_COLS, CAM_HEIGHT*VP_ROWS);

    // The only way we found to simulate viewports on the window.
    mScene.rootEntity.enableScissor = true;
    // Creates the top-left viewport
    mScene.rootEntity.scissorBox = {0, 0, X_RES/VP_COLS, Y_RES/VP_ROWS};

    // And moves the whole scene to be aligned in the top left "viewport"
    mScene.rootEntity.setPositionY(Y_ROOM/VP_ROWS);
    mScene.rootEntity.setPositionX(-X_ROOM/VP_COLS);
    
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
    sceneSprite->setSpriteByName("player");
    const Vec2 pos = aNode.get<Component::Position>().coords;
    sceneSprite->setPosition(pos.x, pos.y);
    sceneSprite->setScale(1.2,1.2);
}

void Display::removedNode(aunteater::Node &aNode)
{
    /// \todo
}