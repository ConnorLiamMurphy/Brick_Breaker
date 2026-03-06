#ifndef __HPP_TITLE__
#define __HPP_TITLE__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

class Title: public GameObject
{
   public:
      Title();
      SDL_FRect* titleRect;
      SDL_FRect* deathRect;
      void update(float deltaTime) override;


};

#endif

