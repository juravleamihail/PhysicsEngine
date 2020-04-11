#pragma once
#include <vector>
#include "PhysicsObject.h"

class PhysicsEngine
{
public:
	void AddPhysicsObject(PhysicsObject physicsObject);
	void Simulate(float delta);
	PhysicsObject GetPhisicsObject(int index);
	int GetNumObjects();
	static PhysicsEngine* getInstance();
	void HandleCollisions();
	void Update(float deltaTime);
	Vector3 Reflect(Vector3 vec, Vector3 normal);
private:
	std::vector<PhysicsObject> m_objects;
	static PhysicsEngine* peInstance;
};
