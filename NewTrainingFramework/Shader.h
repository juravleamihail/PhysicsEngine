#pragma once
#include "ShaderResource.h"

class Shader
{
public:
	ShaderResource * sr; //structura pe baza careia e incarcat shader-ul
	int programId; //obtinut prin linkarea vs-ului si fs-ului

	Shader();
	~Shader();
	void Load();
};