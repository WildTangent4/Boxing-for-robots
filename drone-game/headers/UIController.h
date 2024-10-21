#pragma once
#include <raylib.h>
#include <string>
class UIController {
	float UIClock= 0.0;
public:
	void renderUI(Camera3D& cam,int health);


};