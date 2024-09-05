#include "../headers/GameObject.h"

void GameObject::applyForces() {
	// apply all forces to velocity, capping to max speed if appropriate

	// add forces to velocity

	// cap movement above maxSpeed

	// add velocity to position

	// check if new position instersects with an object

		// if true move to edge of object
}
GameObject::GameObject(Vector3 pos, std::string texture_path)
{
	this->pos = pos;
	this->texture = LoadTexture(texture_path.c_str());
}
