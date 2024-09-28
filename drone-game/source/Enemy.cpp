#include "..\headers\Enemy.h"

bool Enemy::canBeDamaged()
{
	return true;
}

Enemy::Enemy(int health, Vector3 position, SpriteSet sprites, Behaviour behaviourType) : GameObject(position, sprites.rest)
{
	this->health = health;
	this->sprites = sprites;
}

void Enemy::Damage(int amount)
{
	this->health = this->health - amount;
	this->currentState = STUNNED;
	this->texture = this->sprites.hit;
	this->stunTimeRemaining = 0.2;
	if (this->health<=0){
		this->active = false;
	}
}

void Enemy::RunAI(Behaviour type,GameObject* player)
{
	if (currentState == STUNNED) {
		this->stunTimeRemaining = this->stunTimeRemaining - GetFrameTime();
		if (this->stunTimeRemaining <= 0) {
			adjustAggression();
			this->currentState = findNextAction(type,player);
			
			this->texture = this->sprites.rest;
		}
	}
}

void Enemy::adjustAggression()
{
	//include features like if player is moving towards enemy (i.e. looks like they might punch or has block lowered)
	this->aggressionLevel = this->aggressionLevel +
		((this->baseAggressionIncreaseRate)*GetFrameTime());
	printf("%f", this->aggressionLevel);
}

void Enemy::applyState(GameObject* target)
{
	switch (this->currentState)
	{
	case State::BLOCK:
		this->texture = this->sprites.block;
	case State::PUNCH:
		this->texture = this->sprites.punch_heavy;
		//hit target
		//todo make hit function for player - probably worth creating a class "damagable" that enemy and player inherit from
	case State::PUSH:
		this->texture = this->sprites.moveAnim.at(0);//todo create play animation function
	case State::WAIT:
		this->texture = this->sprites.rest;
	case State::STUNNED:
		this->texture = this->sprites.hit;
	case State::RETREAT:
		this->texture = this->sprites.moveAnim.at(0);
	default:
		break;
	}
}

Enemy::State Enemy::findNextAction(Behaviour type, GameObject* player)
{
	Vector3 playerPos = player->pos;

	if (this->currentState == State::STUNNED) {
		return State::STUNNED;
	}

	//if player is visible but not in fighting range, approach
	if (Vector3Distance(playerPos, this->pos) < this->aggroDist && Vector3Distance(playerPos, this->pos) > this->attackDist) {
		return State::PUSH;
	}
	//if player is in fighting range and aggression is high, punch
	else if (Vector3Distance(playerPos, this->pos) < this->aggroDist && this->aggressionLevel > 0.8) {
		return State::PUNCH;
	}
	//if the enemy is about to punch, lower block to give player time to react
	else if (Vector3Distance(playerPos, this->pos) < this->aggroDist && this->aggressionLevel > 0.6) {
		return State::WAIT;
	}
	//if player is in fighting range and aggression is low, block
	else if ((Vector3Distance(playerPos, this->pos) < this->aggroDist && this->aggressionLevel > 0.2)) {
		return State::BLOCK;
	}
	//if player is in fighting range and aggression is very low, retreat
	else if (Vector3Distance(playerPos, this->pos) < this->aggroDist) {
		return State::RETREAT;
	}
	//if player is out of aggro range and do nothing
	else {
		return State::WAIT;
	}
}


