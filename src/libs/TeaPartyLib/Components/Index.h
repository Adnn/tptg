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
	Index(int aId):
		index(aId)
	{}

	const int index;

private:
    COMP_CLONE(Index)
};

}} // namespace TeaParty::Component

#endif