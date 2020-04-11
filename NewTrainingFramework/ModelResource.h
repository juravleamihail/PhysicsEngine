#include <string>
#include "Vertex.h"
#include <vector>
#pragma once

class ModelResource
{
public:
	std::string path = "";
	std::vector<Vertex> modelVerticesVector;
	std::vector<GLushort> indicesVector;
};