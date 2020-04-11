#include <string>
#pragma once

class TextureResource
{
public:
	std::string minFilter, magFilter, wrapS, wrapT;
	std::string path;
	std::string type;
	int texture_type;
	int textureWidth = 0, textureHeight = 0, textureBpp = 0;
};
