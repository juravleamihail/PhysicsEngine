#pragma once
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

class IntersectData
{
public:
	//IntersectData(bool doesIntersect, float distance) : m_doesIntersect(doesIntersect), m_distance(distance){}
	IntersectData(bool doesIntersect, Vector3 direction) : m_doesIntersect(doesIntersect), m_direction(direction) {}
	bool GetDoesIntersect() { return m_doesIntersect; }
	float GetDistance() { return m_distance; };
	Vector3 GetDirection() { return m_direction; }
private:
	bool m_doesIntersect;
	float m_distance;
	Vector3 m_direction;
};
