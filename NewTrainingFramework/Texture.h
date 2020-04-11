#pragma once
#include "TextureResource.h"

class Texture
{
public:
	TextureResource* tr; //structura pe baza careia e incarcata textura
	unsigned int textureId; //generat prin glGenTextures()
	char* pixelArray;

	Texture();
	~Texture();
	void Load();
};
