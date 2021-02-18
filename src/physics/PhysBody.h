//
// Created by michal on 3/11/20.
//

#ifndef SEMESTRAL_WORK_PHYSBODY_H
#define SEMESTRAL_WORK_PHYSBODY_H


#include <SDL2/SDL.h>
#include "../graphics/Renderable.h"
#include "../rpg/RPGItem.h"

/**
 * Class representing one item in physical world
 */
class PhysBody : Renderable {
public:
    /**
     *
     * @param x X center position in game units
     * @param y Y center position in game units
     * @param w Width in game units
     * @param h Height in game units
     */
    PhysBody(int x, int y, int w, int h);

    ~PhysBody();

    /**
     *
     * @return Shape of body
     */
    SDL_Rect *getShape();

    /**
     *
     * @return Shape of body from last step, useful for difference between frames
     */
    SDL_Rect *getOldShape();

    /**
     * @brief Set whatever body should immediately stop moving if no velocity is set after step
     * @param autoFreeze True if should be stopped immediately, false otherwise
     */
    void setAutoFreeze(bool autoFreeze);

    /**
     * @brief Get whatever body should immediately stop moving if no velocity is set after step
     * @return True if body stops immediately after step if no force is applied, false otherwise
     */
    bool getAutoFreeze() const;

    /**
     *
     * @param velocityX X velocity in game units per step
     * @param velocityY Y velocity in game units per step
     */
    void setVelocity(int velocityX, int velocityY);

    /**
     *
     * @param velocityX X velocity in game units per step
     */
    void setVelocityX(int velocityX);

    /**
     *
     * @param velocityY Y velocity in game units per step
     */
    void setVelocityY(int velocityY);

    /**
     * @brief Multiply current velocity
     * @param multiplier Multiplier to multiply each component of velocity with
     */
    void mulVelocity(float multiplier);

    /**
     *
     * @return X velocity in game units per step
     */
    int getVelocityX() const;

    /**
     *
     * @return Y velocity in game units per step
     */
    int getVelocityY() const;

    /**
     *
     * @return X velocity in game units per step from previous step
     */
    int getLastStepVelocityX() const;

    /**
     *
     * @return Y velocity in game units per step from previous step
     */
    int getLastStepVelocityY() const;

    /**
     * @brief Set whatever body should be dynamic/move when collided by others
     * @param dynamic Whatever body should be dynamic
     */
    void setDynamic(bool dynamic);

    /**
     * @brief Get whatever body should be dynamic/move when collided by others
     * @return True if body is dynamic, false otherwise
     */
    bool isDynamic() const;

    /**
     *
     * @param x X coordinate of top left corner of the body in game units
     * @param y Y coordinate of top left corner of the body in game units
     */
    void setPosition(int x, int y);

    /**
     *
     * @return X coordinate of top left corner of the body
     */
    int getX() const;

    /**
     *
     * @return Y coordinate of top left corner of the body
     */
    int getY() const;

    /**
     *
     * @return X coordinate of the center of the body
     */
    int getCenterX() const;

    /**
     *
     * @return Y coordinate of the center of the body
     */
    int getCenterY() const;

    /**
     *
     * @param width Width in game units to be set
     */
    void setWidth(int width);

    /**
     *
     * @param height Height in game units to be set
     */
    void setHeight(int height);

    /**
     *
     * @return Body width in game units
     */
    int getWidth() const;

    /**
     *
     * @return Body height in game units
     */
    int getHeight() const;

    void render(CameraRenderer *renderer) override;

    /**
     * @brief Transform body based on current velocity
     */
    void applyVelocity();

    /**
     * @brief Backup current shape for further use in collision handling
     */
    void invalidateShape();

    /**
     * @brief Revert to old shape
     */
    void revert();

    /**
     * @brief Set position to be under another rect as close as possible
     * @param rect Rect this operation is relative to
     */
    void setBottom(const SDL_Rect *rect);

    /**
     * @brief Set position to be above another rect as close as possible
     * @param rect Rect this operation is relative to
     */
    void setTop(const SDL_Rect *rect);

    /**
     * @brief Set position to the left of another rect as close as possible
     * @param rect Rect this operation is relative to
     */
    void setLeft(const SDL_Rect *rect);

    /**
     * @brief Set position to the right of another rect as close as possible
     * @param rect Rect this operation is relative to
     */
    void setRight(const SDL_Rect *rect);

    /**
     * @brief Set whatever body should not collide at all
     * @param sensor True if body should collide, false if not
     */
    void setSensor(bool sensor);

    /**
     * @brief Get if is body not collidable
     * @return true if not collidable false othervise
     */
    bool isSensor() const;

    /**
     *
     * @return Identifier assigned to body, -1 if none assigned
     */
    int getIdentifier() const;

    /**
     *
     * @param identifier Value of identifier, keep in mind that -1 is reserved as default
     */
    void setIdentifier(int identifier);

    /**
     *
     * @return RpgItem assigned, nullptr if none assigned
     */
    RPGItem *getItem() const;

    /**
     *
     * @param item RpgItem to be assigned
     */
    void setItem(RPGItem *item);

    /**
     * @brief Get if body will be removed as soon as possible
     * @return
     */
    bool isToBeRemoved() const;

    /**
     * @brief Set if body will be removed as soon as possible
     * @return
     */
    void setToBeRemoved(bool toBeRemoved);

private:
    int velocityX = 0; //unitsPerTick
    int velocityY = 0; //unitsPerTick
    int lastStepVelocityX = 0; //unitsPerTick
    int lastStepVelocityY = 0; //unitsPerTick
    int identifier = -1;

    float dumping = 1.0001;

    bool dynamic = false;
    bool sensor = false;
    bool autoFreeze = false;
    bool toBeRemoved = false;

    SDL_Rect shape;
    SDL_Rect oldShape;

    RPGItem *item = nullptr;
};


#endif //SEMESTRAL_WORK_PHYSBODY_H
