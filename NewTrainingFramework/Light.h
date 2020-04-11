#pragma once
#include "../Utilities/Math.h"

class Light
{
public:
	Vector3 position, directionLight, specColor, diffColor;
	int id;
	float specPower;
	std::string type;
};