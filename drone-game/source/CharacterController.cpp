#include "../headers/CharacterController.h"

CharacterController::CharacterController(GameObject* player, Camera3D* cam)
{
	this->player = player;
	this->camera = cam;
}

void CharacterController::applyGameTick(std::vector<GameObject*> objects)
{
	applyInputs(objects);
	applyQueuedInputs();
}

void CharacterController::applyInputs(std::vector<GameObject*> objects)
{
	applyMoveInputsToPlayerObject();
	applyAttackInputs(objects);
	applyCameraInputs();
	applyJumpInputs();
}

void CharacterController::applyQueuedInputs()
{
}

void CharacterController::applyAttackInputs(std::vector<GameObject*> objects)
{
	//TODO:check that x time has passed since last attack to avoid spam
	if (IsKeyPressed(KEY_Q)) {
		//filter all objects to only objects that are within the correct distance
		//O(n)

		std::vector<GameObject*> nearObjects;
		Vector3 playerPos = this->player->pos;
		printf("detected %I64u objects\n", objects.size());
		std::copy_if(std::begin(objects), std::end(objects), std::back_inserter(nearObjects), [playerPos](GameObject* obj) {return Vector3Distance(playerPos, obj->pos) < 3; });//TODO make range specific to equipped weapon
		printf("detected %I64u obejcts in attack range\n", nearObjects.size());
		//filter to only object within the hurt box (2,4 rectangle on ground in front of player)
	}
}

void CharacterController::applyCameraInputs()
{
	if (IsWindowFocused()) {
		HideCursor();
		//rotate camera base on mouse
		float mouse_sensitivity = 0.003f;
		Vector2 mousePositionDelta = GetMouseDelta();
		SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
		CameraYaw(this->camera, -mousePositionDelta.x * mouse_sensitivity, false);
		CameraPitch(this->camera, -mousePositionDelta.y * mouse_sensitivity, false, false, false);

		//move camera based on WASD
		float camera_move_speed = 0.5;//default 0.5
		if (IsKeyDown(KEY_W)) CameraMoveForward(this->camera, camera_move_speed, true);
		if (IsKeyDown(KEY_A)) CameraMoveRight(this->camera, -camera_move_speed, true);
		if (IsKeyDown(KEY_S)) CameraMoveForward(this->camera, -camera_move_speed, true);
		if (IsKeyDown(KEY_D)) CameraMoveRight(this->camera, camera_move_speed, true);
	}
	else {
		ShowCursor();
	}
}

void CharacterController::applyMoveInputsToPlayerObject()
{
	//double currentCameraRotation = this->camera.
	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D)) {
		this->player->pos = { this->camera->position.x, this->camera->position.y - 2,this->camera->position.z }; //update player position (accounting for player height)
	}
}

void CharacterController::applyJumpInputs()
{
}
