#include "brick.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include <SDL3/SDL.h>
#include <string>

Brick::Brick(int health, int xpos, int ypos) {
	this->health = health;
	this->xpos = xpos;
	this->ypos = ypos;
	sprites.push_back("sprites/Brick1.png");
	sprites.push_back("sprites/Brick2.png");
	sprites.push_back("sprites/Brick3.png");
	sprites.push_back("sprites/Brick4.png");
	sprites.push_back("sprites/Brick5.png");
	auto* spriteComponent = addComponent<SpriteComponent>();
	auto* soundComponent = addComponent<SoundComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(), sprites[this->health-1]);
	soundComponent->loadSound();
	rect = spriteComponent->getRect();
	spriteComponent->setX(this->xpos);
	spriteComponent->setY(this->ypos);
}

void Brick::update(float deltaTime) {
	GameObject::update(deltaTime);
	for (auto it = Engine::keyEvents.begin(); it != Engine::keyEvents.end(); ++it) {
		if (it->key.key == SDLK_LSHIFT) {
			hit(deltaTime);
		}
		if (it->key.key == SDLK_RSHIFT) {
			pos();
		}
	}
}

void Brick::hit(float deltaTime) {
	health -= 1;
	SpriteComponent* sprite = this->getComponent<SpriteComponent>();
	SoundComponent* sound = this->getComponent<SoundComponent>();
	sound->playSound("sounds/Brick_Break.wav");
	if (health >= 1) {
		sprite->loadSprite(Engine::instance().getRenderer(), sprites[health - 1]);
		sprite->setX(xpos);
		sprite->setY(ypos);
	}
	else {
		health = 0;
	}
	SDL_Log("health: %d", health);
	
	
}

void Brick::pos() {
	SDL_Log("Brick X: %f", rect->x);
	SDL_Log("Brick Y: %f", rect->y);
}