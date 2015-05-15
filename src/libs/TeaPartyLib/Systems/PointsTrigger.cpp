#include "PointsTrigger.h"

#include "Utilities.h"

#include "../Components/BallsPoint.h"
#include "../Components/CallbackNoParam.h"
#include "../Components/PointsTarget.h"

#include <aunteater/globals.h>

using namespace TeaParty;
using namespace System;
using namespace Component;

class NodePointTrigger
{
public:
    static const aunteater::ArchetypeTypeSet gComponentTypes;
};

const aunteater::ArchetypeTypeSet NodePointTrigger::gComponentTypes = {
    &typeid(TeaParty::Component::CallbackNoParam),
    &typeid(TeaParty::Component::BallsPoint),
    &typeid(TeaParty::Component::PointsTarget)
};

void PointsTrigger::addedToEngine(aunteater::Engine &aEngine)
{
    mPointsTriggers = &aEngine.getNodes<NodePointTrigger>();
}

void PointsTrigger::update(double time)
{
    //static int i = 0;
    std::vector<CallbackNoParam::Function> triggered;
    for (aunteater::Node &trigger : *mPointsTriggers)
    {
        //std::cout << "F:" << i << "    " << trigger.get<BallsPoint>().point << "   " << trigger.get<PointsTarget>().target << std::endl;
        if(trigger.get<BallsPoint>().point >= trigger.get<PointsTarget>().target)
        {
            triggered.push_back(trigger.get<CallbackNoParam>().callback);
        }
    }

    // Deffered in order not to invalidate the loop iterators
    std::for_each(triggered.begin(), triggered.end(), [](CallbackNoParam::Function &aFunc){aFunc();});

    //i++;
}
