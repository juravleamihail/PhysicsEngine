#include "stdafx.h"
#include "Plane.h"
#include "math.h"

Plane Plane::Normalized()
{
	float magnitude = m_normal.Length();

	return Plane(m_normal/magnitude, m_distance / magnitude);
}

IntersectData Plane::IntersectSphere(SphereCollider other)
{
	float distanceFromSphereCenter = fabs(m_normal.Dot(other.GetCenter()) + m_distance);
	float distanceFromSphere = distanceFromSphereCenter - other.GetRadius();

	return IntersectData(distanceFromSphere < 0, m_normal * distanceFromSphere);
}
