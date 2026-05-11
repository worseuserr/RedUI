#include <string>
#include "RedUI/Graphics/Sprite.h"

using namespace RedUI;

Sprite::Sprite(const std::string &textureDict, const std::string &textureName, const float heading)
{
	TextureDict = textureDict;
	TextureName = textureName;
	Heading = heading;
}
