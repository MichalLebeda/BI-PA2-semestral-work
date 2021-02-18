//
// Created by michal on 4/27/20.
//

#include "Ghost.h"
#include "Enemies.h"

Ghost::Ghost(const Assets *assets, int x, int y, PhysWorld *world, Player *player) :
        Enemy(assets,assets->ghostDyingAnim,
              x, y,
              metersToUnits(0.5f), metersToUnits(0.4f),
              30,
              30,
              1,
              20,
              world, player) {

    anim = assets->ghostApproachingAnim;
}

Animation<TextureRegion>* Ghost::getApproachingAnim() {
    return assets->ghostApproachingAnim;
}

Animation<TextureRegion>* Ghost::getDyingAnim() {
    return assets->ghostDyingAnim;
}

Animation<TextureRegion>* Ghost::getAttackingAnim() {
    return assets->ghostAttackingAnim;
}

Animation<TextureRegion>* Ghost::getShockedAnim() {
    return assets->ghostShockedAnim;
}

int Ghost::getId() {
    return Enemies::GHOST;
}
