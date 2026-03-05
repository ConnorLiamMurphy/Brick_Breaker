#include "ball.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include <SDL3/SDL.h>
#include "brick.hpp"

Ball::Ball() {
	float x = 965;
	float y = 1100;
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
					float left = ox2 - rect->x;
					float right = x2 - oRect->x;
					float top = oy2 - rect->y;
					float bottom = y2 - oRect->y;
					float lr = std::min(left, right);
					float bt = std::min(top, bottom);
					float min = std::min(lr, bt);
					Vector2d normal;
					if (min == left) {
						normal = Vector2d(1, 0);
						SDL_Log("left");
					}
					else if (min == right) {
						normal = Vector2d(-1, 0);
						SDL_Log("right");
					}
					else if (min == bottom) {
						normal = Vector2d(0, -1);
						SDL_Log("bottom");
					}
					else if (min == top) {
						normal = Vector2d(0, 1);
						SDL_Log("top");
					}
					if (Brick* brick = dynamic_cast<Brick*>(objects[i].get())) {
						brick->hit();
						transformComponent->bounce(dt, normal);
					}
					else {
						transformComponent->bounce(dt, normal);
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