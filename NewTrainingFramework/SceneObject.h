#include <string>
#include <vector>
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#pragma once
#include "../Utilities/Math.h"

class SceneObject
{
public:
	SceneObject();
	~SceneObject();
	void UpdateModelMatrix();
	void InitObject();
	void virtual Draw();
	void virtual Update();
	void SetCommonData();

	std::string idModel, type, blend, name;
	int idShader;
	Vector3 height;
	std::vector<Texture*> textures;
	Vector3 position, rotation, scale, color, up;
	Vector3 oldPosition;
	Vector3 xAxis, yAxis, zAxis;
	Matrix modelMatrix, viewMatrix, projectionMatrix;
	GLfloat moveSpeed, rotateSpeed;
	Vector3 velocity;
	float radius;
	bool isFollowingCameraOx = false, isFollowingCameraOy = false, isFollowingCameraOz = false;
	Model* model;
	Shader* shader;
};
