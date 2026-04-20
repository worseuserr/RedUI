#include "RedUI/Input/Key.h"

using namespace RedUI;

bool Input::IsKeyDown(Key key)
{
	return ((GetAsyncKeyState(static_cast<SHORT>(key)) & KEY_PRESSED_BIT) != 0);
}
