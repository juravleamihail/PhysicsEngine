#include "stdafx.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"

IntersectData Collider::Intersect(Collider & other)
{
	if (m_type == TYPE_SPHERE && other.GetType() == TYPE_SPHERE)
	{
		SphereCollider * self = (SphereCollider*)this;
		SphereCollider &other1 = (SphereCollider&)other;
		return self->IntersectSphereCollider((SphereCollider&)other);
	}
	else if (m_type == TYPE_BOX && other.GetType() == TYPE_BOX)
	{
		BoxCollider* self = (BoxCollider*)this;
		BoxCollider& other1 = (BoxCollider&)other;
		return self->IntersectAxisAlignedBoundingBox((BoxCollider&)other);
	}

	return IntersectData(false, 0);
}

void Collider::Transform(Vector3 & translation)
{
}
