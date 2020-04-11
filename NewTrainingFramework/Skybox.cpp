#include "stdafx.h"
#include "Skybox.h"

void Skybox::Draw()
{
	glUseProgram(shader->programId);

	SetCommonData();

	glDrawElements(GL_TRIANGLES, model->nrIndici, GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Skybox::Update()
{

}