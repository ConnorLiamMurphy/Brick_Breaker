#ifndef     __HPP_BRICK__
#define		__HPP_BRICK__

#include "game_objects.hpp"
#include <SDL3/SDL.h>
#include <vector>

class Brick : public GameObject {
public:
	Brick(int health, int xpos, int ypos);
	void pos();
	void update(float deltaTime) override;
	void hit(float deltaTime);
private:
	SDL_FRect* rect;
	int health;
	std::vector<char*> sprites;
	int xpos;
	int ypos;
	
};




#endif 
