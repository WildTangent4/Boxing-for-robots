#pragma once
#include <iostream>
#include <raylib.h>
#include <thread>
#include <vector>
#include "GameObject.h"
class PhysicsManager {
	//note: using atomic means custom move, copy and delete constructors need to be created
	std::atomic<bool> physicsPaused = false;
	std::atomic<bool> gameIsRunning = true;
	std::vector<GameObject> Objects;

	void physicsLoop() {
		while (gameIsRunning) {
			if (!physicsPaused) {
				runTickForAllObjects();
			}
		}
	}

	void runTickForAllObjects() {
		for each (GameObject x in Objects)//NOTE TO SELF CHECK IF THIS IS BY REFERENCE
		{
			applyTick(x);
		}
	}

	void applyTick(GameObject obj) {
		printf("applying physics ticks to objects IS NOT IMPLEMENTED");
	}

public:

	PhysicsManager() {}

	void simulate() {
		std::thread physicsThread = std::thread(&PhysicsManager::physicsLoop,this);
		physicsThread.detach();
	}

	void endSimulation() {
		physicsPaused = true;
		gameIsRunning = false;
		Objects.clear();
	}

	~PhysicsManager() {
		endSimulation();
	}

	PhysicsManager(const PhysicsManager&) = delete;
	PhysicsManager& operator=(const PhysicsManager&) = delete;

};