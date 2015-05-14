//
//  Controller.h
//  tptg
//
//  Created by Franz on 14/05/15.
//
//

#ifndef _Component_Controller_
#define _Component_Controller_

#include <Polycode.h>
#include <aunteater/Component.h>

namespace TeaParty { namespace Component {
class Controller : public aunteater::Component
{
public:
	Controller(Polycode::JoystickInfo * aJoystickInfo)
	{
		mJoystickInfo = aJoystickInfo;
	}

	Polycode::JoystickInfo *mJoystickInfo;
private:
    COMP_CLONE(Controller)
};
}}
#endif 