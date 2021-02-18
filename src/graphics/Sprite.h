//
// Created by michal on 3/10/20.
//

#ifndef SEMESTRAL_WORK_SPRITE_H
#define SEMESTRAL_WORK_SPRITE_H

#include <SDL.h>
#include "Renderable.h"
#include "TextureRegion.h"

/**
 * Class representing TextureRegion located at some coordinates in game space with specified width and height.
 * Sprites can be rendered, moved etc.
 */
class Sprite : public Renderable {
public:

    /**
     *
     * @param textureRegion desired region of the sprite
     */
    Sprite(TextureRegion *textureRegion);

    /**
     *
     * @param textureRegion desired region of the sprite
     * @param x X coordinate in game units
     * @param y Y coordinate in game units
     */
    Sprite(TextureRegion *textureRegion, int x, int y);

    ~Sprite();

    void render(CameraRenderer *renderer) override;

    /**
     * @brief Obtain boundary region based on current position and size
     * @return ptr to SDL_Rect which this sprite occupies
     */
    const SDL_Rect *getRect();

    /**
     * @brief Automatically set size based on game units for each texel in current region
     */
    void setSizeBasedOnRegion();

    /**
     * @brief Set size in game units
     * @param width Width in game units
     * @param height Height in game units
     */
    void setSize(int width, int height);

    /**
     * @brief Set x coordinate of the top left corner
     * @param x X coordinate of the top left corner in game units
     */
    void setX(int x);

    /**
     * @brief Set y coordinate of the top left corner
     * @param y Y coordinate of the top left corner in game units
     */
    void setY(int y);

    /**
     * @brief Set x coordinate of the center
     * @param x X coordinate of the center in game units
     */
    void setXCenterBased(int x);

    /**
     * @brief Set y coordinate of the center
     * @param y Y coordinate of the center in game units
     */
    void setYCenterBased(int y);

    /**
     * @brief Set position of the top left corner
     * @param x top left x coordinate in game units
     * @param y top left y coordinate in game units
     */
    void setPosition(int x, int y);

    /**
     * Set center position
     * @param x X coordinate in game units
     * @param y Y coordinate in game units
     */
    void setPositionCenterBased(int x, int y);

    /**
     * @brief Set the positon relative to the current position
     * @param x X amount to move on x coordinate
     * @param y Y amount to move on y coordinate
     */
    void translate(int x, int y);

    /**
     *
     * @return returns top left x position coordinate in game units
     */
    int getX();

    /**
     *
     * @return returns top left y position coordinate in game units
     */
    int getY();

    /**
     * @brief Get x position of the center
     * @return x coordinate of sprite center in game units
     */
    int getCenterX();

    /**
     * @brief Get y position of the center
     * @return y coordinate of sprite center in game units
     */
    int getCenterY();

    /**
     *
     * @return width in game units
     */
    int getWidth();

    /**
     *
     * @return height in game units
     */
    int getHeight();

    /**
     * @brief Get currently set TextureRegion
     * @return return ptr to TextureRegion used by this sprite
     */
    TextureRegion *getRegion();

    /**
     * @brief Set TextureRegion to be rendered at sprite position with width and height of the sprite
     * @param region TextureRegion to be set
     */
    void setRegion(TextureRegion *region);

protected:
    SDL_Rect rect;
    TextureRegion *region;
};


#endif //SEMESTRAL_WORK_SPRITE_H
