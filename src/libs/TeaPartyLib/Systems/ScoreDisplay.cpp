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
        mScene(std::make_unique<Polycode::Scene>(1 /*Polycode::Scene::SCENE_2D*/)),
        mLabel(new Polycode::SceneLabel("", SCORE_SIZE, "sans"))
{
    auto rect = new Polycode::ScenePrimitive(Polycode::ScenePrimitive::TYPE_BOX, 450, 60, 0);
    rect->setColor(0.2, 0.2, 0.3, 0.8);
    mScene->addEntity(rect);

    mLabel->setColorInt(255, 214, 0, 255);
    mScene->addEntity(mLabel.get());

    mScene->getActiveCamera()->setOrthoSize(1280, 1024);
}

void ScoreDisplay::update(double time)
{
    std::ostringstream oss;
    for (auto &scorer : *mScorers)
    {
        oss << "P" << scorer.get<Index>().index << ": " << scorer.get<Score>().score << "    ";
    }
    mLabel->setText(oss.str());
}
