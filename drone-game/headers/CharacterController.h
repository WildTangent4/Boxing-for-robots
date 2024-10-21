#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include <rcamera.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <raymath.h>


class CharacterController {
public:
	CharacterController(GameObject* player, Camera3D* cam);
	void applyGameTick(std::vector<GameObject*> objects);
	void renderArms(Camera3D &camera);

	void setPosture(float newPosture);
	float getPosture();
	bool isPunching();
	bool isBlocking();
private:

	enum armState {
		BLOCK = 1,
		REST = 2,
		PUNCH = 3,
		RETURNING_TO_BLOCK = 4
	};

	float punchCooldown = 0.1;
	float timeSinceLastLeftPunch = INFINITY;
	float timeSinceLastRightPunch = INFINITY;
	float posture = 0; 

	armState leftArmState = REST;
	armState rightArmState = REST;

	RenderTexture2D canvas = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

	Texture2D r_block = LoadTexture("../../../resources/R_block.png");
	Texture2D r_rest = LoadTexture("../../../resources/R_rest.png");
	Texture2D r_punch = LoadTexture("../../../resources/R_punch.png");

	Texture2D l_block = LoadTexture("../../../resources/L_block.png");
	Texture2D l_rest = LoadTexture("../../../resources/L_rest.png");
	Texture2D l_punch = LoadTexture("../../../resources/L_punch.png");

	float lastXangle = 0;
	float lastYangle = 0;

	float moveSpeed = 0.2;
	float playerHeight = 2;

	GameObject* player;
	Camera3D* camera;
	double coyoteTime = 0;
	/// <summary>
	/// takes all currently pressed inputs and applies them to this controllers character module
	/// </summary>
	void applyInputs(std::vector<GameObject*> objects);
	/// <summary>
	/// applies all queued jump inputs that are less than coyote time old
	/// </summary>
	void applyQueuedInputs();
	void applyAttackInputs(std::vector<GameObject*> objects);
	void applyCameraInputs();
	void applyMoveInputsToPlayerObject();
	void applyJumpInputs();

	std::vector<GameObject*> getNearObjects(std::vector<GameObject*> objects,float range);
	std::vector<Enemy*> getTargetableObjects(std::vector<GameObject*> objects, float range);

	static bool isInView(GameObject* object, GameObject* player, Camera3D* camera);

	//rotates point about origin NOTE: this function violates SRP, should make a math class to contain methods like this
	static Vector2 applyRotation(float angle, Vector2 point);
};