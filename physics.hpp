#ifndef         __HPP_PHYSICS__
#define         __HPP_PHYSICS__

#include <box2d/box2d.h>
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

class World {
    public:
        static World& instance(){
            static World instance;
            return instance;
        }

        World(const World&) = delete;
        World& operator=(const World&) = delete;

        World();
        ~World() = default;

        bool init();
        void shutdown();
        b2BodyId createBody(b2BodyDef bd);

        b2WorldId world;
};

#endif
