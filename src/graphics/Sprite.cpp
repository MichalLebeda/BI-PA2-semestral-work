//
// Created by michal on 3/10/20.
//

#include "Sprite.h"
#include "../Util.h"

Sprite::Sprite(TextureRegion *textureRegion) : rect({0,0,0,0}) {
    this->region = textureRegion;

    setSizeBasedOnRegion();
}

Sprite::Sprite(TextureRegion *textureRegion, int x, int y) {
    this->region = textureRegion;

    setPosition(x, y);
    setSizeBasedOnRegion();
}

Sprite::~Sprite() {

}

void Sprite::render(CameraRenderer *renderer) {
    renderer->renderRegionImmediately(region, &rect);
}

void Sprite::setSize(int width, int height) {
    rect.w = width;
    rect.h = height;
}

void Sprite::setSizeBasedOnRegion() {
    setSize(pixelsToUnits(region->getRect()->w), pixelsToUnits(region->getRect()->h));
}

void Sprite::setX(int x) {
    rect.x = x;
}

void Sprite::setY(int y) {
    rect.y = y;
}

void Sprite::setPosition(int x, int y) {
    rect.x = x;
    rect.y = y;
}

void Sprite::setPositionCenterBased(int x, int y) {
    rect.x = x - rect.w / 2;
    rect.y = y - rect.h / 2;
}

void Sprite::translate(int x, int y) {
    rect.x += x;
    rect.y += y;
}

int Sprite::getX() {
    return rect.x;
}

int Sprite::getY() {
    return rect.y;
}

int Sprite::getCenterX() {
    return rect.x + rect.w / 2;
}

int Sprite::getCenterY() {
    return rect.y + rect.h / 2;
}

int Sprite::getWidth() {
    return rect.w;
}

int Sprite::getHeight() {
    return rect.h;
}

const SDL_Rect *Sprite::getRect() {
    return &rect;
}

TextureRegion *Sprite::getRegion() {
    return region;
}

void Sprite::setRegion(TextureRegion *region) {
    this->region = region;
}

void Sprite::setXCenterBased(int x) {
    rect.x = x - rect.w / 2;
}

void Sprite::setYCenterBased(int y) {
    rect.y = y - rect.h / 2;
}
