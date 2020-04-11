#include "SceneObject.h"
#pragma once

class TerrainObject : public SceneObject
{
public:
	int nrCelule, dimCelula;
	int offsetY;
	void InitTerrain();

	TerrainObject();
	void Draw();
	void Update();
};
