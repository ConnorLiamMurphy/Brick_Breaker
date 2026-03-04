#include "components.hpp"
#include "game_objects.hpp"

#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL.h>

GameObject* Component::getOwner() const {
    return owner;
}

void Component::setOwner(GameObject* go) {
    owner = go;
}

void SpriteComponent::setX(int x) {
    destRect.x = x;
}

void SpriteComponent::setY(int y) {
    destRect.y = y;
}

void SpriteComponent::setW(int w) {
    destRect.w = w;
}

void SpriteComponent::setH(int h) {
    destRect.h = h;
}



bool SpriteComponent::loadSprite(SDL_Renderer* renderer, char* path) {
    // Hard coding this for my sample game that uses 64x64 sprites.
    // You may need to adjust and/or have variable sizes.
    destRect = {0, 0, 64, 64};
    this->renderer = renderer;

    // Surfaces are software based, so slow.  But, we need them
    // when loading.
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        SDL_Log("IMG_Load Error: %s", SDL_GetError());
        return false;
    }

    // Now create a hardware-based renderer and delete the software one.
    sprite = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    return sprite != nullptr;
}

SpriteComponent::~SpriteComponent() {
    if (sprite) {
        SDL_DestroyTexture(sprite);
        sprite = nullptr;
    }
}

// Sometimes we might need to get the image.
SDL_Texture* SpriteComponent::getSprite() {
    return sprite;
}

void SpriteComponent::update(float) {
    SDL_RenderTexture(renderer, sprite, nullptr, &destRect);
}

// The destRect is where and how much of the image will be drawn.
SDL_FRect* SpriteComponent::getRect(){
    return &destRect;
}

bool TransformComponent::setupTransform(float pps, float x, float y) {
    this->pps = pps;
    this->position = Vector2d(x, y);
    this->currVelocity = Vector2d(0, 0);
    return true;
}

Vector2d TransformComponent::inputMove(float deltaTime, char input) {
    Vector2d velocity(0,0);
    if (input == 'l') {
        velocity.X = velocity.X - pps;
    } else if (input == 'r') {
        velocity.X = velocity.X + pps;
    } else if (input == 'u') {
        velocity.Y = velocity.Y - pps;
    } else if (input == 'd') {
        velocity.Y = velocity.Y + pps;
    }
    position = position + (velocity * deltaTime);
    if (position.X <= horizontalClamp.X) {
        position.X = horizontalClamp.X;
    }
    if (position.X >= horizontalClamp.Y) {
        position.X = horizontalClamp.Y;
    }
    return position;
}

void TransformComponent::update(float dt) {
    position = position + (currVelocity * dt);
    GameObject* transOwner = this->getOwner();
    auto* sprite = transOwner->getComponent<SpriteComponent>();
    SDL_FRect* rect = sprite->getRect();
    rect->x = position.X;
    rect->y = position.Y;
}

void TransformComponent::initMove() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);

    int randInt = dist(gen);
    SDL_Log("%d", randInt);
    if (randInt == 1) {
        currVelocity.X = currVelocity.X + pps;
    }
    else {
        currVelocity.X = currVelocity.X - pps;
    }
    currVelocity.Y = currVelocity.Y - pps;
}

void TransformComponent::bounce(float deltaTime) {
    //code for calculating new vector after colliding.
    //maybe add an operator function in the vector class to calculate new reflection vector (math.pdf slide 22)
}

void TransformComponent::setClamps(float x1, float x2, float ytop, float ybottom) {
    //possibly set defualt values for the edge of the screen
    horizontalClamp.X = x1;
    horizontalClamp.Y = x2;
    verticalClamp.X = ytop;
    verticalClamp.Y = ybottom;
}

SoundComponent::~SoundComponent() {
    ma_engine_uninit(&engine);
}

void SoundComponent::playSound(char* wav_file) {
    ma_engine_play_sound(&engine, wav_file, NULL);
}


bool SoundComponent::loadSound() {
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        return false;
    }
    return true;
}

