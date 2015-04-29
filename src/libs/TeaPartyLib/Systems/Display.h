//
//  Display.h
//
//  Created by Adrien David.
//
//

#ifndef System_Display_h
#define System_Display_h

#include <Polycode.h>

#include <aunteater/System.h>
#include <aunteater/Family.h>

namespace TeaParty { namespace System {

class ImageObserver : public aunteater::FamilyObserver
{
public:
    ImageObserver(Polycode::Entity &aRoot) :
            mSimulationRoot(&aRoot)
    {}

    virtual void addedNode(aunteater::Node &aNode) override;
    virtual void removedNode(aunteater::Node &aNode) override;
    
private:
    Polycode::Entity *mSimulationRoot;
};

class CameraObserver : public aunteater::FamilyObserver
{
public:
    CameraObserver(Polycode::Entity &aRoot) :
            mSimulationRoot(&aRoot)
    {}

    virtual void addedNode(aunteater::Node &aNode) override;
    virtual void removedNode(aunteater::Node &aNode) override;
    
private:
    Polycode::Entity *mSimulationRoot;
};

class Display : public aunteater::System, public aunteater::FamilyObserver
{
public:
    Display();

    // Take care of the NodeRenderable
    virtual void addedToEngine(aunteater::Engine &aEngine) override;
    virtual void update(double aTime) override;

    virtual void addedNode(aunteater::Node &aNode) override;
    virtual void removedNode(aunteater::Node &aNode) override;
    
private:
    aunteater::Nodes mRenderables;
    aunteater::Nodes mCameras;
    Polycode::Entity mSimulationRoot; // The actual scene is stored in the camera, to customize clipping, etc..
                                      // but the content of the simulation is common to all cameras : this data member
    ImageObserver mImageObserver = ImageObserver(mSimulationRoot);
    CameraObserver mCameraObserver = CameraObserver(mSimulationRoot);
};

}} // namespace TeaParty::System

#endif
