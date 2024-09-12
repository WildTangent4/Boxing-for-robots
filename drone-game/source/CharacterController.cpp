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
		std::vector<Enemy*> targets = getTargetableObjects(objects,5);
		for (Enemy* target : targets) {
			target->Damage(1);
		}
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
		float camera_move_speed = 0.2;//default 0.5
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

std::vector<Enemy*> CharacterController::getTargetableObjects(std::vector<GameObject*> objects, float range)
{
	//todo:rename enemy to something like "damagable" and have the enemy class inherit from that (this lets you have destructible scenery)
	std::vector<Enemy*> enemies;
	Vector3 playerPos = this->player->pos;
	//std::copy_if(std::begin(objects), std::end(objects), std::back_inserter(enemies), [](GameObject* obj) {return obj->canBeDamaged; });//TODO make range specific to equipped weapon
	for (GameObject* obj : objects) {
		//printf("found an object", enemies.size());
		if (obj->canBeDamaged()) {
			enemies.push_back(dynamic_cast<Enemy*>(obj));
		}
	}
	//printf("detected %I64u enemies in play\n", enemies.size());


	//std::vector<Enemy*> nearEnemies;
	//std::copy_if(std::begin(enemies), std::end(enemies), std::back_inserter(nearEnemies), [playerPos, range](Enemy* obj) {return Vector3Distance(playerPos, obj->pos) < range; });//TODO make range specific to equipped weapon
	//printf("detected %I64u enemies in range\n", nearEnemies.size());

	std::vector<Enemy*> targetedEnemies;
	//printf("copying \n");

	GameObject* player = this->player;
	Camera3D* camera = this->camera;
	std::copy_if(std::begin(enemies), std::end(enemies), std::back_inserter(targetedEnemies), [player,camera](Enemy* obj) {return isInView(obj,player,camera); });
	printf("detected %I64u enemies in target box\n", targetedEnemies.size());
	
	return targetedEnemies;
}

bool CharacterController::isInView(GameObject* object, GameObject* player, Camera3D* camera)
{
	//printf("running isInView\n");
	Vector3 localObjectPos3D = Vector3Subtract(object->pos, player->pos);
	Vector2 localObjectPos2D = { localObjectPos3D.x,localObjectPos3D.z };
	Vector3 localTarget = Vector3Subtract(camera->target, player->pos);
	double targetAngle = atan2(localTarget.x, localTarget.z);
	//ensure target angle covers 360 degree range
	printf("\n\n%f\n\n", targetAngle);

	printf("found angle, appling rotations\n");
	Vector2 hurtBoxNearLeft = applyRotation(targetAngle, { -5,0 });
	Vector2 hurtBoxNearRight = applyRotation(targetAngle, { 5,0 });
	Vector2 hurtBoxFarLeft = applyRotation(targetAngle, { -5,5 });
	Vector2 hurtBoxFarRight = applyRotation(targetAngle, { 5,5 });

	//shift box onto player position
	hurtBoxNearLeft = { player->pos.x + hurtBoxNearLeft.x, player->pos.z + hurtBoxNearLeft.y };
	hurtBoxNearRight = { player->pos.x + hurtBoxNearRight.x, player->pos.z + hurtBoxNearRight.y };
	hurtBoxFarLeft = { player->pos.x + hurtBoxFarLeft.x, player->pos.z + hurtBoxFarLeft.y };
	hurtBoxFarRight = { player->pos.x + hurtBoxFarRight.x, player->pos.z + hurtBoxFarRight.y };

	printf("constructing hurtbox and checking collisions\n");
	std::vector<Vector2> hurtBox = { hurtBoxNearLeft, hurtBoxFarLeft, hurtBoxFarRight, hurtBoxNearRight, hurtBoxNearLeft };

	bool isInBox = CheckCollisionPointPoly(localObjectPos2D, (Vector2*)hurtBox.data(), 4);
	printf("isInBox value: %d\n",isInBox);

	return isInBox;
}

Vector2 CharacterController::applyRotation(float angle, Vector2 point)
{
	//printf("running applyRotation\n");
	double rotationMatrix[2][2] = {
		{ cos(angle) , -sin(angle) },
		{ sin(angle) , cos(angle)  }
	};

	Vector2 rotatedPoint = {
		point.x * rotationMatrix[0][0] + point.y * rotationMatrix[0][1],
		point.x * rotationMatrix[1][0] + point.y * rotationMatrix[1][1]
	};

	//printf("rotated a point\n");
	return rotatedPoint;
}


