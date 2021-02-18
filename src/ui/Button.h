//
// Created by michal on 5/27/20.
//

#ifndef SEMESTRAL_WORK_BUTTON_H
#define SEMESTRAL_WORK_BUTTON_H


#include "../graphics/Renderable.h"
#include "../Assets.h"

/**
 * Minimal button implementation
 */
class Button : Renderable {
public:

    /**
     *
     * @param x Button X position in window coordinates
     * @param y Button Y position in window coordinates
     * @param width Button width in window coordinates
     * @param height Button height in window coordinates
     * @param text Text to be shown on top of the button
     * @param assets Assets instance for obtaining region
     * @param font Font for computing text width
     */
    Button(int x, int y, int width, int height, string text, const Assets *assets, TTF_Font *font);

    void render(CameraRenderer *renderer);

    /**
     * @brief Set position
     * @param x X in window coordinates
     * @param y Y in window coordinates
     */
    bool hit(int x, int y);

    /**
     * @brief Make button to handle hover at X Y
     * @param x X pixel coordinate
     * @param y Y pixel coordinate
     */
    void handleHover(int x, int y);

protected:
    bool hovered = false;
    SDL_Rect boundingRect;

    string text;

    const Assets *assets;

    int textWidth;
    int textHeight;

    SDL_Color nonHoveredColor{120, 120, 120, 255};
};


#endif //SEMESTRAL_WORK_BUTTON_H
