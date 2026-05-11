#pragma once

namespace RedUI
{
	class Sprite
	{
	public:
		std::string	TextureDict;
		std::string	TextureName;
		float		Heading;

		Sprite(const std::string &textureDict, const std::string &textureName, float heading = 0.0f);
	};
}
