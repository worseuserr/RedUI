#include "RedUI/UIState.h"

using namespace RedUI;

bool								UIState::IsUpdating = false;
bool								UIState::CursorEnabled = false;
float								UIState::ScreenVerticalRatio = 1.0f;
std::vector<UIObjectOwner>			UIState::RootObjects = {};
std::vector<AnimationOwner>			UIState::Animations = {};
std::map<UIObject *, UIObject *>	UIState::QueuedHierarchyChanges = {};
std::vector<AnimationOwner *>		UIState::QueuedFinishedAnimations = {};
