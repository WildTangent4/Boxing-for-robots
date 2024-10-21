#include "..\headers\Player.h"
#include "..\headers\CharacterController.h"

bool Player::damage(int amount)
{
	this->health = this->health - amount;

	this->inputController->setPosture(0);

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


void Player::update(std::vector<GameObject*> objects)
{
	

	this->inputController->renderArms(this->cam);
	this->interfaceController.renderUI(this->cam, this->health);

	if (this->obj->active) {
		this->inputController->applyGameTick(objects);
	}
}
