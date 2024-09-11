#include "..\headers\Enemy.h"

Enemy::Enemy(int health, Vector3 position, std::string texturePath, Behaviour behaviourType) : GameObject(position, texturePath)
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

