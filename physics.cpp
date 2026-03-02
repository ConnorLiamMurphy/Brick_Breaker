#include "physics.hpp"
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Hard coding values for game
static constexpr int   WINDOW_W     = 800;
static constexpr int   WINDOW_H     = 600;
static constexpr float PPM          = 50.0f;   // pixels per meter

static int toPixX(float x) { return static_cast<int>(x * PPM); }
static int toPixY(float y) { return static_cast<int>(WINDOW_H - y * PPM); }

World::World() { init(); }

b2BodyId* World::createBody(b2BodyDef bd);
{
    b2BodyId body = b2CreateBody(world, &bd);
    return body;
}

bool World::init() {
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 1.0f};
    this->world = b2CreateWorld(&worldDef);

    return true;
}

void World::shutdown() {
    b2DestroyWorld(this->world);
    return;
}


