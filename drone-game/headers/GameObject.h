#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <string>
#include "raylib.h"
class GameObject{
public:

	Texture2D texture;
	const int maxSpeed = 100;
	int direction = 0;
	Vector3 pos;
	struct forceOnBody {
		int x = 0;
		int y = 0;
	};
	forceOnBody force;
	struct velocity {
		int x = 0;
		int y = 0;
	};
	velocity velocity;
	void applyForces();
	GameObject(Vector3 pos,std::string texture_path);//(position startPosition, PhysicsManager& physicsSystem);
};
#endif // !GAMEOBJECT_H