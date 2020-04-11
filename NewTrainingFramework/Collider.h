#pragma once
#include "IntersectData.h"

#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

class Collider
{
public:
	enum
	{
		TYPE_BOX,
		TYPE_SPHERE
	};

	Collider(int type): m_type(type) {}

	IntersectData Intersect(Collider & other);

	virtual void Transform(Vector3& translation);

	int GetType() { return m_type; }
private:
	int m_type;
};
