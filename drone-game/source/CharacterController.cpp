#include "../headers/CharacterController.h"

CharacterController::CharacterController(GameObject* player, Camera3D* cam)
{
	this->player = player;
	this->camera = cam;
}

void CharacterController::applyGameTick()
{
	apply_inputs();
	apply_queued_inputs();
}

void CharacterController::apply_inputs()
{
	applyMoveInputs();
	applyCameraInputs();
	applyJumpInputs();
}

void CharacterController::apply_queued_inputs()
{
}

void CharacterController::applyCameraInputs()
{
	UpdateCamera(this->camera, CAMERA_FIRST_PERSON);
}

void CharacterController::applyMoveInputs()
{
}

void CharacterController::applyJumpInputs()
{
}
