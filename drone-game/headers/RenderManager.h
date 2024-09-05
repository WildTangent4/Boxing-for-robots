#pragma once
#include "GameObject.h"
#include <vector>
class RenderManager
{
public:
	RenderManager();
	~RenderManager();
	
	void addObject(GameObject* obj);
private:
	std::vector<GameObject*> objects;

};

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}

