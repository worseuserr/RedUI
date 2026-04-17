#pragma once

#include <map>
#include <vector>
#include "UIObject.h"
#include "Animation.h"

namespace RedUI
{
	// Contains all UI objects and states.
	class	UIState
	{
	public:
		static bool								IsUpdating;
		// Root UI objects. All other objects are children.
		static std::vector<UIObjectOwner>		RootObjects;
		static std::vector<AnimationOwner>		Animations;
		// Queued hierarchy changes if they were done during updating. <oldParent, newParent>
		static std::map<UIObject *, UIObject *>	QueuedHierarchyChanges;
		static std::vector<AnimationOwner *>	QueuedFinishedAnimations;
	};

	inline bool								UIState::IsUpdating = false;
	inline std::vector<UIObjectOwner>		UIState::RootObjects = {};
	inline std::vector<AnimationOwner>		UIState::Animations = {};
	inline std::map<UIObject *, UIObject *>	UIState::QueuedHierarchyChanges = {};
	inline std::vector<AnimationOwner *>	UIState::QueuedFinishedAnimations = {};
}

