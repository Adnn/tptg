//
//  ComponentPosition.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__ComponentKeyboard__
#define __aunteater__ComponentKeyboard__

#include <Polycode.h>
#include <aunteater/Component.h>
#include <memory>

namespace TeaParty { namespace Component {
class Keyboard : public aunteater::Component
{
public:
	Keyboard(Polycode::PolyKEY aL = Polycode::KEY_LEFT, Polycode::PolyKEY aR = Polycode::KEY_RIGHT,
             Polycode::PolyKEY aA = Polycode::KEY_a) :
            left(aL),
            right(aR),
            action(aA)
	{}

    Polycode::PolyKEY left;
    Polycode::PolyKEY right;
    Polycode::PolyKEY action;

private:
    COMP_CLONE(Keyboard)
};
}}
#endif /* defined(__aunteater__ComponentKeyboard__) */