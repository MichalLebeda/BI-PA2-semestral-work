//
// Created by michal on 3/18/20.
//

#include "AnimatedTile.h"
#include "../Game.h"

AnimatedTile::AnimatedTile(Animation<TextureRegion> *animation, int x, int y) : Tile(animation->getFrame(0), x, y) {
    this->animation = animation;
    setRandomOffset();
}

AnimatedTile::~AnimatedTile() {

}

void AnimatedTile::render(CameraRenderer *renderer) {
    time += tickDelta;
    floorSprite->setRegion(animation->getFrame(time));

    Tile::render(renderer);
}

void AnimatedTile::setRandomOffset() {
    time = rand() % animation->getLength();
}

