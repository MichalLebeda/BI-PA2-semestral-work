//
// Created by michal on 3/11/20.
//

#include "PhysicalEntity.h"
#include "../physics/PhysWorld.h"
#include <iostream>

PhysicalEntity::PhysicalEntity(TextureRegion *region, int x, int y, int bodyWidth, int bodyHeight, bool dynamic,
                               PhysWorld *world) {
    sprite = new Sprite(region);

    createBody(x, y, bodyWidth, bodyHeight, dynamic);

    world->addBody(body);
}

PhysicalEntity::PhysicalEntity(TextureRegion *region, PhysBody *body) {
    sprite = new Sprite(region);
    this->body = body;
}

PhysicalEntity::PhysicalEntity(TextureRegion *region) {
    sprite = new Sprite(region);
}

PhysicalEntity::~PhysicalEntity() {
    delete sprite;
}

void PhysicalEntity::render(CameraRenderer *renderer) {
    updateSpritePosition();
    renderer->renderLaterDepthSorted(sprite->getRegion(), *sprite->getRect());
}

void PhysicalEntity::createBody(int x, int y, int width, int height, bool dynamic) {
    body = new PhysBody(x, y, width, height);
    body->setDynamic(dynamic);
}

PhysBody *PhysicalEntity::getBody() {
    return body;
}

void PhysicalEntity::setSpriteOffset(int xOffset, int yOffset) {
    this->spriteOffsetX = xOffset;
    this->spriteOffsetY = yOffset;
}

void PhysicalEntity::setSpriteOffsetX(int xOffset) {
    this->spriteOffsetX = xOffset;
}

void PhysicalEntity::setSpriteOffsetY(int yOffset) {
    this->spriteOffsetY = yOffset;
}

void PhysicalEntity::alignSpriteCenter() {
    setSpriteOffset(-sprite->getWidth() / 2,
                    -sprite->getHeight() / 2);
}

void PhysicalEntity::alignSpriteTopCenter() {
    setSpriteOffset(-sprite->getWidth() / 2,
                    -sprite->getHeight());
}

void PhysicalEntity::updateSpritePosition() {
    if (positionDirty) {
        sprite->setPosition(body->getCenterX() + spriteOffsetX,
                            body->getCenterY() + spriteOffsetY);

        if (!body->isDynamic()) {
            positionDirty = false;
        }
    }
}
