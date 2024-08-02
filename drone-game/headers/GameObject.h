#pragma once
class GameObject{
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
	const int maxSpeed = 100;
public:
	void applyForces() {
		// apply all forces to velocity, capping to max speed if appropriate
		
		// add forces to velocity
		
		// cap movement above maxSpeed

		// add velocity to position

		// check if new position instersects with an object
			
			// if true move this object to the outer edge of the collider
	}
	
};