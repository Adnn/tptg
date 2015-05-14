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
    auto zIndex = aNode.get<Component::Position>().z;
    mSimulationRoot->getChildAtIndex(zIndex)->addChild(sceneElem.get());
    const Vec2 pos = aNode.get<Component::Position>().coords;
    sceneElem->setPosition(pos.x, pos.y);
}

void ImageObserver::removedNode(aunteater::Node &aNode)
{
    /// \todo
}

//void CameraObserver::addedNode(aunteater::Node &aNode)
//{
//    // All cameras clipping scene share the same scene graph : it is assigned here
//    auto clippedScene = aNode.get<Component::ClippedScene>().polyScene;
//    clippedScene->addChild(mSimulationRoot);
//}
//
//void CameraObserver::removedNode(aunteater::Node &aNode)
//{}


Display::Display()
{
    Polycode::CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Polycode::Renderer::TEX_FILTERING_NEAREST);
    // Add layers
    for (int layerId = 0; layerId != LAYERS; ++layerId)
    {
        mSimulationRoot.addChild(new Polycode::Entity);
    }
}

void Display::addedToEngine(Engine &aEngine)
{
    mRenderables = &aEngine.getNodes<NodeRenderable>();
    mCameras = &aEngine.getNodes<NodeCamera>();
    aEngine.registerToNodes<NodeRenderable>(this);
    aEngine.registerToNodes<NodeImage>(&mImageObserver);
    //aEngine.registerToNodes<NodeCamera>(&mCameraObserver);
}

void Display::update(double aTime)
{
    for (aunteater::Node node : *mRenderables)
    {
        // Moves the sprite in the 2D plane
        auto sceneSprite = node.get<Component::Sprite>().polySprite;
        const Vec2 pos = node.get<Component::Position>().coords;
        sceneSprite->setPosition(pos.x,pos.y);

        // Make sure the sprite ends up in the right layer (corresponding to its Z index)
        const int z = node.get<Component::Position>().z;
        int prevZ = mSpriteToZ.at(sceneSprite.get());
        if(prevZ != z)
        {
            mSimulationRoot.getChildAtIndex(prevZ)->removeChild(sceneSprite.get());
            mSimulationRoot.getChildAtIndex(z)->addChild(sceneSprite.get());
            mSpriteToZ[sceneSprite.get()] = z;
        }
    }

    for (aunteater::Node node : *mCameras)
    {
        // Moves the camera in the 2D plane
        const Vec2 pos = node.get<Component::Position>().coords;
        auto scene = node.get<Component::ClippedScene>().polyScene;
        scene->getActiveCamera()->setPosition(pos.x, pos.y);

        // Assign the layer corresponding to the Z index of the camera
        auto clippedScene = node.get<Component::ClippedScene>().polyScene;
        auto zIndex = node.get<Component::Position>().z;
        clippedScene->removeEntity(clippedScene->rootEntity.getChildAtIndex(0)); // Clear
        clippedScene->addChild(mSimulationRoot.getChildAtIndex(zIndex));
    }
}

void Display::addedNode(aunteater::Node &aNode)
{
    auto zIndex = aNode.get<Component::Position>().z;
    auto sceneSprite = aNode.get<Component::Sprite>().polySprite;
    mSimulationRoot.getChildAtIndex(zIndex)->addChild(sceneSprite.get());
    mSpriteToZ.insert({sceneSprite.get(), zIndex});

    sceneSprite->setSpriteByName("player");
    const Vec2 pos = aNode.get<Component::Position>().coords;
    sceneSprite->setPosition(pos.x, pos.y);
    sceneSprite->setScale(1.2,1.2);
}

void Display::removedNode(aunteater::Node &aNode)
{
    /// \todo
}