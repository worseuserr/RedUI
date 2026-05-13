#pragma once
#include <map>
#include <vector>
#include "UIObject.h"
#include "Graphics/Animation.h"
#include "Input/Mouse.h"

namespace RedUI
{
	struct	FocusState
	{
		unsigned int	InteractionRefs;
		unsigned int	CursorRefs;
		unsigned int	InputDisabledRefs;
	};

	// Contains all UI objects and states.
	class	UIState
	{
	public:
		static FocusState						Focus;
		static bool								UpdateLoopEnabled;
		static bool								IsUpdating;
		// Tracks whether mouse cursor should be enabled.
		static bool								CursorEnabled;
		// Tracks whether ui objects can interact with the mouse.
		static bool								InteractionEnabled;
		// Tracks whether mouse inputs should be disabled.
		static bool								MouseInputsDisabled;
		// Ratio for performing uniform scaling. {Scale.X = 1, Scale.Y = 1 * ScreenVerticalRatio}
		static float							ScreenVerticalRatio;
		// Root UI objects. All other objects are children.
		static std::vector<UIObjectOwner>		RootObjects;
		static std::vector<AnimationOwner>		Animations;
		// Queued hierarchy changes if they were done during updating. <oldParent, newParent>
		// Could move these into a QueuedState or similar struct.
		static std::vector<UIObject *>			QueuedObjectDeletions;
		static std::map<UIObject *, UIObject *>	QueuedHierarchyChanges;
		static std::vector<AnimationOwner *>	QueuedFinishedAnimations;
	};
}

