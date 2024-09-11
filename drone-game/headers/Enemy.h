#pragma once
#include "GameObject.h"
class Enemy : public GameObject {
	Enemy(int health);
private:
	enum Behaviour {AGGRESSIVE,FLANKING, DEFENSIVE, BALANCED, SHORT_TEMPER};
	enum States {BLOCK,RETREAT,PUSH,PUNCH};
	int health = 1;
	void Damage(int amount);
	void RunAI();
};