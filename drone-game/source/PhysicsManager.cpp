#include "../headers/PhysicsManager.h"
void PhysicsManager::physicsLoop() {
	while (gameIsRunning) {
		if (!physicsPaused) {
			runTickForAllObjects();
		}
	}
}

void PhysicsManager::runTickForAllObjects() {
	for each (GameObject x in objects)//note: if you ever have a bug where positions are not correctly updating on each physics tick, check if objects are stored and accessed by reference here
	{
		applyTick(x);
	}
}

void PhysicsManager::applyTick(GameObject obj) {
	printf("applying physics ticks to objects IS NOT IMPLEMENTED");
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
void PhysicsManager::addObject(GameObject* obj)
{
	this->objects.push_back(obj)
}
/*
PhysicsManager::addObject(GameObject obj) {
	objects.push_back(obj);
}
*/