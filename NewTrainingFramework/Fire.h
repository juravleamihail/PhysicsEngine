#pragma once
#include "SceneObject.h"

class Fire: public SceneObject
{
public:
	void Draw();
	void Update();
	float u_time, dispMax;
};