#include "RedUI/Graphics/Animation.h"

using namespace RedUI;

std::vector<AnimationOwner *>	IAnimation::FinishedQueue = {};
std::vector<AnimationOwner>		IAnimation::All = {};

void IAnimation::Tick()
{
	for (AnimationOwner &anim : All)
		if (anim->Update()) // Queue animation for removal if finished.
			FinishedQueue.push_back(&anim);
}

void IAnimation::TickQueue()
{
	for (const AnimationOwner *anim : FinishedQueue)
		std::erase(All, *anim);
	FinishedQueue.clear();
}

void IAnimation::Register(AnimationOwner anim)
{
	All.push_back(std::move(anim));
}

