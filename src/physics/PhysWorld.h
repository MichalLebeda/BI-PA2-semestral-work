//
// Created by michal on 3/11/20.
//

#ifndef SEMESTRAL_WORK_PHYSWORLD_H
#define SEMESTRAL_WORK_PHYSWORLD_H


#include <SDL2/SDL.h>
#include <vector>
#include "PhysBody.h"
#include "WorldContactListener.h"

using namespace std;

/**
 * "Simulated" world containing rectangular bodies
 */
class PhysWorld {
public:
    PhysWorld();

    ~PhysWorld();

    /**
     * @brief Step physical simulation by one unit, should be called every frame
     */
    void step();

    /**
     * @brief Add simulated body
     * @param body Body to add
     */
    void addBody(PhysBody *body);

    /**
     * @brief Get all simulated bodies (even static)
     * @return vector of simulated bodies
     */
    vector<PhysBody *> *getBodies();

    /**
     * @brief Get contact listener called when collision occur
     * @return Instance of WorldContactListener or nullptr if none set
     */
    WorldContactListener *getContactListener() const;

    /**
     * @brief Set contact listener to be called when collision occurs
     * @param contactListener WorldContactListener to be set
     */
    void setContactListener(WorldContactListener *contactListener);

    /**
     * @brief Remove all bodies returning true for isToBeRemoved();
     */
    void removeJunkBodies();

private:
    void resolveCollision(PhysBody *dynamicBodyA, PhysBody *bodyB);

    bool collide(PhysBody *bodyA, PhysBody *bodyB);

    vector<PhysBody *> bodies;

    SDL_Rect intersectionRect;

    WorldContactListener *contactListener = nullptr;
};


#endif //SEMESTRAL_WORK_PHYSWORLD_H
