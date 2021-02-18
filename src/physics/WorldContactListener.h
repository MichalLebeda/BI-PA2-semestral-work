//
// Created by michal on 3/17/20.
//

#ifndef SEMESTRAL_WORK_WORLDCONTACTLISTENER_H
#define SEMESTRAL_WORK_WORLDCONTACTLISTENER_H


#include "PhysBody.h"

/**
 * Abstract class for handling contacts with helper methods
 */
class WorldContactListener {
public:

    /**
     * @brief Called when contact occurs
     * @param bodyA First body in contact
     * @param bodyB Second body in contact
     */
    virtual void onContact(PhysBody *bodyA, PhysBody *bodyB) = 0;

    /**
     * @brief Return whatever at least one of two bodies contain identifier
     * @param identifier Identifier we are looking for
     * @param bodyA Body to be searched for given identifier
     * @param bodyB Another body to be searched for given identifier
     * @return True if body was found false otherwise
     */
    bool isInContact(int identifier, PhysBody *bodyA, PhysBody *bodyB) const;

    /**
     * @brief Get body with given identifier from two bodies
     * @param identifier Identifier we are looking for
     * @param bodyA Body to be searched for given identifier
     * @param bodyB Another body to be searched for given identifier
     * @return Body with given identifier or nullptr
     */
    PhysBody *getFromContact(int identifier, PhysBody *bodyA, PhysBody *bodyB) const;

    virtual ~WorldContactListener() = default;

};


#endif //SEMESTRAL_WORK_WORLDCONTACTLISTENER_H
