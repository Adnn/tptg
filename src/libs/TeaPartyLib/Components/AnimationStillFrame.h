//
//  AnimationStillFrame.h
//  tptg
//
//  Created by Franz on 14/05/15.
//
//

#ifndef _Component_AnimationStillFrame_
#define _Component_AnimationStillFrame_

#include <Polycode.h>
#include <aunteater/Component.h>

namespace TeaParty { namespace Component {
class AnimationStillFrame : public aunteater::Component
{
public:
	AnimationStillFrame():
		requestFrame(0)
	{
	}

	int requestFrame;
private:
    COMP_CLONE(AnimationStillFrame)
};
}}
#endif 