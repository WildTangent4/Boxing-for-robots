#include "../headers/UIController.h"

void UIController::renderUI(Camera3D& cam,int health)
{
	DrawText(std::to_string(health).c_str(), 50, 50, 30, BLACK);

}
