#include "stdafx.h"
#include <iostream>
#include "PhysicsObject.h"

void PhysicsObject::Integrate(float delta)
{
	sceneObject->position += sceneObject->velocity * delta;
	//sceneObject->UpdateModelMatrix();
}

void PhysicsObject::SetVelocity(Vector3 newVelocity)
{
	sceneObject->velocity = newVelocity;
}
