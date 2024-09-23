#include "..\headers\Enemy.h"

bool Enemy::canBeDamaged()
{
	return true;
}

Enemy::Enemy(int health, Vector3 position, SpriteSet sprites, Behaviour behaviourType) : GameObject(position, sprites.rest)
{
	this->health = health;
	this->sprites = sprites;
	RunAI(behaviourType);
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

void Enemy::RunAI(Behaviour type)
{
	if (currentState == STUNNED) {
		this->stunTimeRemaining = this->stunTimeRemaining - GetFrameTime();
		if (this->stunTimeRemaining <= 0) {
			currentState = findNextAction(type);
			this->texture = this->sprites.rest;
		}
	}
}

Enemy::State Enemy::findNextAction(Behaviour type)
{
	return WAIT;
}


