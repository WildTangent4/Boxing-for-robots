#pragma once
#include "GameObject.h"
#include <rcamera.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <raymath.h>
class CharacterController {
public:
	CharacterController(GameObject* player, Camera3D* cam);
	void applyGameTick(std::vector<GameObject*> objects);
private:
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
	std::vector<GameObject*> getTargetableObjects(std::vector<GameObject*> objects, float range);

	bool isInView(GameObject*);

	//rotates point about origin
	Vector2 applyRotation(float angle, Vector2 point);
};