#include "paddle.hpp"
#include "brick.hpp"
#include "ball.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include <box2d/box2d.h>
#include <SDL3/SDL_main.h>

int main(int argc, char** argv) {
    // Create the objects that make up our game, and start the run.
    Engine& engine = Engine::instance();
    World& world = World::instance();

    Scene scene;
    Paddle paddle;
    Brick brick1 = Brick(5, 750, 500);
    Brick brick2 = Brick(4, 850, 450);
    Brick brick3 = Brick(3, 950, 400);
    Brick brick4 = Brick(2, 1050, 350);
    Brick brick5 = Brick(1, 950, 300);
    Ball ball = Ball();

    scene.addObject(&brick1);
    scene.addObject(&brick2);
    scene.addObject(&brick3);
    scene.addObject(&brick4);
    scene.addObject(&brick5);
    scene.addObject(&paddle);
    scene.addObject(&ball);
    engine.setScene(&scene);
    engine.run();
    return 0;
}

