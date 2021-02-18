//
// Created by michal on 3/16/20.
//

#include "PhysWorldDebugRenderer.h"

PhysWorldDebugRenderer::PhysWorldDebugRenderer() {

}

void PhysWorldDebugRenderer::render(CameraRenderer *renderer) {
    vector<PhysBody *> *bodies = world->getBodies();

    for (auto it = bodies->begin(); it != bodies->end(); it++) {

        if ((*it)->isDynamic()) {
            renderer->setShapeColor(10, 255, 0, 80);
        } else {
            renderer->setShapeColor(255, 10, 0, 80);
        }

        switch ((*it)->getIdentifier()) {
            case STAIRS_DOWN:
                renderer->setShapeColor(159, 140, 112, 100);
                break;
            case STAIRS_UP:
                renderer->setShapeColor(200, 255, 40, 100);
                break;
        }

        (*it)->render(renderer);
    }

}

PhysWorld *PhysWorldDebugRenderer::getWorld() const {
    return world;
}

void PhysWorldDebugRenderer::setWorld(PhysWorld *world) {
    PhysWorldDebugRenderer::world = world;
}

