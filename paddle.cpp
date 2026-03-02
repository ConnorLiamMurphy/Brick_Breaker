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

    // Create body, send to physics world to get body id
    b2BodyDef bd = b2DefaultBodyDef();
    bd.type = b2_dynamicBody;
    bd.position = {950/PPM, (WINDOW_H - 850)/PPM};
    this->body = World::instance().createBody(bd);

    // Need to translate to physics engine lengths
    b2Polygon box = b2MakeBox(32,16);
    b2ShapeDef sd = b2DefaultShapeDef();
    sd.density = 10.0f;
    sd.material.restitution = 0.0f;
    sd.material.friction = 0.0f;
    b2CreatePolygonShape(body, &sd, &box);

}

void Paddle::update(float deltaTime) {
	GameObject::update(deltaTime);
		for (auto it = Engine::keyEvents.begin(); it != Engine::keyEvents.end(); ++it) {
			if (it->key.key == SDLK_A || it->key.key == SDLK_LEFT) {
				b2Vec2 move = {10.0f, 0.0f};
                b2Body_ApplyLinearImpulseToCenter(body, move, false);
                //left(deltaTime);
			}
			if (it->key.key == SDLK_D || it->key.key == SDLK_RIGHT) {
				b2Vec2 move = {-10.0f, 0.0f};
                b2Body_ApplyLinearImpulseToCenter(body, move, false);
                //right(deltaTime);
            }
            /*if (it->key.key != SDLK_A || it->key.key != SDLK_LEFT || it->key.key != SDLK_D || it->key.key != SDLK_RIGHT) {
                b2Vec2 move = {0.0f, 0.0f};
                b2Body_SetLinearVelocity(body, move);
            }*/
        }
        pos();
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
    b2Vec2 pos = b2Body_GetPosition(this->body);
    int cx = toPixX(pos.x);
    int cy = toPixY(pos.y);
    this->rect->x = cx;
    this->rect->y = cy;
	SDL_Log("paddle X: %f", rect->x);
	SDL_Log("paddle Y: %f", rect->y);
}
