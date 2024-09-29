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
				{ 
					obj->pos.x,
					obj->pos.y+obj->textureScale/2,//begin the texture at head height
					obj->pos.z
				},//draw billboard from the top of the object instead of from its feet
				obj->textureScale,
				WHITE);
		}
	}
}

RenderManager::~RenderManager() {
};