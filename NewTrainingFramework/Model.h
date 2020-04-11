#pragma once
#include "ModelResource.h"
#include <string>

class Model
{
public:
	ModelResource* mr; //structura pe baza careia e incarcat modelul
	GLuint ibold; //id-ul bufferului care contine indicii
	GLuint wireIbold; //id-ul bufferului care contine indicii pentru afisarea wired
	GLuint vboId; //id - ul bufferului care contine vertecsii
	int nrIndici, nrIndiciWired;
	
	Model();
	~Model();
	void Load();
	void ReadIndicesString(std::string indicesString);
};
