#ifndef     __HPP_WALL__
#define     __HPP_WALL__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

class Wall : public GameObject {
    public:
        Wall(int w, int h, int xpos, int ypos);
        void pos();
        void update(float deltaTime) override;
    private:
        SDL_FRect* rect;
        int w;
        int h;
        int xpos;
        int ypos;
};

#endif
