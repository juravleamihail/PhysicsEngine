#pragma once
#include "SphereCollider.h"

#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

class Plane
{
public:
	Plane(Vector3 normal, float distance) : m_normal(normal), m_distance(distance){}

	Plane Normalized();
	IntersectData IntersectSphere(SphereCollider other);

	Vector3 GetNormal() { return m_normal; }
	float GetDistance() { return m_distance; }

private:
	Vector3 m_normal;
	float m_distance;
};
