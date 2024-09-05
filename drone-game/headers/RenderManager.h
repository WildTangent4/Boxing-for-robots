#pragma once
#include "GameObject.h"
#include <vector>
#include "raylib.h"
class RenderManager
{
public:
	RenderManager(Camera3D* camera);
	~RenderManager();
	/// <summary>
	/// add an object to the list of objects to be rendered
	/// </summary>
	/// <param name="obj"></param>
	void addObject(GameObject& obj);
	/// <summary>
	/// renders all objects once (needs to be run in a loop)
	/// </summary>
	void render();
private:
	Camera3D* viewport;
	std::vector<GameObject*> objects;

};

