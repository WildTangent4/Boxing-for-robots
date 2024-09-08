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
		std::vector<GameObject*> near_enemies = getNearObjects(objects, 2);//change to attackrange
		isInView(this->player);
		//filter all objects to only objects that are within the correct distance
		//O(n)

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

std::vector<GameObject*> CharacterController::getNearObjects(std::vector<GameObject*> objects,float range)
{

	std::vector<GameObject*> nearObjects;
	Vector3 playerPos = this->player->pos;
	std::copy_if(std::begin(objects), std::end(objects), std::back_inserter(nearObjects), [playerPos,range](GameObject* obj) {return Vector3Distance(playerPos, obj->pos) < range; });//TODO make range specific to equipped weapon
	printf("detected %I64u obejcts in range\n", nearObjects.size());
	return nearObjects;
}

std::vector<GameObject*> CharacterController::getTargetableObjects(std::vector<GameObject*> objects, float range)
{

	std::vector<GameObject*> nearObjects;
	Vector3 playerPos = this->player->pos;
	std::copy_if(std::begin(objects), std::end(objects), std::back_inserter(nearObjects), [playerPos, range](GameObject* obj) {return Vector3Distance(playerPos, obj->pos) < range; });//TODO make range specific to equipped weapon
	printf("detected %I64u obejcts in range\n", nearObjects.size());

	std::vector<GameObject*> targetedObjects;
	printf("copying \n");
	std::copy_if(std::begin(nearObjects), std::end(nearObjects), std::back_inserter(targetedObjects), [this](GameObject* obj) {return isInView(obj); });
	printf("detected %I64u obejcts in target box\n", targetedObjects.size());
	
	return nearObjects;
}

bool CharacterController::isInView(GameObject* object)
{
	printf("running isInView\n");
	Vector3 localObjectPos3D = Vector3Subtract(object->pos, this->player->pos);
	Vector2 localObjectPos2D = { localObjectPos3D.x,localObjectPos3D.z };
	Vector3 localTarget = Vector3Subtract(this->camera->target, this->player->pos);
	float targetAngle = atan2(localTarget.x, localTarget.z);

	printf("found angle, appling rotations\n");
	Vector2 hurtBoxNearLeft = applyRotation(targetAngle,{ -5, 0 });
	Vector2 hurtBoxNearRight = applyRotation(targetAngle, {5,0});
	Vector2 hurtBoxFarLeft = applyRotation(targetAngle, {-5,-5});
	Vector2 hurtBoxFarRight = applyRotation(targetAngle, {5,-5});

	printf("constructing hurtbox and checking collisions\n");
	std::vector<Vector2> hurtBox = { hurtBoxNearLeft, hurtBoxFarLeft, hurtBoxFarRight, hurtBoxNearRight, hurtBoxNearLeft };

	bool isInBox = CheckCollisionPointPoly(localObjectPos2D, (Vector2*)hurtBox.data(), 4);
	printf("isInBox value: %d\n",isInBox);

	return isInBox;
}

Vector2 CharacterController::applyRotation(float angle, Vector2 point)
{
	printf("running applyRotation\n");
	double rotationMatrix[2][2] = {
		{ cos(angle) , -sin(angle) },
		{ sin(angle) , cos(angle)  }
	};

	Vector2 rotatedPoint = {
		point.x * rotationMatrix[0][0] + point.y * rotationMatrix[0][1],
		point.x * rotationMatrix[1][0] + point.y * rotationMatrix[1][1]
	};

	printf("rotated a point\n");
	return rotatedPoint;
}


