#include "ball.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include "physics.hpp"
#include <SDL3/SDL.h>
#include <box2d/box2d.h>

Ball::Ball() {
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(), "sprites/Ball.png");
	rect = spriteComponent->getRect();
    
    // Create body, send to physics world to get body id
    b2BodyDef bd = b2DefaultBodyDef();
    bd.type = b2_dynamicBody;
    bd.position = {950/PPM, (WINDOW_H - 700)/PPM};
    this->body = World::instance().createBody(bd);

    b2Circle circle;
    circle.center = {0.0f, 0.0f};
    circle.radius = 0.25f;
    
    b2ShapeDef sd = b2DefaultShapeDef();
    sd.density = 1.0f;
    sd.material.friction = 0.0f;
    sd.material.restitution = 1.0f;
    b2CreateCircleShape(this->body, &sd, &circle);

	spriteComponent->setX(950);
	spriteComponent->setY(800);

    b2Body_ApplyLinearImpulseToCenter(body, {0.0f, 0.0f}, false);

}

void Ball::update(float deltaTime) {
	GameObject::update(deltaTime);
	/*for (auto it = Engine::keyEvents.begin(); it != Engine::keyEvents.end(); ++it) {
		if (it->key.key == SDLK_W) {
			pos();
		}
	}*/
    pos();
}


void Ball::pos() {
    b2Vec2 pos = b2Body_GetPosition(this->body);
    int cx = toPixX(pos.x);
    int cy = toPixY(pos.y);
	//SDL_Log("ball X: %f", cx);
	//SDL_Log("ball Y: %f", cy);
    rect->x = cx;
    rect->y = cy;
}
