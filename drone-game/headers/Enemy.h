#pragma once
#include "GameObject.h"
#include "raylib.h"
#include "SpriteSet.h"
#include <string>
class Enemy : public GameObject {
public:
	bool canBeDamaged() override;
	enum Behaviour { AGGRESSIVE, FLANKING, DEFENSIVE, BALANCED, SHORT_TEMPER, TEST };
	Enemy(int health, Vector3 position, SpriteSet sprites, Behaviour behaviourType);
	void Damage(int amount);
private:
	enum States {BLOCK,RETREAT,PUSH,PUNCH};
	int health = 1;
	void RunAI(Behaviour type);
};