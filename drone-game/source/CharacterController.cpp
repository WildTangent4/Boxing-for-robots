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
	//rotate camera base on mouse
	float mouse_sensitivity = 0.003f;
	Vector2 mousePositionDelta = GetMouseDelta();
	CameraYaw(this->camera, -mousePositionDelta.x * mouse_sensitivity, false);
	CameraPitch(this->camera, -mousePositionDelta.y * mouse_sensitivity, false, false, false);

	//move camera based on WASD
	double camera_move_speed = 0.5;//default 0.5
	if (IsKeyDown(KEY_W)) CameraMoveForward(this->camera, camera_move_speed, true);
	if (IsKeyDown(KEY_A)) CameraMoveRight(this->camera, -camera_move_speed, true);
	if (IsKeyDown(KEY_S)) CameraMoveForward(this->camera, -camera_move_speed, true);
	if (IsKeyDown(KEY_D)) CameraMoveRight(this->camera, camera_move_speed, true);
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
