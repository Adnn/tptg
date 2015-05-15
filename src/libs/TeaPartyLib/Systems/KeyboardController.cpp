#include "KeyboardController.h"

#include "../Components/Keyboard.h"
#include "../Components/ActionController.h"

#include <Polycode.h>

using namespace aunteater;
using namespace TeaParty;
using namespace System;

class NodeKeyboardActionController
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodeKeyboardActionController::gComponentTypes =
    { &typeid(TeaParty::Component::Keyboard),
      &typeid(TeaParty::Component::ActionController) };

KeyboardController::KeyboardController()
{
}

void KeyboardController::addedToEngine(aunteater::Engine &aEngine)
{
    mKeyboardActionControllers = &aEngine.getNodes<NodeKeyboardActionController>();
}

void buttonUpdate(Polycode::CoreInput *aKeyboard,
                  TeaParty::Component::input_state &aButton, Polycode::PolyKEY aKey)
{
    if(aKeyboard->getKeyState(aKey))
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

void KeyboardController::update(double time)
{
    Polycode::CoreInput * keyboard = Polycode::CoreServices::getInstance()->getCore()->getInput();

    for (auto & keyboardActionCtrl : *mKeyboardActionControllers)
    {
        Component::ActionController & actionController =
            keyboardActionCtrl.get<Component::ActionController>();

        const Component::Keyboard &kb = keyboardActionCtrl.get<Component::Keyboard>();

        buttonUpdate(keyboard, actionController.up, Polycode::KEY_UP);
        buttonUpdate(keyboard, actionController.down, Polycode::KEY_DOWN);
        buttonUpdate(keyboard, actionController.left, kb.left);
        buttonUpdate(keyboard, actionController.right, kb.right);
        buttonUpdate(keyboard, actionController.buttonAction, Polycode::KEY_SPACE);
        buttonUpdate(keyboard, actionController.buttonA, kb.action);
        buttonUpdate(keyboard, actionController.buttonZ, Polycode::KEY_z);
        buttonUpdate(keyboard, actionController.buttonT, Polycode::KEY_t);
    }
}