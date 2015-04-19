#ifndef _TeaParty_Component_Animation_h
#define _TeaParty_Component_Animation_h

#include "../Animation.h"

#include <aunteater/Component.h>
#include <map>
#include <string>

namespace TeaParty { namespace Component {
class AnimationList : public aunteater::Component
{
public:
	AnimationList(std::string aDefaultAnim) :
		mCounterToCancelability(0),
		mAnimationToPlay(aDefaultAnim)
	{}

	void addAnimation(TeaParty::Structure::Animation &aAnimation)
	{
		mAnimationList.insert(std::pair<std::string,TeaParty::Structure::Animation>(aAnimation.mName,aAnimation));
	}

	std::string mAnimationToPlay;
	std::map<std::string,TeaParty::Structure::Animation> mAnimationList;
	float mCounterToCancelability;
	std::string mCurrentlyPlaying;
private:
	COMP_CLONE(AnimationList)
};
}}
#endif  // #ifdef