#include "RedUI/UIState.h"

using namespace RedUI;

bool								UIState::IsUpdating = false;
bool								UIState::CursorEnabled = false;
bool								UIState::MouseInputsDisabled = false;
float								UIState::ScreenVerticalRatio = 1.0f;
std::vector<UIObjectOwner>			UIState::RootObjects = {};
std::vector<AnimationOwner>			UIState::Animations = {};
std::vector<UIObject *>				UIState::QueuedObjectDeletions = {};
std::map<UIObject *, UIObject *>	UIState::QueuedHierarchyChanges = {};
std::vector<AnimationOwner *>		UIState::QueuedFinishedAnimations = {};
