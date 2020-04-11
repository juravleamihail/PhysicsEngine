#include "stdafx.h"
#include "Texture.h"
#include "../Utilities/utilities.h" 

Texture::Texture()
{
}

Texture::~Texture()
{
}

void Texture::Load()
{
	auto a = glGetError();

	if (tr->type == "2d")
		tr->texture_type = GL_TEXTURE_2D;
	else if (tr->type == "cube")
		tr->texture_type = GL_TEXTURE_CUBE_MAP;

	auto c = glGetError();

	this->pixelArray = LoadTGA(tr->path.c_str(), &tr->textureWidth, &tr->textureHeight, &tr->textureBpp);

	glGenTextures(1, &this->textureId);
	glBindTexture(tr->texture_type, this->textureId);

	int texture_format;

	if (this->tr->textureBpp == 32)
		texture_format = GL_RGBA;
	else if (this->tr->textureBpp == 24)
		texture_format = GL_RGB;
	else
		texture_format = GL_RGBA;

	auto d = glGetError();

	if (this->tr->minFilter == "LINEAR")
		glTexParameteri(tr->texture_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (this->tr->magFilter == "LINEAR")
		glTexParameteri(tr->texture_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (this->tr->wrapS == "CLAMP_TO_EDGE")
		glTexParameteri(tr->texture_type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	if (this->tr->wrapS == "GL_REPEAT")
		glTexParameteri(tr->texture_type, GL_TEXTURE_WRAP_S, GL_REPEAT);

	if (this->tr->wrapT == "CLAMP_TO_EDGE")
		glTexParameteri(tr->texture_type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	if (this->tr->wrapT == "GL_REPEAT")
		glTexParameteri(tr->texture_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	auto e = glGetError();

	if(this->tr->type == "2d")
		glTexImage2D(tr->texture_type, 0, texture_format, this->tr->textureWidth, this->tr->textureHeight, 0, texture_format, GL_UNSIGNED_BYTE, this->pixelArray);
	else if (this->tr->type == "cube")
	{
		int width = this->tr->textureWidth / 4;
		int height = this->tr->textureHeight / 3;

		auto g = glGetError();

		auto h = glGetError();

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, texture_format, width, height, 0, texture_format, GL_UNSIGNED_BYTE, 0);
		for (int i = 0; i < height; i++) {
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, 0, i, width, 1, texture_format, GL_UNSIGNED_BYTE, this->pixelArray + (this->tr->textureWidth*height + 2 * width) * this->tr->textureBpp / 8 + this->tr->textureWidth * (this->tr->textureBpp / 8)*i);
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, texture_format, width, height, 0, texture_format, GL_UNSIGNED_BYTE, 0);
		for (int i = 0; i < height; i++) {
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, 0, i, width, 1, texture_format, GL_UNSIGNED_BYTE, this->pixelArray + this->tr->textureWidth*height * this->tr->textureBpp/8 + this->tr->textureWidth * (this->tr->textureBpp / 8)*i);
		}//imaginea din dreapta

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, texture_format, width, height, 0, texture_format, GL_UNSIGNED_BYTE, this->pixelArray);
		for (int i = 0; i < height; i++) {
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, 0, i, width, 1, texture_format, GL_UNSIGNED_BYTE, this->pixelArray + width * this->tr->textureBpp / 8 + this->tr->textureWidth * (this->tr->textureBpp / 8)*i);
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, texture_format, width, height, 0, texture_format, GL_UNSIGNED_BYTE, this->pixelArray);
		for (int i = 0; i < height; i++) {
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, 0, i, width, 1, texture_format, GL_UNSIGNED_BYTE, this->pixelArray + (this->tr->textureWidth*height*2 + width) * this->tr->textureBpp / 8 + this->tr->textureWidth * (this->tr->textureBpp / 8)*i);
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, texture_format, width, height, 0, texture_format, GL_UNSIGNED_BYTE, this->pixelArray);
		for (int i = 0; i < height; i++) {
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, 0, i, width, 1, texture_format, GL_UNSIGNED_BYTE, this->pixelArray + (this->tr->textureWidth*height + width) * this->tr->textureBpp / 8 + this->tr->textureWidth * (this->tr->textureBpp / 8)*i);
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, texture_format, width, height, 0, texture_format, GL_UNSIGNED_BYTE, this->pixelArray);
		for (int i = 0; i < height; i++) {
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, 0, i, width, 1, texture_format, GL_UNSIGNED_BYTE, this->pixelArray + (this->tr->textureWidth*height + 3 * width) * this->tr->textureBpp / 8 + this->tr->textureWidth * (this->tr->textureBpp / 8)*i);
		}

		auto f = glGetError();
		int bss = 3;
	}

	auto b = glGetError();

	//TODO:ceata
}
