//
//  Index.h
//  tptg
//
//  Created by Franz on 14/05/15.
//
//

#ifndef _Component_Index_
#define _Component_Index_

#include <Polycode.h>
#include <aunteater/Component.h>

namespace TeaParty { namespace Component {

class Index : public aunteater::Component
{
public:
	Index(int aId, aunteater::weak_entity counter):
		index(aId),
        ballsCounter(counter)
	{}

	const int index;
    aunteater::weak_entity ballsCounter;

private:
    COMP_CLONE(Index)
};

}} // namespace TeaParty::Component

#endif