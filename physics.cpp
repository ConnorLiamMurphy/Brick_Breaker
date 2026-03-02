#include "physics.hpp"
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

World::World() { init(); }

b2BodyId World::createBody(b2BodyDef bd) {
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


