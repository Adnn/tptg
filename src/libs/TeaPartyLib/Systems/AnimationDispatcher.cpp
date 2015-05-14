#include "AnimationDispatcher.h"

#include "../Components/Sprite.h"
#include "../Components/AnimationList.h"
#include "../Animation.h"

#include <aunteater/Engine.h>

using namespace TeaParty;
using namespace System;
using aunteater::ArchetypeTypeSet;
using aunteater::Engine;

class NodeAnimationable
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodeAnimationable::gComponentTypes = {
    &typeid(Component::AnimationList),
    &typeid(Component::Sprite)
};

void AnimationDispatcher::addedToEngine(Engine &aEngine)
{
    mAnimationables = &aEngine.getNodes<NodeAnimationable>();
}

void AnimationDispatcher::update(double time) {
	for(aunteater::Node node : *mAnimationables)
	{
		auto animationList = &node.get<Component::AnimationList>();
		auto sprite = node.get<Component::Sprite>().polySprite;

		if (animationList->mCounterToCancelability > 0) {
			animationList->mCounterToCancelability--;
		}

		if (!animationList->mAnimationToPlay.empty() &&
			animationList->mAnimationToPlay != animationList->mCurrentlyPlaying &&
			animationList->mCounterToCancelability <= 0 &&
			animationList->mAnimationList.find(animationList->mAnimationToPlay) != animationList->mAnimationList.end())
		{
			sprite->setSpriteStateByName(animationList->mAnimationToPlay,0,false);
			Structure::Animation animationStruct = animationList->mAnimationList.at(animationList->mAnimationToPlay);
			animationList->mCounterToCancelability = animationStruct.mNonCancelableFrame*(60.0f / animationStruct.mFps);
			animationList->mCurrentlyPlaying = animationList->mAnimationToPlay;
			animationList->mAnimationToPlay = "";
		}
	}
}