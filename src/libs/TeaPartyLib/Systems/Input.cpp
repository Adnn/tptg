#include "Input.h"

#include "../Components/Speed.h"
#include "../Components/ActionController.h"
#include "../Components/AnimationList.h"

#include <aunteater/Engine.h>

using namespace TeaParty;
using namespace System;
using aunteater::ArchetypeTypeSet;
class NodeControl
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodeControl::gComponentTypes =
    { &typeid(TeaParty::Component::ActionController),
      &typeid(TeaParty::Component::Speed),
      &typeid(TeaParty::Component::AnimationList) };

Input::Input()
{
}

void Input::addedToEngine(aunteater::Engine &aEngine)
{
	mNodeList = &aEngine.getNodes<NodeControl>();
}

void Input::update(double time)
{
	for (aunteater::Node node : *mNodeList)
	{
		auto speed = &node.get<Component::Speed>();
		auto animation = &node.get<Component::AnimationList>();
		auto actionController = &node.get<Component::ActionController>();
		if (animation->mCounterToCancelability <= 0)
		{
			if (isDown(actionController->left))
			{
				speed->vX = -BASE_SPEED;
				animation->mAnimationToPlay = "run_left";
			}
			else if (isDown(actionController->right))
			{
				speed->vX = BASE_SPEED;
				animation->mAnimationToPlay = "run_right";
			}
			else
			{
				if (speed->vX > 0)
				{
					animation->mAnimationToPlay = "idle_right";
				}
				else
				{
					animation->mAnimationToPlay = "idle_left";
				}
					
			}
		}
	}
}