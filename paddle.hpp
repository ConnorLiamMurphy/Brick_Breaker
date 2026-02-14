#ifndef     __HPP_PADDLE__
#define		__HPP_PADDLE__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

class Paddle: public GameObject {
public:
	Paddle();
	void left(float);
	void right(float);
	void pos();
	void update(float deltaTime) override;
private:
	SDL_FRect* rect;
	float pps = 3.0;
};




#endif 
