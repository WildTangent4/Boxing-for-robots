#pragma once
#include "GameObject.h"
#include "raylib.h"
#include "SpriteSet.h"
#include <string>
#include "raymath.h"
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
	void RunAI(Behaviour type,GameObject* player);
private:
	//float from 0 to 1, 1 being max agression, 0 being minimum, the ai will attack if the aggression value is high
	float aggressionLevel = 0;

	//increase agression by this much per second, modifiers should be applied based on factors like current health and time since last hit
	float baseAggressionIncreaseRate = 0.5;
	enum State {
		BLOCK = 1, //dont move and protect yourself
		RETREAT = 2,//walk away from the player and maintain a safe ish distance
		PUSH = 3,//move to get into a position to attack the player
		PUNCH = 4,//attack the player
		STUNNED = 5,//stop all actions after being hit
		WAIT = 6
	};
	State currentState;
	SpriteSet sprites;
	float moveSpeed = 0.1;
	float stunTimeRemaining = 0;
	int health = 1;
	float aggroDist = 10;
	float attackDist = 2;
	void adjustAggression();
	void applyState(GameObject* target);
	State findNextAction(Behaviour type,GameObject * player);
};