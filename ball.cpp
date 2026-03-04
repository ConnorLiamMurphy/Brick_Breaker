#include "ball.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include <SDL3/SDL.h>

Ball::Ball() {
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(), "sprites/Ball.png");
	rect = spriteComponent->getRect();
	spriteComponent->setX(965);
	spriteComponent->setY(800);
	spriteComponent->setH(32);
	spriteComponent->setW(32);

}

void Ball::update(float deltaTime) {
	GameObject::update(deltaTime);
	handleCollision();
	for (auto it = Engine::keyEvents.begin(); it != Engine::keyEvents.end(); ++it) {
		if (it->key.key == SDLK_RSHIFT) {
			pos();
		}
	}
	// need some sort of collision detection which calls the bounce function THEN the hit function of bricks


}


void Ball::pos() {
	SDL_Log("ball X: %f", rect->x);
	SDL_Log("ball Y: %f", rect->y);
}

void Ball::handleCollision() {
	auto& objects = Engine::instance().scene->getObjects();
	for (int i = 0; i < objects.size(); ++i) {
		if (objects[i].get() != this) {
			auto* sprite = objects[i].get()->getComponent<SpriteComponent>();
			SDL_FRect* oRect = sprite->getRect();
			int x2 = rect->x + rect->w;
			int ox2 = oRect->x + oRect->w;
			int y2 = rect->y + rect->h;
			int oy2 = oRect->y + oRect->h;
			if (((oRect->x <= rect->x && rect->x <= ox2) && (oRect->y <= rect->y && rect->y <= oy2))
				|| (oRect->x <= x2 && x2 <= ox2) && (oRect->y <= y2 && y2 <= oy2)) {
				SDL_Log("collision detected");
			}
		}
		
	}
	
}