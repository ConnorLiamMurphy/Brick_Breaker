#include "paddle.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include <SDL3/SDL.h>

Paddle::Paddle() {
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(), "sprites/paddle.png");
	rect = spriteComponent->getRect();
	spriteComponent->setX(950);
	spriteComponent->setY(850);

}

void Paddle::update(float deltaTime) {
	GameObject::update(deltaTime);
		for (auto it = Engine::keyEvents.begin(); it != Engine::keyEvents.end(); ++it) {
			if (it->key.key == SDLK_A || it->key.key == SDLK_LEFT) {
				left(deltaTime);
			}
			if (it->key.key == SDLK_D || it->key.key == SDLK_RIGHT) {
				right(deltaTime);
			}
			if (it->key.key == SDLK_RSHIFT) {
				pos();
			}
		}
}

void Paddle::left(float dt) {
	if (rect->x - (pps * dt) > 650) {
		rect->x -= pps * dt;
	}
	else {
		rect->x = 650;
	}
	
}

void Paddle::right(float dt) {
	if (rect->x + (pps * dt) < 1250) {
		rect->x += pps * dt;
	}
	else {
		rect->x = 1250;
	}
}

void Paddle::pos() {
	SDL_Log("X: %f", rect->x);
	SDL_Log("Y: %f", rect->y);
}