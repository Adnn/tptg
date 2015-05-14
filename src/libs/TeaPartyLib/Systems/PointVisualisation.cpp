#include "PointVisualisation.h"

#include "../Components/BallsPoint.h"
#include "../Components/AnimationStillFrame.h"

#include <Polycode.h>

using namespace aunteater;
using namespace TeaParty;
using namespace System;

class NodePointCount
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodePointCount::gComponentTypes =
    { &typeid(TeaParty::Component::BallsPoint),
      &typeid(TeaParty::Component::AnimationStillFrame) };

PointVisualisation::PointVisualisation()
{
}

void PointVisualisation::addedToEngine(aunteater::Engine &aEngine)
{
    mPointCount = &aEngine.getNodes<NodePointCount>();
}

void PointVisualisation::update(double time)
{
    for (auto & node : *mPointCount)
    {
    	auto ballsPoint = &node.get<Component::BallsPoint>();
    	auto stillFrame = &node.get<Component::AnimationStillFrame>();

    	stillFrame->requestFrame = (int)ballsPoint->point/MAX_POINT*12;
    }
}