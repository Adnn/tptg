//
//  BallsPoint.h
//  tptg
//
//  Created by Franz on 14/05/15.
//
//

#ifndef _Component_BallsPoint_
#define _Component_BallsPoint_

#include <Polycode.h>
#include <aunteater/Component.h>

namespace TeaParty { namespace Component {

class BallsPoint : public aunteater::Component
{
public:
	BallsPoint(int aPoint = 0):
		point(aPoint)
	{
	}

	int point;

private:
    COMP_CLONE(BallsPoint)
};

}} // namespace TeaParty::Component

#endif 