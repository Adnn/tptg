#ifndef TeaParty_Animation_h
#define TeaParty_Animation_h

#include <string>

namespace TeaParty { namespace Structure {
struct Animation {
	Animation(std::string aName, int aNonCancelableFrame, float aFps) :
		mName(aName),
		mNonCancelableFrame(aNonCancelableFrame),
		mFps(aFps)
	{}
	const std::string mName;
	const int mNonCancelableFrame;
	const float mFps;
};

}}
#endif