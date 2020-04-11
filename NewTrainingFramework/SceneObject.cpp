#include "stdafx.h"
#include "Vertex.h"
#include "SceneObject.h"
#include "SceneManager.h"

SceneObject::SceneObject()
{
	oldPosition = position;
	UpdateModelMatrix();
	isFollowingCameraOx = false; isFollowingCameraOy = false; isFollowingCameraOz = false;
}

SceneObject::~SceneObject()
{
}

void SceneObject::UpdateModelMatrix()
{
	Matrix S, T, Rx, Ry, Rz;
	T.SetTranslation(position);
	S.SetScale(scale);
	Rx.SetRotationX(rotation.x);
	Ry.SetRotationY(rotation.y);
	Rz.SetRotationZ(rotation.z);

	modelMatrix = S * Rx * Ry * Rz * T;
}

void SceneObject::InitObject()
{
	model->nrIndici = model->mr->indicesVector.size();

	//buffer object
	glGenBuffers(1, &model->vboId);
	glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*model->mr->modelVerticesVector.size(), model->mr->modelVerticesVector.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &model->ibold);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->ibold);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*model->mr->indicesVector.size(), model->mr->indicesVector.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	UpdateModelMatrix();
}

void SceneObject::Draw()
{
	glUseProgram(shader->programId);

	SetCommonData();

	glDrawElements(GL_TRIANGLES, model->nrIndici, GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SceneObject::SetCommonData()
{
	glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->ibold);

	Matrix mat;
	mat.SetIdentity();
	mat = modelMatrix * SceneManager::getInstance()->GetActiveCamera()->viewMatrix * SceneManager::getInstance()->GetActiveCamera()->perspMatrix;

	if (shader->sr->positionAttribute != -1)
	{
		glEnableVertexAttribArray(shader->sr->positionAttribute);
		glVertexAttribPointer(shader->sr->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (shader->sr->modelUniform != -1)
	{
		glUniformMatrix4fv(shader->sr->modelUniform, 1, GL_FALSE, (GLfloat*)modelMatrix.m );
	}

	if (shader->sr->camPosUniform != -1)
	{
		auto cameraPos = SceneManager::getInstance()->GetActiveCamera()->position;
		glUniform3f(shader->sr->camPosUniform, cameraPos.x, cameraPos.y, cameraPos.z);
	}

	if (shader->sr->fogColorUniform != -1)
	{
		glUniform3f(shader->sr->fogColorUniform, SceneManager::getInstance()->fogColor.x , SceneManager::getInstance()->fogColor.y, SceneManager::getInstance()->fogColor.z);
	}

	if (shader->sr->wideRadiusUniform != -1)
	{
		glUniform1f(shader->sr->wideRadiusUniform, SceneManager::getInstance()->wideRadius);
	}

	if (shader->sr->smallRadiusUniform != -1)
	{
		glUniform1f(shader->sr->smallRadiusUniform, SceneManager::getInstance()->smallRadius);
	}

	if (shader->sr->colorAttribute != -1)
	{
		glEnableVertexAttribArray(shader->sr->colorAttribute);
		glVertexAttribPointer(shader->sr->colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(Vector3));
	}

	if (shader->sr->textureCoordAttribute != -1)
	{
		glEnableVertexAttribArray(shader->sr->textureCoordAttribute);

		glVertexAttribPointer(shader->sr->textureCoordAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(5 * sizeof(Vector3)));
	}

	if (shader->sr->textureCoordAttribute2 != -1)
	{
		glEnableVertexAttribArray(shader->sr->textureCoordAttribute2);

		glVertexAttribPointer(shader->sr->textureCoordAttribute2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(5 * sizeof(Vector3) + sizeof(Vector2)));
	}

	if (shader->sr->rotationMatrixUniform != -1)
	{
		glUniformMatrix4fv(shader->sr->rotationMatrixUniform, 1, GL_FALSE, (GLfloat*)(mat.m));
	}

	if (shader->sr->c_ambUniform != -1)
	{
		Vector3 ambLight = SceneManager::getInstance()->ambientalLight;
		glUniform3f(shader->sr->c_ambUniform, ambLight.x, ambLight.y, ambLight.z);
	}

	if (shader->sr->ratioAmbientalUniform != -1)
		glUniform1f(shader->sr->ratioAmbientalUniform, SceneManager::getInstance()->ambientalLightRatio);
	
	int count = 0;
	for (auto lightmap : SceneManager::getInstance()->lightsMap)
	{
		if (shader->sr->c_luminaDiffUniform[count] != -1)
		{
			Vector4 diffColor = lightmap.second->diffColor;
			glUniform4f(shader->sr->c_luminaDiffUniform[count], diffColor.x, diffColor.y, diffColor.z, diffColor.w);
		}

		if (shader->sr->c_luminaSpecUniform[count] != -1)
		{
			Vector4 specColor = lightmap.second->specColor;
			glUniform4f(shader->sr->c_luminaSpecUniform[count], specColor.x, specColor.y, specColor.z, specColor.w);
		}

		if (shader->sr->a_normalUniform[count] != -1)
		{
			glEnableVertexAttribArray(shader->sr->a_normalUniform[count]);
			glVertexAttribPointer(shader->sr->a_normalUniform[0], 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(2 * sizeof(Vector3)));
		}

		if (shader->sr->directionLightUniform[count] != -1)
		{
			Vector4 directionLight = lightmap.second->directionLight;
			glUniform4f(shader->sr->directionLightUniform[count], directionLight.x, directionLight.y, directionLight.z, directionLight.w);
		}

		if (shader->sr->SpecPowerUniform[count] != -1)
			glUniform1f(shader->sr->SpecPowerUniform[count], lightmap.second->specPower);

		count++;
	}

	for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(textures[i]->tr->texture_type, textures[i]->textureId);

		if (shader->sr->uniformTexture[i] != -1)
		{
			glUniform1i(shader->sr->uniformTexture[i], i);
		}
	}
}

void SceneObject::Update()
{
	if (isFollowingCameraOx)
		position.x = SceneManager::getInstance()->GetActiveCamera()->position.x;

	if (isFollowingCameraOy)
		position.y = SceneManager::getInstance()->GetActiveCamera()->position.y;

	if (isFollowingCameraOz)
		position.z = SceneManager::getInstance()->GetActiveCamera()->position.z;
	
	//if (isFollowingCameraOx || isFollowingCameraOy || isFollowingCameraOz)
		UpdateModelMatrix();
}
