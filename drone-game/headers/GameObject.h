#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <string>
#include "raylib.h"

class GameObject{
public:
	virtual bool canBeDamaged();
	bool active = true;
	Texture2D texture;
	int direction = 0;
	/// <summary>
	/// warning force is not fully implemented right now, apply velocity directly instead
	/// </summary>
	Vector3 force = { 0,0,0 };
	Vector3 pos = { 0,0,0 };
	Vector3 velocity = { 0,0,0 };
	void applyForces(double delta_time);
	GameObject(Vector3 pos,std::string texture_path);
	GameObject(Vector3 pos, Texture2D texture);
	virtual ~GameObject() = default;
private:
	const float maxSpeed = 100;
};
#endif // !GAMEOBJECT_H