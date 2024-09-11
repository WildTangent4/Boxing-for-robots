#include "../headers/RenderManager.h"
void RenderManager::addObject(GameObject& obj)
{
	this->objects.push_back(&obj);
}

RenderManager::RenderManager(Camera3D* camera) {
	this->viewport = camera;
}

void RenderManager::render()
{
	
	for (const GameObject* obj : objects) {
		if (obj->active) {
			DrawBillboard(*(this->viewport),
				obj->texture,
				obj->pos,
				2,
				WHITE);
		}
	}
}

RenderManager::~RenderManager() {
};