#include "Input.h"

#include "../Components/Speed.h"
#include "../Components/Keyboard.h"
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
    { &typeid(TeaParty::Component::Keyboard),
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
	Polycode::CoreInput * keyboard = Polycode::CoreServices::getInstance()->getCore()->getInput();
	for (aunteater::Node node : *mNodeList)
	{
		auto speed = &node.get<Component::Speed>();
		auto animation = &node.get<Component::AnimationList>();
		if (animation->mCounterToCancelability <= 0)
		{
			if (keyboard->getKeyState(Polycode::KEY_LEFT))
			{
				speed->vX = -BASE_SPEED;
				animation->mAnimationToPlay = "run_left";
			}
			else if (keyboard->getKeyState(Polycode::KEY_RIGHT))
			{
				speed->vX = BASE_SPEED;
				animation->mAnimationToPlay = "run_right";
			}
			else
			{
				//speed->vX = 0;
				animation->mAnimationToPlay = "idle";
			}
		}
	}
}