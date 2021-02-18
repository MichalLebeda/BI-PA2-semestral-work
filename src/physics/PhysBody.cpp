//
// Created by michal on 3/11/20.
//

#include "PhysBody.h"

PhysBody::PhysBody(int x, int y, int w, int h) {
    shape.x = x;
    shape.y = y;
    shape.w = w;
    shape.h = h;
}

PhysBody::~PhysBody() {
    if (item != nullptr) {
        delete item;
    }
}

SDL_Rect *PhysBody::getShape() {
    return &shape;
}

SDL_Rect *PhysBody::getOldShape() {
    return &oldShape;
}

void PhysBody::setDynamic(bool dynamic) {
    this->dynamic = dynamic;
}

bool PhysBody::isDynamic() const {
    return dynamic;
}

void PhysBody::render(CameraRenderer *renderer) {
    renderer->renderRect(&shape);
    renderer->renderRectLines(&shape);
}

int PhysBody::getX() const {
    return shape.x;
}

int PhysBody::getY() const {
    return shape.y;
}

int PhysBody::getCenterX() const {
    return shape.x + shape.w / 2;
}

int PhysBody::getCenterY() const {
    return shape.y + shape.h / 2;
}

int PhysBody::getWidth() const {
    return shape.w;
}

int PhysBody::getHeight() const {
    return shape.h;
}

void PhysBody::setVelocity(int velocityX, int velocityY) {
    this->velocityX = velocityX;
    this->velocityY = velocityY;
}

void PhysBody::setVelocityX(int velocityX) {
    this->lastStepVelocityX = velocityX;
    this->velocityX = velocityX;
}

void PhysBody::setVelocityY(int velocityY) {
    this->lastStepVelocityY = velocityY;
    this->velocityY = velocityY;
}

int PhysBody::getVelocityX() const {
    return velocityX;
}

int PhysBody::getVelocityY() const {
    return velocityY;
}

int PhysBody::getLastStepVelocityX() const {
    return lastStepVelocityX;
}

int PhysBody::getLastStepVelocityY() const {
    return lastStepVelocityY;
}

void PhysBody::applyVelocity() {
    invalidateShape();
    shape.x += velocityX;
    shape.y += velocityY;

    lastStepVelocityX = velocityX;
    lastStepVelocityY = velocityY;

    if (autoFreeze) {
        velocityX = 0;
        velocityY = 0;
    } else {
        velocityX /= dumping;
        velocityY /= dumping;
    }
}

void PhysBody::invalidateShape() {
    oldShape = shape;
}

void PhysBody::revert() {
    shape = oldShape;
}

void PhysBody::setBottom(const SDL_Rect *rect) {
    shape.y = rect->y + rect->h + COLLISION_SPACE;
}

void PhysBody::setTop(const SDL_Rect *rect) {
    shape.y = rect->y - shape.h - COLLISION_SPACE;
}

void PhysBody::setLeft(const SDL_Rect *rect) {
    shape.x = rect->x - shape.w - COLLISION_SPACE;
}

void PhysBody::setRight(const SDL_Rect *rect) {
    shape.x = rect->x + rect->w + COLLISION_SPACE;
}

void PhysBody::setAutoFreeze(bool autoFreeze) {
    this->autoFreeze = autoFreeze;
}

bool PhysBody::getAutoFreeze() const {
    return autoFreeze;
}

int PhysBody::getIdentifier() const {
    return identifier;
}

void PhysBody::setIdentifier(int identifier) {
    PhysBody::identifier = identifier;
}

void PhysBody::setPosition(int x, int y) {
    shape.x = x;
    shape.y = y;
}

void PhysBody::setSensor(bool sensor) {
    this->sensor = sensor;
}

bool PhysBody::isSensor() const {
    return sensor;
}

RPGItem *PhysBody::getItem() const {
    return item;
}

void PhysBody::setItem(RPGItem *item) {
    PhysBody::item = item;
}

void PhysBody::setWidth(int width) {
    shape.w = width;
}

void PhysBody::setHeight(int height) {
    shape.h = height;
}

bool PhysBody::isToBeRemoved() const {
    return toBeRemoved;
}

void PhysBody::setToBeRemoved(bool toBeRemoved) {
    PhysBody::toBeRemoved = toBeRemoved;
}

void PhysBody::mulVelocity(float multiplier) {
    velocityX *= multiplier;
    velocityY *= multiplier;
}
