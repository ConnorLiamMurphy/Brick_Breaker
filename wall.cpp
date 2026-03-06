#include "wall.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include <SDL3/SDL.h>
#include <string>

Wall::Wall(int w, int h, int xpos, int ypos) {
    this->w = w;
    this->h = h;
    this->xpos = xpos;
    this->ypos = ypos;
    auto* spriteComponent = addComponent<SpriteComponent>();
    spriteComponent->loadSprite(Engine::instance().getRenderer(), "sprites/wall.png"); // replace temp with the sprite
    rect = spriteComponent->getRect();
    spriteComponent->setX(this->xpos);
    spriteComponent->setY(this->ypos);
    spriteComponent->setW(this->w);
    spriteComponent->setH(this->h);
}

void Wall::update(float deltaTime) {
    GameObject::update(deltaTime);
    for (auto it = Engine::keyEvents.begin(); it != Engine::keyEvents.end(); ++it) {
        if (it->key.key == SDLK_RSHIFT) {
            pos();
        }
    }
}

void Wall::pos() {
    SDL_Log("Wall X: %f", rect->x);
    SDL_Log("Wall Y: %f", rect->y);
    SDL_Log("Wall W: %f", rect->w);
    SDL_Log("Wall H: %f", rect->h);
}
