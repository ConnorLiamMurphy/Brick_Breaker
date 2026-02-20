#include "ball.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include <SDL3/SDL.h>

Ball::Ball() {
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(), "sprites/Ball.png");
	rect = spriteComponent->getRect();
	spriteComponent->setX(950);
	spriteComponent->setY(800);

}

void Ball::update(float deltaTime) {
	GameObject::update(deltaTime);
	for (auto it = Engine::keyEvents.begin(); it != Engine::keyEvents.end(); ++it) {
		if (it->key.key == SDLK_RSHIFT) {
			pos();
		}
	}
}


void Ball::pos() {
	SDL_Log("ball X: %f", rect->x);
	SDL_Log("ball Y: %f", rect->y);
}