#include "stdafx.h"
#include "BoxCollider.h"

IntersectData BoxCollider::IntersectAxisAlignedBoundingBox(BoxCollider & other)
{
	Vector3 distances1 = other.GetMinExtents() - m_maxExtents;
	Vector3 distances2 = m_minExtents - other.GetMaxExtents();
	Vector3 distances;

	distances.x = distances1.x > distances2.x ? distances1.x : distances2.x;
	distances.y = distances1.y > distances2.y ? distances1.y : distances2.y;
	distances.z = distances1.z > distances2.z ? distances1.z : distances2.z;

	float maxDistance;
	if (distances.x > distances.y && distances.x > distances.z)
		maxDistance = distances.x;
	else if (distances.y > distances.x && distances.y > distances.z)
		maxDistance = distances.y;
	else
		maxDistance = distances.z;

	return IntersectData(maxDistance < 0, distances);
}
