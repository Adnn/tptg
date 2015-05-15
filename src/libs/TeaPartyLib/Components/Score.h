//
//  Score.h
//  tptg
//
//  Created by Franz on 14/05/15.
//
//

#ifndef _Component_Score_
#define _Component_Score_

#include <Polycode.h>
#include <aunteater/Component.h>

namespace TeaParty { namespace Component {

class Score : public aunteater::Component
{
public:
	Score(int aVal=0):
		score(aVal)
	{}

	int score;

private:
    COMP_CLONE(Score)
};

}} // namespace TeaParty::Component

#endif
