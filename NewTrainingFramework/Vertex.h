#pragma once
#include "..\\Utilities\Math.h"

struct Vertex 
{
	Vector3 pos;
	Vector3 col;
	Vector3 norm;
	Vector3 binorm;
	Vector3 tgt;
	Vector2 uv;
	Vector2 uv2;

	Vertex(const Vertex & v2) : pos(v2.pos), col(v2.col), norm(v2.norm), binorm(v2.binorm), tgt(v2.tgt), uv(v2.uv), uv2(v2.uv2) {}
	Vertex():pos(Vector3(0,0,0)), col(Vector3(0, 0, 0)), norm(Vector3(0, 0, 0)), binorm(Vector3(0, 0, 0)), tgt(Vector3(0, 0, 0)), uv(Vector2(0, 0)), uv2(Vector2(0,0)){}
};

