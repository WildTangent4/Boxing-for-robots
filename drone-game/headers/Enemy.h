#pragma once
#include "GameObject.h"
#include "raylib.h"
#include "SpriteSet.h"
#include <string>
class Enemy : public GameObject {
public:
	enum Behaviour {
		AGGRESSIVE = 1,
		FLANKING = 2, 
		DEFENSIVE = 3, 
		BALANCED = 4, 
		SHORT_TEMPER = 5, 
		TEST = 6
	};
	bool canBeDamaged() override;
	Enemy(int health, Vector3 position, SpriteSet sprites, Behaviour behaviourType);
	void Damage(int amount);
	void RunAI(Behaviour type);
private:
	enum State {
		BLOCK = 1,
		RETREAT = 2,
		PUSH = 3,
		PUNCH = 4,
		STUNNED = 5,
		WAIT = 6
	};
	State currentState;
	SpriteSet sprites;
	float stunTimeRemaining = 0;
	int health = 1;
	
	State findNextAction(Behaviour type);
};