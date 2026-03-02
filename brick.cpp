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

    // Create body, send to physics world to get body id
    b2BodyDef bd = b2DefaultBodyDef();
    bd.type = b2_staticBody;
    bd.position = {xpos/PPM, (WINDOW_H - ypos)/PPM};
    this->body = World::instance().createBody(bd);

    // Need to translate to physics engine lengths
    b2Polygon box = b2MakeBox(8,4);
    b2ShapeDef sd = b2DefaultShapeDef();
    sd.density = 1.0f;
    sd.material.restitution = 1.0f;
    sd.material.friction = 0.0f;
    b2CreatePolygonShape(body, &sd, &box);
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
    b2Vec2 pos = b2Body_GetPosition(this->body);
    int cx = toPixX(pos.x);
    int cy = toPixY(pos.y);
    this->rect->x = cx;
    this->rect->y = cy;
	SDL_Log("Brick X: %f", rect->x);
	SDL_Log("Brick Y: %f", rect->y);
}
