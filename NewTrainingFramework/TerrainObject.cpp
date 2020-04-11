#include "stdafx.h"
#include "TerrainObject.h"
#include "SceneManager.h"
#include <iostream>
using namespace std;

void TerrainObject::InitTerrain()
{
	model = new Model();
	model->mr = new ModelResource();
	for (int i = 0; i < nrCelule + 1; i++)
	{
		for (int j = 0; j < nrCelule + 1; j++)
		{
			Vertex vertex;
			vertex.pos = Vector3(-nrCelule / 2 * dimCelula + j * dimCelula, 0, -nrCelule / 2 * dimCelula + i * dimCelula);
			vertex.norm = Vector3(0, 1, 0);
			vertex.uv = Vector2((float)i / nrCelule, (float)j / nrCelule);
			vertex.uv2 = Vector2(i, j);
			model->mr->modelVerticesVector.push_back(vertex);
		}
	}

	for (int i = 0; i < nrCelule ; i++)
	{
		for (int j = 0; j < nrCelule; j++)
		{
			int index1 = i * (nrCelule + 1) + j;
			int index2 = index1 + 1;
			int index3 = (i + 1) * (nrCelule + 1) + j;
			int index4 = index3 + 1;
			model->mr->indicesVector.push_back(index1);
			model->mr->indicesVector.push_back(index2);
			model->mr->indicesVector.push_back(index3);

			model->mr->indicesVector.push_back(index4);
			model->mr->indicesVector.push_back(index3);
			model->mr->indicesVector.push_back(index2);
		}
	}

	position.x = SceneManager::getInstance()->GetActiveCamera()->position.x;
	position.y = 0;
	position.z = SceneManager::getInstance()->GetActiveCamera()->position.z;
}

TerrainObject::TerrainObject()
{
}

void TerrainObject::Draw()
{
	glUseProgram(shader->programId);

	if (shader->sr->heightUniform != -1)
	{
		glUniform3f(shader->sr->heightUniform, height.x, height.y, height.z);
	}

	SetCommonData();

	glDrawElements(GL_TRIANGLES, model->nrIndici, GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void TerrainObject::Update()
{
	float xCam = SceneManager::getInstance()->GetActiveCamera()->position.x;
	float zCam = SceneManager::getInstance()->GetActiveCamera()->position.z;


	if (xCam > position.x && (xCam - position.x) > dimCelula)
	{
		position.x += dimCelula;

		for(int i=0;i< model->mr->modelVerticesVector.size();i++)
			{
				model->mr->modelVerticesVector[i].uv.y += (float)1/nrCelule;
			}
	}

	else if (xCam < (position.x - dimCelula) && xCam < position.x)
	{
		position.x -= dimCelula;

		for (int i = 0; i < model->mr->modelVerticesVector.size(); i++)
		{
			model->mr->modelVerticesVector[i].uv.y -= (float)1 / nrCelule;
		}
	}

	if ((zCam - position.z) > dimCelula && zCam > position.z)
	{
		position.z += dimCelula;

		for (int i = 0; i < model->mr->modelVerticesVector.size(); i++)
		{
			model->mr->modelVerticesVector[i].uv.x += (float)1 / nrCelule;
		}
		int fdf;
	}

	else if (zCam < position.z - dimCelula && zCam < position.z)
	{
		position.z -= dimCelula;

		for (int i = 0; i < model->mr->modelVerticesVector.size(); i++)
		{
			model->mr->modelVerticesVector[i].uv.x -= (float)1 / nrCelule;
		}
		int gddf;
	}

	model->nrIndici = model->mr->indicesVector.size();

	//buffer object
	glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*model->mr->modelVerticesVector.size(), model->mr->modelVerticesVector.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->ibold);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*model->mr->indicesVector.size(), model->mr->indicesVector.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	UpdateModelMatrix();
}
