#include "../headers/CharacterController.h"

CharacterController::CharacterController(GameObject* player)
{
	this->player = player;
}

void CharacterController::applyGameTick()
{
	apply_inputs();
	apply_queued_inputs();
}

void CharacterController::apply_inputs()
{
}

void CharacterController::apply_queued_inputs()
{
}
