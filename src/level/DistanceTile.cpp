//
// Created by michal on 3/20/20.
//

#include "DistanceTile.h"

DistanceTile::DistanceTile(Animation<TextureRegion> *animation, int x, int y, Player *player) : Tile(
        animation->getFrame(0), x, y) {
    this->animation = animation;
    this->player = player;
}

DistanceTile::~DistanceTile() {

}

void DistanceTile::render(CameraRenderer *renderer) {
    float distX = player->getBody()->getX() - floorSprite->getCenterX();
    float distY = player->getBody()->getY() - floorSprite->getCenterY();
    float distance = sqrt(distX * distX + distY * distY);

//    distance -= metersToUnits(0.4f);
    if (distance < DISTANCE_TILE_MIN_DIST) {
        distance = DISTANCE_TILE_MIN_DIST;
        player->getRpgComponent()->handleDamage(1);
    }

    if (distance > DISTANCE_TILE_MAX_DIST) {
        distance = DISTANCE_TILE_MAX_DIST;
    }

    floorSprite->setRegion(animation->getFrame(
            (animation->getLength() - 1) *
            (1.f - (distance - DISTANCE_TILE_MIN_DIST) / (DISTANCE_TILE_MAX_DIST - DISTANCE_TILE_MIN_DIST))));

    animation->getLength();
    Tile::render(renderer);
}
