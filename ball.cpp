#include "ball.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include <SDL3/SDL.h>
#include "brick.hpp"

Ball::Ball() {
	float x = 965;
	float y = 800;
	auto* spriteComponent = addComponent<SpriteComponent>();
	auto* transformComponent = addComponent<TransformComponent>();
	transformComponent->setupTransform(pps, x, y);
	spriteComponent->loadSprite(Engine::instance().getRenderer(), "sprites/Ball.png");
	rect = spriteComponent->getRect();
	spriteComponent->setX(x);
	spriteComponent->setY(y);
	spriteComponent->setH(32);
	spriteComponent->setW(32);
	transformComponent->initMove();
}

void Ball::update(float deltaTime) {
	GameObject::update(deltaTime);
	handleCollision(deltaTime);
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

void Ball::handleCollision(float dt) {
	auto& objects = Engine::instance().scene->getObjects();
	auto* transformComponent = getComponent<TransformComponent>();
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
				if (std::find(colliding.begin(), colliding.end(), objects[i].get()) == colliding.end()) {
					if (Brick* brick = dynamic_cast<Brick*>(objects[i].get())) {
						brick->hit();
						transformComponent->bounce(dt);
					}
					else {
						transformComponent->bounce(dt);
					}
					colliding.push_back(objects[i].get());
				}
			}
			else if (std::find(colliding.begin(), colliding.end(), objects[i].get()) != colliding.end()){
				colliding.erase(std::find(colliding.begin(), colliding.end(), objects[i].get()));
			}
		}
		
	}
	
}