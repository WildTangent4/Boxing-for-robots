#pragma once
#include "GameObject.h"
#include "UIController.h"
#include "raylib.h"
#include "rcamera.h"
#include <vector>

class CharacterController;//forward declaration avoids circular include from enemy.H

class Player {
	Camera3D cam;
	UIController interfaceController;
	CharacterController* inputController;
	int health;
public:
	Player(int health, Vector3 position, Camera3D& cam,GameObject& baseObject);
	void update(std::vector<GameObject*> objects);
	bool damage(int amount);//note this is NOT the Damagable class method being overriden, player is a special case because of the project structure
	GameObject* obj;
};