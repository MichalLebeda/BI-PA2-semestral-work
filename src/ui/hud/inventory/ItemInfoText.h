//
// Created by michal on 3/28/20.
//

#ifndef SEMESTRAL_WORK_ITEMINFOTEXT_H
#define SEMESTRAL_WORK_ITEMINFOTEXT_H


#include "../../../graphics/Renderable.h"
#include "../../../rpg/RPGItem.h"
#include "../../../rpg/RPGPlayer.h"

/**
 * Class for drawing info about item (for example item player is standing on)
 */
class ItemInfoText : Renderable {
public:
    ItemInfoText();

    ~ItemInfoText();

    void render(CameraRenderer *renderer) override;

    /**
     * @brief Set item whose information will be later rendered
     * @param item
     */
    void setItem(const RPGItem *item);

    /**
     * @brief Set position in pixels
     * @param x X coordinate in pixels
     * @param y Y coordinate in pixels
     */
    void setPosition(int x, int y);

    /**
     * @brief Set whatever item name should be bottom instead of on top
     * @param bottom
     */
    void setAlignBottom(bool bottom);

    /**
     * @brief Set extra text to be rendered after item name
     */
    void setExtraText(string);

private:
    bool alignBottom = true;
    const RPGItem *item = nullptr;
    SDL_Point position;

    static const int TEXT_SPACE = 32;

    string extraText;
};


#endif //SEMESTRAL_WORK_ITEMINFOTEXT_H
