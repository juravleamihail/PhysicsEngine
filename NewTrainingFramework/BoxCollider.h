#pragma once
#include "IntersectData.h"
#include "Collider.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

class BoxCollider : public Collider
{
public:
	BoxCollider(Vector3 minExtents, Vector3 maxExtents) : Collider(Collider::TYPE_BOX), m_minExtents(minExtents), m_maxExtents(maxExtents){}
	IntersectData IntersectAxisAlignedBoundingBox(BoxCollider& other) ;
	Vector3 GetMinExtents() { return m_minExtents; }
	Vector3 GetMaxExtents() { return m_maxExtents; }
	Vector3 m_minExtents;
	Vector3 m_maxExtents;
};
