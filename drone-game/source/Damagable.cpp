#include "../headers/Damagable.h"

bool Damagable::canBeDamaged() const
{
	return true;
}

Damagable::Damagable(int startingHealth) : health(startingHealth)
{
}
