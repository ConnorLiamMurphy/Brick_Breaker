#include "title.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include <SDL3/SDL.h>

Title::Title()
{
   auto* spriteComponent = addComponent<SpriteComponent>();
   spriteComponent->loadSprite(Engine::instance().getRenderer(), "sprites/title_screen.png");
   titleRect = spriteComponent->getRect();

   spriteComponent->setX(0);
   spriteComponent->setY(0);
   titleRect->w = 1920;
   titleRect->h = 1080;

}

void Title::update(float deltaTime) 
{
        GameObject::update(deltaTime);
                for (auto it = Engine::keyEvents.begin(); it != Engine::keyEvents.end(); ++it) {
                        if (it->key.key == SDLK_SPACE) 
			{
                           titleRect->x -= 50000000;
                        }
                }
}
