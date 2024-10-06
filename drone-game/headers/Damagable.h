#pragma once

class Damagable {
public:
	int health;
	bool canBeDamaged() const;
	//deal the specified amount of damage, returns true if enemy was defeated
	virtual bool damage(int damage) = 0;
	Damagable(int startingHealth);
};