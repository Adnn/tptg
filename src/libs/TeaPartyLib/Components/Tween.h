//
//  Tween.h
//
//  Created by Franz.
//
//

#ifndef Component_Tween_h
#define Component_Tween_h

#include "../Vec2.h"
#include <aunteater/Component.h>

#include <vector>
 
namespace TeaParty { namespace Component {

struct Tween : public aunteater::Component
{
    Tween(Vec2 aDest, Vec2 aOrigin, float aTime)
    {
    	mIndex = 0;
    	
    	for(int i = 0; i < aTime*60; i++)
    	{
			mTweenTable.push_back((aOrigin - aDest) / (aTime*60.0));
    	}
    }

    std::vector<Vec2> mTweenTable;
    int mIndex;

private:
    COMP_CLONE(Tween)
};

}} // namespace TeaParty::Component

#endif