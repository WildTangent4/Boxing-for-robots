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
	std::vector<GameObject> objects;

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
	void applyTick(GameObject obj);
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
	PhysicsManager& operator=(const PhysicsManager&) = delete;
	void addObject(GameObject * obj);
};