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
	applyMoveInputsToPlayerObject();
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

void CharacterController::applyMoveInputsToPlayerObject()
{
	//double currentCameraRotation = this->camera.
	if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D)) {
		this->player->pos = { this->camera->position.x, this->camera->position.y - 2,this->camera->position.z }; //update player position (accounting for player height)
	}
}

void CharacterController::applyJumpInputs()
{
}
