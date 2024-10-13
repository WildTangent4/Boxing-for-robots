#include "../headers/CharacterController.h"

CharacterController::CharacterController()
{
}

CharacterController::CharacterController(GameObject* player, Camera3D* cam)
{
	this->player = player;
	this->camera = cam;
}

void CharacterController::applyGameTick(std::vector<GameObject*> objects)
{
	applyInputs(objects);
	//applyQueuedInputs();
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
	//todo add a light attack if the shift key is pressed
	
	//handle right arm	
	if (IsKeyPressed(KEY_E) && this->timeSinceLastRightPunch>punchCooldown && (this->timeSinceLastLeftPunch > punchCooldown)) {
		this->timeSinceLastRightPunch = 0;
		this->rightArmState = PUNCH;
		std::vector<Enemy*> targets = getTargetableObjects(objects,5);
		for (Enemy* target : targets) {
			target->damage(1);
		}
	}
	else {	//end the last punch if the cooldown is complete
		this->timeSinceLastRightPunch += GetFrameTime();
		if (this->timeSinceLastRightPunch > punchCooldown) {
			this->rightArmState = REST;
		}
	}
	
	//handle left arm
	if (IsKeyPressed(KEY_Q) && this->timeSinceLastLeftPunch > punchCooldown && (this->timeSinceLastRightPunch > punchCooldown)) {
		this->timeSinceLastLeftPunch = 0;
		this->leftArmState = PUNCH;
		std::vector<Enemy*> targets = getTargetableObjects(objects, 5);
		for (Enemy* target : targets) {
			target->damage(1);
		}
	}
	else {	//end the last punch if the cooldown is complete
		this->timeSinceLastLeftPunch += GetFrameTime();
		if (this->timeSinceLastLeftPunch > punchCooldown) {
			this->leftArmState = REST;
		}
	}

	if (IsKeyDown(KEY_LEFT_SHIFT)) {
		if (this->timeSinceLastLeftPunch > punchCooldown) {
			this->leftArmState = this->posture >= 1 ? BLOCK : RETURNING_TO_BLOCK;
			if (this->posture < 1) {
				this->posture = this->posture + GetFrameTime();
			}
		}
		if (this->timeSinceLastRightPunch > punchCooldown) {
			this->rightArmState = this->posture>=1 ? BLOCK : RETURNING_TO_BLOCK;
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

void CharacterController::renderUI(Camera3D & camera)
{
	float screenHeight = GetScreenHeight();
	float screenWidth = GetScreenWidth();

	//calculate required scale
	float scaleX = screenWidth / this->r_block.width;
	float scaleY = screenHeight / this->r_block.height;

	//lerp UI pos to camera movement
	float bobDampingStrength = 0.1;
	float bobMovementScaleX = 70;
	float bobMovementScaleY = 20;
	float bobMovementFrequency = 0.5;
	float posY = 1-sin(sqrt(pow(player->pos.x,2)+pow(player->pos.y,2)) * bobMovementFrequency );
	
	//float currentYangle = atan2(,camera.target.y;
	float currentXangle = atan2(camera.target.x-player->pos.x,camera.target.y - player->pos.y);
	float camMovementX = currentXangle - lastXangle;

	float posX = Lerp(0,camMovementX,bobDampingStrength);
	

	Rectangle source = { 0,-screenHeight, screenWidth,-screenHeight };
	Rectangle dest = { posX* bobMovementScaleX,posY*bobMovementScaleY,screenWidth * scaleX ,screenHeight * scaleY };

	BeginTextureMode(this->canvas);
	ClearBackground(BLANK);
	//render left arm
	switch (leftArmState)
	{
	case BLOCK:
		DrawTexture(this->l_block, 0, 0, WHITE);
		break;
	case REST:
		DrawTexture(this->l_rest, 0, 0, WHITE);
		break;
	case PUNCH:
		DrawTexture(this->l_punch, 0,0 , WHITE);
		break;
	case RETURNING_TO_BLOCK:
		DrawTexture(this->l_block, 0, (1 / this->posture) * 10, WHITE);
		break;
	}

	//render right arm
	switch (rightArmState)
	{
	case BLOCK:
		DrawTexture(this->r_block, 0, 0, WHITE);
		break;
	case REST:
		DrawTexture(this->r_rest, 0, 0, WHITE);
		break;
	case PUNCH:
		DrawTexture(this->r_punch, 0, 0, WHITE);
		break;
	case RETURNING_TO_BLOCK:
		DrawTexture(this->r_block, 0, (1 / this->posture) * 10, WHITE);
		break;
	}
	EndTextureMode();

	DrawTexturePro(this->canvas.texture, source, dest, { 0,0 }, 0, WHITE);
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
			Enemy* enemy = dynamic_cast<Enemy*>(obj);
			if (enemy != nullptr) {
				enemies.push_back(enemy);
			}
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
	//get the angle from the player pos to where the camera is looking
	Vector3 localTarget = Vector3Subtract(camera->target, player->pos);
	double cameraAngle = atan2(localTarget.x, localTarget.z);

	//get the angle from the player to the enemy position
	Vector3 localObjectPos = Vector3Subtract(object->pos, player->pos);
	double targetAngle = atan2(localObjectPos.x, localObjectPos.z);
	
	//return if the enemy position is withoin the specified bounds (defined by hitConeAngle)
	double hitConeAngle = 15 * DEG2RAD;
	double angleDifference = cameraAngle - targetAngle;
	return (angleDifference<hitConeAngle && angleDifference>-hitConeAngle);
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


