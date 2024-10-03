#include "..\headers\Enemy.h"

bool Enemy::canBeDamaged()
{
	return true;
}

Enemy::Enemy(int health, Vector3 position, SpriteSet sprites, Behaviour behaviourType) : GameObject(position, sprites.rest)
{
	this->health = health;
	this->sprites = sprites;
	this->AIType = behaviourType;
}

void Enemy::Damage(int amount)
{
	this->health = this->health - amount;
	this->currentState = STUNNED;
	this->texture = this->sprites.hit;
	this->stunTimeRemaining = 0.2;

	switch (this->AIType) {
	case Behaviour::AGGRESSIVE:
		this->aggressionLevel = 0.5;
		break;
	case Behaviour::BALANCED:
		this->aggressionLevel = 0;
		break;
	default:
		this->aggressionLevel = 0;
	}

	if (this->health<=0){
		this->active = false;
	}
}

void Enemy::RunAI(Behaviour type,GameObject* player)
{
	this->stunTimeRemaining = this->stunTimeRemaining - GetFrameTime();
	if (this->stunTimeRemaining <= 0) {
		if (this->currentState == State::STUNNED) {
			this->currentState = State::WAIT;
		}
		
		adjustAggression();
		this->currentState = findNextAction(type,player);
		this->texture = this->sprites.rest;
		applyState(player);
	}
	
}

void Enemy::adjustAggression()
{
	//include features like if player is moving towards enemy (i.e. looks like they might punch or has block lowered)
	this->aggressionLevel = this->aggressionLevel +
		((this->baseAggressionIncreaseRate)*GetFrameTime());
}

void Enemy::applyState(GameObject* target)
{
	switch (this->currentState)
	{
	case BLOCK:
		this->texture = this->sprites.block;
		break;
	case PUNCH:
		this->texture = this->sprites.punch_heavy;
		this->aggressionLevel = this->AIType == AGGRESSIVE ? 0.5 : 0;
		if (timeSinceLastPunch < punchLingerTimeS) {
			this->timeSinceLastPunch = this->timeSinceLastPunch + GetFrameTime();
		}
		else {
			this->punchCharge = 0;
			this->timeSinceLastPunch = 0;
		}
		break;
		//hit target
		//todo make hit function for player - probably worth creating a class "damagable" that enemy and player inherit from
	case PUSH:
		this->texture = this->sprites.moveAnim.at(0);//todo create play animation function
		//move towards player
		//todo move this into a function called move that takes into account things like floor height and pathing
		this->pos =
			Vector3Add(//add movement to position
				(Vector3Scale(//account for frame rate
					Vector3Scale(//apply move speed
						Vector3Normalize(//normalise distance to constant magnitude to get direction vector
							Vector3Subtract(
								target->pos,
								this->pos)
						),
						this->moveSpeed
					),
					GetFrameTime())),
				this->pos
			);
		break;
	case WAIT:
		this->texture = this->sprites.rest;
		break;
	case STUNNED:
		this->texture = this->sprites.hit;
		break;
	case RETREAT:
		this->texture = this->sprites.moveAnim.at(0);//todo create play animation function
		this->pos =
			Vector3Add(//add movement to position
				(Vector3Scale(//account for frame rate
					Vector3Scale(//apply move speed
						Vector3Normalize(//normalise distance to constant magnitude to get direction vector
							Vector3Subtract(
								this->pos,
								target->pos)
						),
						this->moveSpeed
					),
					GetFrameTime())),
				this->pos
			);
	case READY_PUNCH:
		this->punchCharge = this->punchCharge + GetFrameTime();
		int windUpFrames = this->sprites.punch_heavy_wind.size();
		float frameLength = 1.0 / windUpFrames;
		for (int frame = 0; frame < windUpFrames; frame++) {
			if (punchCharge > frame * frameLength) {
				this->texture = this->sprites.punch_heavy_wind.at(frame);
			}
		}
		break;
	}
}

Enemy::State Enemy::findNextAction(Behaviour type, GameObject* player)
{
	Vector3 playerPos = player->pos;

	if (this->currentState == State::STUNNED) {
		if (this->debugMode) { printf("state is STUNNED\n"); }
		return State::STUNNED;
	}

	//if player is in fighting range and a punch is charged, punch
	else if (Vector3Distance(playerPos, this->pos) < this->attackDist && this->punchCharge >= 1) {
		if (this->debugMode) { printf("state is PUNCH\n"); }
		return State::PUNCH;
	}

	//note the following if statements must be ordered from highest to lowest aggression level required

	//if player is visible but not in fighting range, approach
	if (Vector3Distance(playerPos, this->pos) < this->aggroDist && Vector3Distance(playerPos, this->pos) > this->attackDist && ! Vector3Distance(playerPos, this->pos) < this->attackDist &&  this->aggressionLevel > 0.4) {
		if (this->debugMode) { printf("state is PUSH\n"); }
		return State::PUSH;
	}
	
	//if the enemy is about to punch, lower block to give player time to react
	else if (Vector3Distance(playerPos, this->pos) < this->aggroDist && this->aggressionLevel > 0.6) {
		if (this->debugMode) { printf("state is READY_PUNCH (charge: %f)\n",this->punchCharge); }
		return State::READY_PUNCH;
	}
	//if player is in fighting range and aggression is low, block
	else if ((Vector3Distance(playerPos, this->pos) < this->aggroDist && this->aggressionLevel > 0.2)) {
		if (this->debugMode) { printf("state is BLOCK\n"); }
		return State::BLOCK;
	}
	//if player is in fighting range and aggression is very low, retreat
	else if (Vector3Distance(playerPos, this->pos) < this->aggroDist) {
		if (this->debugMode) { printf("state is RETREAT\n"); }
		return State::RETREAT;
	}
	//if player is out of aggro range and do nothing
	else {
		if (this->debugMode) { printf("state is WAIT\n"); }
		return State::WAIT;
	}
}


