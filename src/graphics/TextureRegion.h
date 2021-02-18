//
// Created by michal on 3/11/20.
//

#ifndef SEMESTRAL_WORK_TEXTUREREGION_H
#define SEMESTRAL_WORK_TEXTUREREGION_H


#include <SDL2/SDL_render.h>

/**
 * Class representing rectangular part of texture used for drawing.
 * There is no need for loading multiple small textures which negatively affects performance.
 */
class TextureRegion {
public:

    /**
     * @brief Constructor
     * @param x
     * @param y
     * @param width
     * @param height
     * @param texture
     */
    TextureRegion(int x, int y, int width, int height, SDL_Texture *texture);

    ~TextureRegion();

    /**
     * @brief Get region rectangle relative to texture in texture texels units
     * @return Regions rectangle
     */
    SDL_Rect *getRect() const;

    /**
     * @brief Get texture this region is sourced from
     * @return SDL_Texture source texture
     */
    SDL_Texture *getTexture() const;

private:
    SDL_Rect *rect;
    SDL_Texture *texture;
};


#endif //SEMESTRAL_WORK_TEXTUREREGION_H
