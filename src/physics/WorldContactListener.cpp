//
// Created by michal on 3/17/20.
//

#include "WorldContactListener.h"
#include <iostream>

using namespace std;

bool WorldContactListener::isInContact(int identifier, PhysBody *bodyA, PhysBody *bodyB) const {
    return bodyA->getIdentifier() == identifier || bodyB->getIdentifier() == identifier;
}

PhysBody *WorldContactListener::getFromContact(int identifier, PhysBody *bodyA, PhysBody *bodyB) const {
    if (bodyA->getIdentifier() == identifier) {
        return bodyA;
    }

    if (bodyB->getIdentifier() == identifier) {
        return bodyB;
    }

    return nullptr;
}

