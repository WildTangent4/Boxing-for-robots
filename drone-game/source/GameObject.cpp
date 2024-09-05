#include "../headers/GameObject.h"
#include "raymath.h"
void GameObject::applyForces(double delta_time) {
	// apply all forces to velocity, capping to max speed if appropriate (use std clamp)
	// add forces to velocity
	Vector3 new_velocity= Vector3Add(this->velocity, this->force);
	double time_scale = delta_time / 1000;
	printf("%f\n", time_scale);
	Vector3 scaled_velocity =  Vector3Scale(Vector3Add(this->velocity,this->force), time_scale);
	//reset force for next tick
	//this->force = { 0,0,0 };

	// cap movement below maxSpeed
	//this->velocity = Vector3ClampValue(this->velocity, -(this->maxSpeed), this->maxSpeed);
	
	// add velocity to position
	//printf("POS BEFORE: X:%f  Y:%f  Z:%f\n", this->pos.x, this->pos.y, this->pos.z);
	printf("x:%f Dx:%f\n", this->pos.x, this->pos.x + scaled_velocity.x);
	printf("y:%f Dy:%f\n", this->pos.y, this->pos.y + scaled_velocity.y);
	printf("z:%f Dz: %f\n", this->pos.z, this->pos.z + scaled_velocity.z);
	//this->pos = Vector3Add(this->pos, this->velocity);
	this->pos.x = this->pos.x + scaled_velocity.x;
	this->pos.y = this->pos.y + scaled_velocity.y;
	this->pos.z = this->pos.z + scaled_velocity.z;
	printf("x:%f\n", this->pos.x);
	printf("y:%f\n", this->pos.y);
	printf("z:%f\n", this->pos.z);
	//printf("POS AFTER: X:%f  Y:%f  Z:%f\n", this->pos.x,this->pos.y,this->pos.z);
	//printf("VEL: X:%f  Y:%f  Z:%f\n", this->velocity.x, this->velocity.y, this->velocity.z);
}
GameObject::GameObject(Vector3 pos, std::string texture_path)
{
	this->pos = pos;
	this->texture = LoadTexture(texture_path.c_str());
}
