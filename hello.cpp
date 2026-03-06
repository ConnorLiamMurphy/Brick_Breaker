#include "paddle.hpp"
#include "brick.hpp"
#include "ball.hpp"
#include "wall.hpp"
#include "engine.hpp"
#include "title.hpp"
#include "game_objects.hpp"
#include <SDL3/SDL_main.h>

int main(int argc, char** argv) {
    // Create the objects that make up our game, and start the run.
    Engine& engine = Engine::instance();

    Scene scene;
    
    scene.addObject(std::make_unique<Wall>(12, 1000, 638, 200));
    scene.addObject(std::make_unique<Wall>(12, 1000, 1350, 200));
    scene.addObject(std::make_unique<Wall>(726, 12, 637, 200));
    scene.addObject(std::make_unique<Ball>());
    scene.addObject(std::make_unique<Paddle>());
    int pos = 850;
    for (int i = 1; i <= 5; ++i) {
        scene.addObject(std::make_unique<Brick>(i, pos, 500));
        pos += 64;
    }

    scene.addObject(std::make_unique<Title>());


    engine.setScene(&scene);
    engine.run();
    return 0;
}

