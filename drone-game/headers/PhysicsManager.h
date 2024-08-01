#pragma once
#include <iostream>
#include <raylib.h>
#include <thread>
#include <vector>
#include "GameObject.h"
class PhysicsManager {
	bool physicsPaused = false;
	std::vector<GameObject> Objects;

	void physicsLoop() {
		printf("hello world");
	}

public:
	PhysicsManager() {
		//temporary constructor to ensure that error is not caused by uninitialised vector
		GameObject testObj = GameObject();
		Objects.push_back(testObj);
	}

	void simulate() {
		std::thread physicsThread = std::thread(&PhysicsManager::physicsLoop,this);//,std::ref(physicsPaused),std::ref(Objects));
		physicsThread.join();//rejoins thread once it completes execution (shouldnt happen while game is running)
	
	}
};