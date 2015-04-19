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
	Keyboard()
	{}
private:
    COMP_CLONE(Keyboard)
};
}}
#endif /* defined(__aunteater__ComponentKeyboard__) */