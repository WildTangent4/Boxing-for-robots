#pragma once
#include "GameObject.h"
#include "raylib.h"
#include "SpriteSet.h"
#include <string>
#include "raymath.h"
#include "Damagable.h"
#include "Player.h"



class Enemy : public GameObject, public Damagable {
public:
	enum Behaviour {
		AGGRESSIVE = 1,
		FLANKING = 2, 
		DEFENSIVE = 3, 
		BALANCED = 4, 
		SHORT_TEMPER = 5, 
		TEST = 6
	};
	
	Enemy(int health, Vector3 position, SpriteSet sprites, Enemy::Behaviour behaviourType, bool debug = false);
	bool Damagable::damage(int amount);
	void RunAI(Player* player);
	bool canBeDamaged() const override;
private:
	//float from 0 to 1, 1 being max agression, 0 being minimum, the ai will attack if the aggression value is high
	float aggressionLevel = 0;

	//increase agression by this much per second, modifiers should be applied based on factors like current health and time since last hit
	float baseAggressionIncreaseRate = 0.1;
	enum State {
		BLOCK = 1, //dont move and protect yourself
		RETREAT = 2,//walk away from the player and maintain a safe ish distance
		PUSH = 3,//move to get into a position to attack the player
		PUNCH = 4,//attack the player
		STUNNED = 5,//stop all actions after being hit
		WAIT = 6,
		READY_PUNCH = 7//wind up a punch. changes sprite based on punch charge
	};
	Behaviour AIType;
	State currentState;
	SpriteSet sprites;
	float moveSpeed = 2;
	float stunTimeRemaining = 0;
	int health = 1;
	bool debugMode = true;
	float aggroDist = 10;
	float attackDist = 2;
	float punchCharge = 0;
	float punchWindUpTimeS = 1;//enemy takes this long to do the punch
	float punchLingerTimeS = 0.3;//enemy stays in punch animation for this long after doing the actual punch
	float timeSinceLastPunch = 0.0;
	void adjustAggression();
	void applyState(Player* target);
	State findNextAction(Behaviour type,Player * player);
};