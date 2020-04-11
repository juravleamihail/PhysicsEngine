#pragma once
#include "SceneObject.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

class PhysicsObject
{
public:
	PhysicsObject(Collider collider) : m_collider(collider), m_sphereCollider(SphereCollider(Vector3(0,0,0), 0)), m_boxCollider(BoxCollider(Vector3(0,0,0),Vector3(0,0,0))){}
	void Integrate(float delta);
	SceneObject * sceneObject;
	float GetRadius() { return sceneObject->radius; }
	Vector3 GetPosition() { return sceneObject->position; }
	Vector3 GetVelocity() { return sceneObject->velocity; }
	void SetVelocity(Vector3 newVelocity);
	Collider GetCollider() 
	{
		Vector3 translation = sceneObject->position - sceneObject->oldPosition;
		sceneObject->oldPosition = sceneObject->position;
		m_collider.Transform(translation);
	
		return m_collider;
	}

	SphereCollider GetSphereCollider()
	{
		m_sphereCollider.SetRadius(sceneObject->radius);
		m_sphereCollider.SetCenter(sceneObject->position);
		return m_sphereCollider;
	}

	BoxCollider GetBoxCollider()
	{
		m_boxCollider.m_minExtents = sceneObject->position - Vector3(50, 50, 50);
		m_boxCollider.m_maxExtents = sceneObject->position + Vector3(50, 50, 50);
		return m_boxCollider;
	}

	BoxCollider SetBoxCollider(Vector3 minExtents, Vector3 maxExtents)
	{
		m_boxCollider.m_minExtents = minExtents;
		m_boxCollider.m_maxExtents = maxExtents;
	}
private:
	Collider m_collider;
	SphereCollider m_sphereCollider;
	BoxCollider m_boxCollider;
};