#ifndef     __HPP_BALL__
#define		__HPP_BALL__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

class Ball : public GameObject {
public:
	Ball();
	void pos();
	void update(float deltaTime) override;
private:
	SDL_FRect* rect;
	float pps = 2.0;
	void handleCollision(float);
	std::vector<GameObject*> colliding;
};




#endif 
