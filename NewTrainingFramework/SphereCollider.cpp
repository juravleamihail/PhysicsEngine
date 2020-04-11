#include "stdafx.h"
#include "SphereCollider.h"

IntersectData SphereCollider::IntersectSphereCollider(SphereCollider other)
{
	float radiusDistance = m_radius + other.m_radius;
	float centerDistance = (other.m_center - m_center).Length();
	float distance = centerDistance - radiusDistance;

	//return IntersectData(centerDistance < radiusDistance, distance);
	return IntersectSphereCollider(SphereCollider(Vector3(0, 0, 0), 0));
}

IntersectData SphereCollider::IntersectSphereColliderTest(SphereCollider other)
{
	float radiusDistance = m_radius + other.m_radius;
	Vector3 direction = other.m_center - m_center;
	float centerDistance = direction.Length();
	direction /= centerDistance;
	float distance = centerDistance - radiusDistance;

	return IntersectData(centerDistance < radiusDistance, direction * distance);
}

void SphereCollider::Transform(Vector3& translation)
{
	m_center += translation;
}
