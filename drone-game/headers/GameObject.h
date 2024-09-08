#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <string>
#include "raylib.h"

class GameObject{
public:

	Texture2D texture;
	const float maxSpeed = 100;
	int direction = 0;
	
	/// <summary>
	/// warning force is not fully implemented right now, apply velocity directly instead
	/// </summary>
	Vector3 force = { 0,0,0 };
	Vector3 pos = { 0,0,0 };
	Vector3 velocity = { 0,0,0 };
	void applyForces(double delta_time);
	GameObject(Vector3 pos,std::string texture_path);
};
#endif // !GAMEOBJECT_H