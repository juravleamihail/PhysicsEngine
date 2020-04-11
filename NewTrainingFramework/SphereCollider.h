#pragma once
#include "IntersectData.h"
#include "Collider.h"

#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

class SphereCollider : public Collider
{
public:
	SphereCollider(Vector3 center, float radius) : Collider(Collider::TYPE_SPHERE), m_center(center), m_radius(radius){}

	IntersectData IntersectSphereCollider(SphereCollider other);
	IntersectData IntersectSphereColliderTest(SphereCollider other);

	void Transform(Vector3& translation);

	Vector3 GetCenter() { return m_center; }
	float GetRadius() { return m_radius; }
	void SetRadius(float radius) { m_radius = radius; }
	void SetCenter(Vector3 center) { m_center = center; }

private:
	Vector3 m_center;
	float m_radius;
};
