#include "stdafx.h"
#include "SceneManager.h"
#include "Fire.h"

void Fire::Draw()
{
	glUseProgram(shader->programId);

	if (shader->sr->u_TimeUniform != -1)
	{
		glUniform1f(shader->sr->u_TimeUniform, u_time);
	}

	if (shader->sr->dispMaxUniform != -1)
	{
		glUniform1f(shader->sr->dispMaxUniform, dispMax);
	}

	SetCommonData();

	glDrawElements(GL_TRIANGLES, model->nrIndici, GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Fire::Update()
{
	u_time = clock();
	u_time = u_time / 2000;

	if (u_time > 1)
		u_time--;
}