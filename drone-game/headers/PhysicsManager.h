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
		for each (GameObject x in Objects)//note: if you ever have a bug where positions are not correctly updating on each physics tick, check if objects are stored and accessed by reference here
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