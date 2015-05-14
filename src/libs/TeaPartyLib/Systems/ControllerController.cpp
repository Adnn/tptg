#include "ControllerController.h"

#include "../Components/Controller.h"
#include "../Components/ActionController.h"

#include <Polycode.h>

using namespace aunteater;
using namespace TeaParty;
using namespace System;

class NodeControllerActionController
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodeControllerActionController::gComponentTypes =
    { &typeid(TeaParty::Component::Controller),
      &typeid(TeaParty::Component::ActionController) };

ControllerController::ControllerController()
{
}

void ControllerController::addedToEngine(aunteater::Engine &aEngine)
{
    mControllerActionControllers = &aEngine.getNodes<NodeControllerActionController>();
}

void axisUpdate(Polycode::JoystickInfo *controller,
	TeaParty::Component::input_state &aPosButton,
	TeaParty::Component::input_state &aNegButton,
	int index)
{
	if(controller->joystickAxisState[index] > 0.2)
	{
		aPosButton = isDown(aPosButton) ?
                  TeaParty::Component::input_state::BUTTON_DOWN : TeaParty::Component::input_state::BUTTON_FALLING_EDGE;
	}
	else
	{
		aPosButton = isUp(aPosButton) ?
			TeaParty::Component::input_state::BUTTON_UP : TeaParty::Component::input_state::BUTTON_RISING_EDGE;
	}
	if(controller->joystickAxisState[index] < -0.2)
	{
		aNegButton = isDown(aNegButton) ?
                  TeaParty::Component::input_state::BUTTON_DOWN : TeaParty::Component::input_state::BUTTON_FALLING_EDGE;
	}
	else
	{
		aNegButton = isUp(aNegButton) ?
			TeaParty::Component::input_state::BUTTON_UP : TeaParty::Component::input_state::BUTTON_RISING_EDGE;
	}
}


void buttonUpdate(Polycode::JoystickInfo *controller,
                  TeaParty::Component::input_state &aButton, int index)
{
    if(controller->joystickButtonState[index])
    {
        aButton = isDown(aButton) ?
                  TeaParty::Component::input_state::BUTTON_DOWN : TeaParty::Component::input_state::BUTTON_FALLING_EDGE;
    }
    else
    {
        aButton = isUp(aButton) ?
                  TeaParty::Component::input_state::BUTTON_UP : TeaParty::Component::input_state::BUTTON_RISING_EDGE;
    }
}

void ControllerController::update(double time)
{
    for (auto & controllerActionCtrl : *mControllerActionControllers)
    {
        Component::ActionController & actionController =
            controllerActionCtrl.get<Component::ActionController>();
        Component::Controller &controller = controllerActionCtrl.get<Component::Controller>();

        axisUpdate(controller.mJoystickInfo,
        	actionController.up,
        	actionController.down,
        	1);
        axisUpdate(controller.mJoystickInfo,
        	actionController.right,
        	actionController.left,
        	0);
        buttonUpdate(controller.mJoystickInfo, actionController.buttonAction, 0);
        buttonUpdate(controller.mJoystickInfo, actionController.buttonA, 1);
        buttonUpdate(controller.mJoystickInfo, actionController.buttonZ, 2);
        buttonUpdate(controller.mJoystickInfo, actionController.buttonT, 3);
    }
}