#include "../headers/Damagable.h"

//bool Damagable::damage(int damage) {
//	this->health = this->health - damage;
//	return !(this->health > 0);
//}
bool Damagable::canBeDamaged() const
{
	return true;
}

Damagable::Damagable(int startingHealth) : health(startingHealth)
{
}
