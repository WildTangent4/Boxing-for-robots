#pragma once
#include <vector>
struct SpriteSet {
	Texture2D rest;
	std::vector<Texture2D> moveAnim;
	Texture2D block;
	Texture2D punch_light;
	Texture2D punch_heavy;
	Texture2D hit;
};