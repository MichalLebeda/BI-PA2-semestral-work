//
// Created by michal on 3/11/20.
//

#include "TextureRegion.h"

TextureRegion::TextureRegion(int x, int y, int width, int height, SDL_Texture *texture) {
    this->rect = new SDL_Rect({x, y, width, height});
    this->texture = texture;
}

TextureRegion::~TextureRegion() {
    delete rect;
}

SDL_Rect *TextureRegion::getRect() const {
    return rect;
}

SDL_Texture *TextureRegion::getTexture() const {
    return texture;
}
