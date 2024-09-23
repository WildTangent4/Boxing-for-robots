#include "..\headers\Enemy.h"

bool Enemy::canBeDamaged()
{
	return true;
}

Enemy::Enemy(int health, Vector3 position, SpriteSet sprites, Behaviour behaviourType) : GameObject(position, sprites.rest)
{
	this->health = health;
	RunAI(behaviourType);
}

void Enemy::Damage(int amount)
{
	this->health = this->health - amount;
	if (this->health<=0){
		this->active = false;
	}
}

void Enemy::RunAI(Behaviour type)
{
}

