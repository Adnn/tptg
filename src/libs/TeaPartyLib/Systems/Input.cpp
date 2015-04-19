#include "Input.h"

#include "../Components/Speed.h"
#include "../Components/Keyboard.h"

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
      &typeid(TeaParty::Component::Speed) };

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
		if (keyboard->getKeyState(Polycode::KEY_LEFT))
		{
			speed->vX = -BASE_SPEED;
		}
		else if (keyboard->getKeyState(Polycode::KEY_RIGHT))
		{
			speed->vX = BASE_SPEED;
		}
		else
		{
			speed->vX = 0;
		}
	}
}