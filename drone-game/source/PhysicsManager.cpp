#include "../headers/PhysicsManager.h"
void PhysicsManager::physicsLoop() {
	while (gameIsRunning) {
		if (!physicsPaused) {
			runTickForAllObjects();
		}
	}
}

void PhysicsManager::runTickForAllObjects() {
	this->previous_tick_end = std::chrono::high_resolution_clock::now();
	double delta = std::chrono::duration<double,std::milli>(this->previous_tick_end-this->previous_tick_start).count();
	this->previous_tick_start = std::chrono::high_resolution_clock::now();
	for (GameObject* x : this->objects)//note: if you ever have a bug where positions are not correctly updating on each physics tick, check if objects are stored and accessed by reference here
	{
		applyTick(x,delta);
	}
}

void PhysicsManager::applyTick(GameObject* obj,double delta) {
	Vector3 start_pos = obj->pos;
	obj->applyForces(delta);
	Vector3 end_pos = obj->pos;
	//TODO: check if line between start and end intersects with any other objects and halt the movement if so
}

void PhysicsManager::simulate() {
	std::thread physicsThread = std::thread(&PhysicsManager::physicsLoop, this);
	physicsThread.detach();
}

void PhysicsManager::endSimulation() {
	physicsPaused = true;
	gameIsRunning = false;
	objects.clear();
}

PhysicsManager::PhysicsManager() {}

PhysicsManager::~PhysicsManager() {
	endSimulation();
}
void PhysicsManager::addObject(GameObject& obj)
{
	this->objects.push_back(&obj);
}
/*
PhysicsManager::addObject(GameObject obj) {
	objects.push_back(obj);
}
*/