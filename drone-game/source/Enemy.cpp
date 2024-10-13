#include "..\headers\Enemy.h"

Enemy::Enemy(int health, Vector3 position, SpriteSet sprites, Behaviour behaviourType, bool debug) : GameObject(position, sprites.rest), Damagable(health), debugMode(debug)
{
	this->health = health;
	this->sprites = sprites;
	this->AIType = behaviourType;
}

bool Enemy::damage(int amount)
{
	this->Damagable::health = this->Damagable::health - amount;
	
	this->currentState = Enemy::STUNNED;
	this->GameObject::texture = this->sprites.hit;
	this->stunTimeRemaining = 0.2;

	switch (this->AIType) {
	case Enemy::Behaviour::AGGRESSIVE:
		this->aggressionLevel = 0.5;
		break;
	case Enemy::Behaviour::BALANCED:
		this->aggressionLevel = 0;
		break;
	default:
		this->aggressionLevel = 0;
	}
	
	bool defeated = this->Damagable::health <= 0;

	if (defeated){
		this->GameObject::active = false;
	}
	return defeated;
}

void Enemy::RunAI(Player* player)
{
	this->stunTimeRemaining = this->stunTimeRemaining - GetFrameTime();
	if (this->stunTimeRemaining <= 0) {
		if (this->currentState == State::STUNNED) {
			this->currentState = State::WAIT;
		}
		
		this->adjustAggression();
		this->currentState = findNextAction(this->AIType,player);
		this->GameObject::texture = this->sprites.rest;
		this->applyState(player);
	}
	
}

bool Enemy::canBeDamaged() const
{
	return Damagable::canBeDamaged();
}

void Enemy::adjustAggression()
{
	//include features like if player is moving towards enemy (i.e. looks like they might punch or has block lowered)
	this->aggressionLevel = this->aggressionLevel +
		((this->baseAggressionIncreaseRate)*GetFrameTime());
}

void Enemy::applyState(Player* target)
{
	switch (this->currentState)
	{
	case BLOCK:
		this->GameObject::texture = this->sprites.block;
		break;
	case PUNCH:
		this->GameObject::texture = this->sprites.punch_heavy;
		this->aggressionLevel = this->AIType == AGGRESSIVE ? 0.5 : 0;
		if (timeSinceLastPunch < punchLingerTimeS) {//if ensures that punch lingers for a set number of seconds
			this->timeSinceLastPunch = this->timeSinceLastPunch + GetFrameTime();
		}
		else {//run only on the first frame of the attack
			target->damage(1);
			this->punchCharge = 0;
			this->timeSinceLastPunch = 0;
		}
		break;
		//hit target
		//todo make hit function for player - probably worth creating a class "damagable" that enemy and player inherit from
	case PUSH:
		this->GameObject::texture = this->sprites.moveAnim.at(0);//todo create play animation function
		//move towards player
		//todo move this into a function called move that takes into account things like floor height and pathing
		this->GameObject::pos =
			Vector3Add(//add movement to position
				(Vector3Scale(//account for frame rate
					Vector3Scale(//apply move speed
						Vector3Normalize(//normalise distance to constant magnitude to get direction vector
							Vector3Subtract(
								target->obj->pos,
								this->GameObject::pos)
						),
						this->moveSpeed
					),
					GetFrameTime())),
				this->GameObject::pos
			);
		break;
	case WAIT:
		this->GameObject::texture = this->sprites.rest;
		break;
	case STUNNED:
		this->GameObject::texture = this->sprites.hit;
		break;
	case RETREAT:
		this->GameObject::texture = this->sprites.moveAnim.at(0);//todo create play animation function
		this->GameObject::pos =
			Vector3Add(//add movement to position
				(Vector3Scale(//account for frame rate
					Vector3Scale(//apply move speed
						Vector3Normalize(//normalise distance to constant magnitude to get direction vector
							Vector3Subtract(
								this->GameObject::pos,
								target->obj->pos)
						),
						this->moveSpeed
					),
					GetFrameTime())),
				this->GameObject::pos
			);
	case READY_PUNCH:
		this->punchCharge = this->punchCharge + GetFrameTime();
		int windUpFrames = this->sprites.punch_heavy_wind.size();
		float frameLength = 1.0 / windUpFrames;
		for (int frame = 0; frame < windUpFrames; frame++) {
			if (punchCharge > frame * frameLength) {
				this->GameObject::texture = this->sprites.punch_heavy_wind.at(frame);
			}
		}
		break;
	}
}

Enemy::State Enemy::findNextAction(Behaviour type, Player* player)
{
	Vector3 playerPos = player->obj->pos;

	if (this->currentState == State::STUNNED) {
		if (this->debugMode) { printf("state is STUNNED\n"); }
		return State::STUNNED;
	}

	//if player is in fighting range and a punch is charged, punch
	else if (Vector3Distance(playerPos, this->GameObject::pos) < this->attackDist && this->punchCharge >= 1) {
		if (this->debugMode) { printf("state is PUNCH\n"); }
		return State::PUNCH;
	}

	//note the following if statements must be ordered from highest to lowest aggression level required

	//if player is visible but not in fighting range, approach
	if (Vector3Distance(playerPos, this->GameObject::pos) < this->aggroDist && Vector3Distance(playerPos, this->GameObject::pos) > this->attackDist && ! Vector3Distance(playerPos, this->GameObject::pos) < this->attackDist &&  this->aggressionLevel > 0.4) {
		if (this->debugMode) { printf("state is PUSH\n"); }
		return State::PUSH;
	}
	
	//if the enemy is about to punch, lower block to give player time to react
	else if (Vector3Distance(playerPos, this->GameObject::pos) < this->aggroDist && this->aggressionLevel > 0.8) {
		if (this->debugMode) { printf("state is READY_PUNCH (charge: %f)\n",this->punchCharge); }
		return State::READY_PUNCH;
	}
	//if player is in fighting range and aggression is low, block
	else if ((Vector3Distance(playerPos, this->GameObject::pos) < this->aggroDist && this->aggressionLevel > 0.2)) {
		if (this->debugMode) { printf("state is BLOCK\n"); }
		return State::BLOCK;
	}
	//if player is in fighting range and aggression is very low, retreat
	else if (Vector3Distance(playerPos, this->GameObject::pos) < this->aggroDist) {
		if (this->debugMode) { printf("state is RETREAT\n"); }
		return State::RETREAT;
	}
	//if player is out of aggro range and do nothing
	else {
		if (this->debugMode) { printf("state is WAIT\n"); }
		return State::WAIT;
	}
}


