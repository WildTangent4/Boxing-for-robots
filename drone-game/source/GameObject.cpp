#include "../headers/GameObject.h"
#include "raymath.h"
void GameObject::applyForces(double delta_time) {
	// apply all forces to velocity, capping to max speed if appropriate (use std clamp)
	// add forces to velocity
	Vector3 new_velocity= Vector3Add(this->velocity, this->force);
	this->velocity = new_velocity;
	double time_scale = delta_time / 2000;
	//printf("\n%f", time_scale);
	Vector3 scaled_velocity =  Vector3Scale(Vector3Add(this->velocity,this->force), time_scale);
	
	//reset force for next tick
	this->force = { 0,0,0 };

	this->pos.x = this->pos.x + scaled_velocity.x;
	this->pos.y = this->pos.y + scaled_velocity.y;
	this->pos.z = this->pos.z + scaled_velocity.z;
}
GameObject::GameObject(Vector3 pos, std::string texture_path)
{
	this->pos = pos;
	this->texture = LoadTexture(texture_path.c_str());
}
