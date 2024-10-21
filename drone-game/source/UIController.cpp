#include "../headers/UIController.h"

void UIController::renderUI(Camera3D& cam,int health)
{
	this->UIClock = this->UIClock + GetFrameTime();

	if (health > 0) {
		DrawText(std::to_string(health).c_str(), 50, 50, 30, BLACK);
	}
	else {
		int textHeight = 50;
		std::string text = "YOU DIED ";
		int textLength = text.size();
		int textWidth = textLength * (textHeight / 7) * 5; //font is 7x5 max
		for (int rowYstart = -((int)this->UIClock % textHeight); rowYstart <= GetScreenHeight(); rowYstart = rowYstart + textHeight) {
			for (int repeatStartPosX = -((int)this->UIClock % textWidth); repeatStartPosX < GetScreenWidth(); repeatStartPosX = repeatStartPosX + textWidth) {
				DrawText(text.c_str(), repeatStartPosX, rowYstart, textHeight, BLACK);
			}
		}
		
	}

}
