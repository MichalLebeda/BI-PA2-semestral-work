//
// Created by michal on 3/11/20.
//

#include "DepthSortedSprite.h"
#include "../Util.h"

DepthSortedSprite::DepthSortedSprite(TextureRegion *textureRegion, int x, int y) : Sprite(
        textureRegion, x, y) {
}

void DepthSortedSprite::render(CameraRenderer *renderer) {
    renderer->renderLaterDepthSorted(region, rect);
}
