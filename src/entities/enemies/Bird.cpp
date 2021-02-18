//
// Created by michal on 4/27/20.
//

#include "Bird.h"
#include "Enemies.h"

Bird::Bird(const Assets *assets, int x, int y, PhysWorld *world, Player *player) :
        Enemy(assets,assets->birdDyingAnim,
              x, y,
              metersToUnits(0.5f), metersToUnits(0.4f),
              10,
              10,
              1,
              4,
              world, player) {

    anim = assets->birdApproachingAnim;
}

Animation<TextureRegion>* Bird::getApproachingAnim() {
    return assets->birdApproachingAnim;
}

Animation<TextureRegion>* Bird::getDyingAnim() {
    return assets->birdDyingAnim;
}

Animation<TextureRegion>* Bird::getAttackingAnim() {
    return assets->birdAttackingAnim;
}

Animation<TextureRegion>* Bird::getShockedAnim() {
    return assets->birdShockedAnim;
}

int Bird::getId() {
    return Enemies::BIRD;
}
