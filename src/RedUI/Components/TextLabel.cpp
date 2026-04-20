#include "RedUI/Components/TextLabel.h"
#include "Sdk/natives.h"

void RedUI::TextLabel::Draw()
{
	UI::SET_TEXT_SCALE(0, TextScale);
	UI::SET_TEXT_COLOR_RGBA(Color.R, Color.G, Color.B, Alpha);
	UI::SET_TEXT_CENTRE(false);
	UI::SET_TEXT_DROPSHADOW(Dropshadow.Distance, Dropshadow.Color.R, Dropshadow.Color.G, Dropshadow.Color.B, Dropshadow.Alpha);
	UI::DRAW_TEXT(MISC::CREATE_STRING(10, "LITERAL_STRING", const_cast<char *>(Text.c_str())), WorldPosition.X, WorldPosition.Y);
}
