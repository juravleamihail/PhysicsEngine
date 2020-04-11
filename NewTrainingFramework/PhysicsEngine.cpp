#include "stdafx.h"
#include "IntersectData.h"
#include "PhysicsEngine.h"

void PhysicsEngine::AddPhysicsObject(PhysicsObject physicsObject)
{
	m_objects.push_back(physicsObject);
}

void PhysicsEngine::Simulate(float delta)
{
	for each (auto object in m_objects)
	{
		object.Integrate(delta);
	}
}

PhysicsObject PhysicsEngine::GetPhisicsObject(int index)
{
	return m_objects[index];
}

int PhysicsEngine::GetNumObjects()
{
	return m_objects.size();
}

PhysicsEngine * PhysicsEngine::peInstance = NULL;

PhysicsEngine * PhysicsEngine::getInstance()
{
	if (peInstance == NULL)
		peInstance = new PhysicsEngine();
	
	return peInstance;
}

void PhysicsEngine::HandleCollisions()
{
	for (int i = 0; i < m_objects.size(); i++)
	{
		for (int j = i+1; j < m_objects.size(); j++)
		{
			auto b1 = m_objects[i].GetRadius();
			auto b2 = m_objects[j].GetRadius();
			auto s2 = m_objects[j].GetCollider();

			auto c1 = m_objects[i].GetCollider();

			//For sphere collider
			//IntersectData intersectData = m_objects[i].GetSphereCollider().IntersectSphereColliderTest(m_objects[j].GetSphereCollider());

			//For Box Collider
			IntersectData intersectData = m_objects[i].GetBoxCollider().IntersectAxisAlignedBoundingBox(m_objects[j].GetBoxCollider());

			if (intersectData.GetDoesIntersect())
			{
				/*m_objects[i].SetVelocity(m_objects[i].GetVelocity() * -1);
				m_objects[j].SetVelocity(m_objects[j].GetVelocity() * -1);*/

				Vector3 direction = intersectData.GetDirection().Normalize();
				Vector3 otherDirection = Reflect(direction, m_objects[i].GetVelocity().Normalize());
				m_objects[i].SetVelocity(Vector3(Reflect(m_objects[i].GetVelocity(), otherDirection)));
				m_objects[j].SetVelocity(Vector3(Reflect(m_objects[j].GetVelocity(), direction)));
			}
		}
	}
}

void PhysicsEngine::Update(float deltaTime)
{
	Simulate(deltaTime);
	HandleCollisions();
}

Vector3 PhysicsEngine::Reflect(Vector3 vec, Vector3 normal)
{
	return (vec - (normal * (vec.Dot(normal) * 2)));
}
