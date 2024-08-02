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

	void physicsLoop();
	void runTickForAllObjects();
	void applyTick(GameObject obj);
public:
	PhysicsManager();
	void simulate();
	void endSimulation();
	~PhysicsManager();
	PhysicsManager(const PhysicsManager&) = delete;
	PhysicsManager& operator=(const PhysicsManager&) = delete;
};