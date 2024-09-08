#pragma once
#include <iostream>
#include <raylib.h>
#include <thread>
#include <vector>
#include <time.h>
#include <chrono>
#include "GameObject.h"
class PhysicsManager {
	//note: using atomic means custom move, copy and delete constructors need to be created
	std::atomic<bool> physicsPaused = false;
	std::atomic<bool> gameIsRunning = true;
	std::chrono::steady_clock::time_point previous_tick_start = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point previous_tick_end = std::chrono::high_resolution_clock::now();
	std::vector<GameObject*> objects;

	/// <summary>
	/// runs physics tick in a loop
	/// </summary>
	/// TODO: should account for physics tick length
	void physicsLoop();
	/// <summary>
	/// runs a physics tick for each object
	/// </summary>
	void runTickForAllObjects();
	/// <summary>
	/// adds forces to velocity, and velocity to position
	/// </summary>
	/// <param name="obj"></param>
	void applyTick(GameObject* obj, double delta);
public:
	PhysicsManager();
	/// <summary>
	/// begin physics simulation
	/// </summary>
	void simulate();
	/// <summary>
	/// stop physicis simulation NOTE: currently deletes all objects
	/// </summary>
	void endSimulation();
	~PhysicsManager();
	PhysicsManager(const PhysicsManager&) = delete;
	PhysicsManager& operator=(const PhysicsManager& manager) = delete;
	void addObject(GameObject*  obj);
	std::vector<GameObject*> getObjects();
};