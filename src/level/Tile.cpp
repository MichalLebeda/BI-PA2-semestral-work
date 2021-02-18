//
// Created by michal on 3/9/20.
//

#include "Tile.h"

#include <iostream>

Tile::Tile(TextureRegion *region, int x, int y) {
    floorSprite = new Sprite(region);

    floorSprite->setPosition(x, y);
}

Tile::~Tile() {
    delete floorSprite;
    delete item;
}

void Tile::render(CameraRenderer *renderer) {
    floorSprite->render(renderer);
    if (item != nullptr) {
        item->render(renderer);
    }
}

void Tile::setWall(Renderable *item) {
    this->item = item;
}
