#include "..\headers\Player.h"
#include "..\headers\CharacterController.h"

bool Player::damage(int amount)
{
	this->health = this->health - amount;

	bool defeated = this->health <= 0;
	if (defeated) {
		printf("player was defeated");
	}
	return defeated;
}

Player::Player(int health, Vector3 position,Camera3D& cam, GameObject& baseObject) : health(health), obj(&baseObject), cam(cam), inputController(new CharacterController(&baseObject,&cam))
{
}


void Player::update(std::vector<GameObject*> objects)
{
	this->inputController->applyGameTick(objects);
	this->inputController->renderUI(this->cam);
	this->interfaceController.renderUI(this->cam);
}
