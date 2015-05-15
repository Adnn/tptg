#include "ScoreDisplay.h"

#include "Utilities.h"

#include "../Components/Index.h"
#include "../Components/Score.h"

#include "../globals.h"

using namespace TeaParty;
using namespace System;
using namespace Component;


class NodeScorer
{
public:
    static const aunteater::ArchetypeTypeSet gComponentTypes;
};

const aunteater::ArchetypeTypeSet NodeScorer::gComponentTypes = {
    &typeid(Component::Score),
    &typeid(Component::Index)
};


void ScoreDisplay::addedToEngine(aunteater::Engine &aEngine)
{
    mScorers = &aEngine.getNodes<NodeScorer>();
}

ScoreDisplay::ScoreDisplay() :
        mScene(std::make_unique<Polycode::Scene>(1 /*Polycode::Scene::SCENE_2D*/))
{
    auto label = new Polycode::SceneLabel("TEXXXXT", 1, "sans.ttf");
    label->setColorInt(255, 100, 0, 255);
    mScene->addEntity(label);
    //mScene->addEntity(new Polycode::SceneImage("target.png"));
    mScene->getActiveCamera()->setOrthoSize(640, 480);
}

void ScoreDisplay::update(double time)
{
    for (auto &scorer : *mScorers)
    {

    }
}
