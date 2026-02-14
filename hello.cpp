#include "car.hpp"
#include "paddle.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include <SDL3/SDL_main.h>

int main(int argc, char** argv) {
    // Create the objects that make up our game, and start the run.
    Engine& engine = Engine::instance();

    Scene scene;
    Car car;
    Paddle paddle;

    scene.addObject(&paddle);
    scene.addObject(&car);
    engine.setScene(&scene);
    engine.run();
    return 0;
}

