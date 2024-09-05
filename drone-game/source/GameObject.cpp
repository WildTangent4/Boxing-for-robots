#include "../headers/GameObject.h"
#include "raymath.h"
void GameObject::applyForces(double delta_time) {
	// apply all forces to velocity, capping to max speed if appropriate (use std clamp)
	// add forces to velocity
	Vector3 scaled_force = Vector3Scale(this->force, delta_time / 60);
	this->velocity = Vector3Add(this->velocity, scaled_force);
	//reset force for next tick
	this->force = { 0,0,0 };

	// cap movement below maxSpeed
	//this->velocity = Vector3ClampValue(this->velocity, -(this->maxSpeed), this->maxSpeed);
	
	// add velocity to position
	printf("POS: X:%f  Y:%f  Z:%f\n", this->pos.x, this->pos.y, this->pos.z);
	//this->pos = Vector3Add(this->pos, this->velocity);
	this->pos.x = this->pos.x + this->velocity.x;
	this->pos.x = this->pos.y + this->velocity.y;
	this->pos.x = this->pos.z + this->velocity.z;
	printf("POS: X:%f  Y:%f  Z:%f\n", this->pos.x,this->pos.y,this->pos.z);
	printf("VEL: X:%f  Y:%f  Z:%f\n", this->velocity.x, this->velocity.y, this->velocity.z);
}
GameObject::GameObject(Vector3 pos, std::string texture_path)
{
	this->pos = pos;
	this->texture = LoadTexture(texture_path.c_str());
}
