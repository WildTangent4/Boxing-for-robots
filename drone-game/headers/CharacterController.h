#pragma once
#include "GameObject.h"
class CharacterController {
public:
	CharacterController(GameObject* player);
	void applyGameTick();
private:
	GameObject* player;
	double coyoteTime = 0;
	/// <summary>
	/// takes all currently pressed inputs and applies them to this controllers character module
	/// </summary>
	void apply_inputs();
	/// <summary>
	/// applies all queued jump inputs that are less than coyote time old
	/// </summary>
	void apply_queued_inputs();
};