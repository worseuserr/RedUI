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
		// Root UI objects. All parented objects are children.
		static std::vector<UIObject *>			Objects;
		static std::vector<Animation *>			Animations;
		// Queued hierarchy changes if they were done during updating. <oldParent, newParent>
		static std::map<UIObject *, UIObject *>	QueuedHierarchyChanges;
	};

	inline bool								UIState::IsUpdating = false;
	inline std::vector<UIObject *>			UIState::Objects = {};
	inline std::vector<Animation *>			UIState::Animations = {};
	inline std::map<UIObject *, UIObject *>	UIState::QueuedHierarchyChanges = {};
}

