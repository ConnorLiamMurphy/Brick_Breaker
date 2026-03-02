#ifndef         __HPP_PHYSICS__
#define         __HPP_PHYSICS__

#include <box2d/box2d.h>

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
        b2BodyId* createBody(b2BodyDef bd);

        b2WorldId* world;
};

#endif
