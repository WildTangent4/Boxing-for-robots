#pragma once
#include <vector>
struct SpriteSet {
	Texture2D rest;
	std::vector<Texture2D> moveAnim;
	float moveAnimLength = 1;
	Texture2D block;
	Texture2D punch_light;
	std::vector<Texture2D> punch_heavy_wind;
	Texture2D punch_heavy;
	Texture2D hit;
};