//
// Created by michal on 3/11/20.
//

#include "PhysWorld.h"
#include <iostream>

using namespace std;

PhysWorld::PhysWorld() {

}

PhysWorld::~PhysWorld() {
    for (auto it:bodies) {
        delete it;
    }
}

void PhysWorld::step() {
    PhysBody *bodyA;
    PhysBody *bodyB;
    for (size_t i = 0; i < bodies.size(); i++) {
        bodyA = bodies.at(i);
        if (bodyA->isDynamic()) {
            bodyA->applyVelocity();
            for (size_t j = 0; j < bodies.size(); j++) {
                bodyB = bodies.at(j);
                if (bodyA != bodyB && collide(bodyA, bodyB)) {
                    resolveCollision(bodyA, bodyB);
                    if (contactListener != nullptr) {
                        contactListener->onContact(bodyA, bodyB);
                    }
                }
            }
        }
    }
}

bool PhysWorld::collide(PhysBody *bodyA, PhysBody *bodyB) {
    return SDL_IntersectRect(bodyA->getShape(), bodyB->getShape(), &intersectionRect) == SDL_TRUE;
}

void PhysWorld::addBody(PhysBody *body) {
    bodies.push_back(body);
}

void PhysWorld::resolveCollision(PhysBody *dynamicBodyA, PhysBody *bodyB) {
    SDL_Rect *a = dynamicBodyA->getShape();
    SDL_Rect *oldA = dynamicBodyA->getOldShape();
    SDL_Rect *b = bodyB->getShape();

    if (dynamicBodyA->isSensor() || bodyB->isSensor()) {
        return;
    }

    if (a->y <= b->y + b->h && oldA->y >= b->y + b->h) {
        dynamicBodyA->setBottom(b);
    } else if (a->y + a->h >= b->y && oldA->y + oldA->h <= b->y) {
        dynamicBodyA->setTop(b);
    } else if (a->x + a->w >= b->x && oldA->x + oldA->w <= b->x) {
        dynamicBodyA->setLeft(b);
    } else if (a->x <= b->x + b->w && oldA->x >= b->x + b->w) {
        dynamicBodyA->setRight(b);
    }
}

vector<PhysBody *> *PhysWorld::getBodies() {
    return &bodies;
}

WorldContactListener *PhysWorld::getContactListener() const {
    return contactListener;
}

void PhysWorld::setContactListener(WorldContactListener *contactListener) {
    if (this->contactListener != nullptr) {
        delete contactListener;//smazeme stary
    }

    this->contactListener = contactListener;
}

void PhysWorld::removeJunkBodies() {
    for (size_t i = 0; i < bodies.size(); i++) {
        PhysBody *body = bodies.at(i);
        if (body->isToBeRemoved()) {
            delete body;
            bodies.erase(bodies.begin() + i);
            i--;
        }
    }
}
