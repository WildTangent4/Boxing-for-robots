#include "..\headers\Player.h"
#include "..\headers\CharacterController.h"

bool Player::damage(int amount)
{

	if (this->inputController->isBlocking()) {
		this->inputController->setPosture(0);
	}
	else {
		this->health = this->health - amount;
	}
	

	bool defeated = this->health <= 0;
	
	if (defeated) {
		this->obj->active = false;
		printf("player was defeated");
	}

	return defeated;
}

Player::Player(int health, Vector3 position,Camera3D& cam, GameObject& baseObject) : health(health), obj(&baseObject), cam(cam), inputController(new CharacterController(&baseObject,&cam))
{
}


bool Player::update(std::vector<GameObject*> objects)
{

	this->inputController->renderArms(this->cam);
	this->interfaceController.renderUI(this->cam, this->health);

	if (this->obj->active) {
		this->inputController->applyGameTick(objects);
	}

	return this->health <= 0;
}
