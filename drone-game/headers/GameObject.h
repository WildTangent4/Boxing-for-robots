#pragma once

class GameObject{
public:
	const int maxSpeed = 100;
	int direction = 0;
	struct position {
		int x = 0;
		int y = 0;
	};
	struct forceOnBody {
		int x = 0;
		int y = 0;
	};
	struct velocity {
		int x = 0;
		int y = 0;
	};
	void applyForces();
	GameObject();//(position startPosition, PhysicsManager& physicsSystem);
	
};