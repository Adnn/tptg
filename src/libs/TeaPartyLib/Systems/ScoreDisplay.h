//
//  ScoreDisplay.h
//  aunteater
//

#ifndef __aunteater__SytemScoreDisplay__
#define __aunteater__SytemScoreDisplay__

#include <aunteater/System.h>
#include <aunteater/Engine.h>
#include <aunteater/Node.h>

#include <PolyScene.h>
#include <PolySceneLabel.h>

namespace TeaParty { namespace System {

class ScoreDisplay : public aunteater::System
{
public:
    ScoreDisplay();

    virtual void addedToEngine(aunteater::Engine &aEngine);
    virtual void update(double time);

public:
    aunteater::Nodes mScorers;
    std::unique_ptr<Polycode::Scene> mScene;
    std::unique_ptr<Polycode::SceneLabel> mLabel;
};

}} //namespace TeaParty::System

#endif /* defined(__aunteater__SytemScoreDisplay) */
