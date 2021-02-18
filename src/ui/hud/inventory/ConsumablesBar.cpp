//
// Created by michal on 3/28/20.
//

#include "ConsumablesBar.h"

ConsumablesBar::ConsumablesBar(RPGPlayer *rpgPlayer, Assets *assets) {
    this->rpgPlayer = rpgPlayer;
    this->rpgInventory = rpgPlayer->getInventory();
    this->assets = assets;
}

ConsumablesBar::~ConsumablesBar() {

}

void ConsumablesBar::render(CameraRenderer *renderer) {
    SDL_Rect drawRect;

    map<int, vector<RPGItem *>> *slots = rpgInventory->getSlots();
    int i = 0;
    for (auto it = slots->begin(); it != slots->end(); it++, i++) {
        RPGItem *firstItem = it->second.at(0);
        TextureRegion *region = assets->itemRegions.at(firstItem->getRegionIndex());

        //draw slot background
        drawRect.x = boundingBox.x + (SLOT_SIZE + SPACE) * i;
        drawRect.y = boundingBox.y;
        drawRect.w = SLOT_SIZE;
        drawRect.h = SLOT_SIZE;
        renderer->renderRegionImmediatelyAbsolutePos(
                assets->tileRegions.at(
                        firstItem->getType() == RPGItem::Type::CONSUMABLE ?
                        SLOT_BG_CONSUMABLE_INDEX : (firstItem->isEquipped())
                                                   ? SLOT_BG_EQUIPPED_INDEX
                                                   : SLOT_BG_INDEX),
                &drawRect);

        //draw item shadow
        drawRect.w = region->getRect()->w * (48 / 16);
        drawRect.h = region->getRect()->h * (48 / 16);

        drawRect.x = boundingBox.x + (SLOT_SIZE + SPACE) * i
                     + SLOT_SIZE / 2
                     - drawRect.w / 2;
        drawRect.y = SLOT_SIZE / 2 - drawRect.h / 2 - 4 + boundingBox.y;

        drawRect.x -= SLOT_SIZE / 16;
        drawRect.y += SLOT_SIZE / 16;
        renderer->renderRegionImmediatelyAbsolutePos(assets->itemRegions.at(firstItem->getRegionIndex()),
                                                     &drawRect,
                                                     41, 29, 43);
        //draw item
        drawRect.x += SLOT_SIZE / 16;
        drawRect.y -= SLOT_SIZE / 16;
        renderer->renderRegionImmediatelyAbsolutePos(assets->itemRegions.at(firstItem->getRegionIndex()),
                                                     &drawRect,
                                                     &firstItem->getColorTint());

        renderer->renderText(to_string(it->second.size()).c_str(),
                             boundingBox.x + (SLOT_SIZE + SPACE) * i + SLOT_SIZE / 2 - 5,
                             boundingBox.y + 43);
    }
}

void ConsumablesBar::setPosition(int x, int y) {
    boundingBox.x = x;
    boundingBox.y = y;
}

bool ConsumablesBar::hit(int x, int y) {
    updateBoundingBox();

    SDL_Point point{x, y};
    return SDL_PointInRect(&point, &boundingBox);
}

void ConsumablesBar::handleHover(int x, int y) {
    SDL_Point point{x, y};
    SDL_Rect itemRect{0, 0, SLOT_SIZE, SLOT_SIZE};

    map<int, vector<RPGItem *>> *slots = rpgInventory->getSlots();
    int i = 0;
    for (auto it = slots->begin(); it != slots->end(); it++, i++) {
        RPGItem *firstItem = it->second.at(0);
        itemRect.x = boundingBox.x + (SLOT_SIZE + SPACE) * i;
        itemRect.y = SPACE - SLOT_SIZE / 16 + boundingBox.y;

        if (SDL_PointInRect(&point, &itemRect)) {
            hoveredItem = firstItem;
        }
    }
}

void ConsumablesBar::handleClick(int x, int y) {
    /**usage of item avoids rapid blinking when moving mouse
     * over equipBar (because of spaces between items)
     */
    if (hoveredItem != nullptr) {
        rpgPlayer->apply(hoveredItem);
        rpgPlayer->getInventory()->remove(hoveredItem);
        hoveredItem = nullptr;
        handleHover(x, y);
    }
}

int ConsumablesBar::getHeight() {
    return SLOT_SIZE;
}

int ConsumablesBar::getWidth() {
    return (SLOT_SIZE + SPACE) * rpgPlayer->getInventory()->getAmountOfSlots();
}

void ConsumablesBar::updateBoundingBox() {
    boundingBox.w = getWidth();
    boundingBox.h = getHeight();
}

void ConsumablesBar::setNotHovered() {
    hoveredItem = nullptr;
}

RPGItem *ConsumablesBar::getHoveredItem() {
    return hoveredItem;
}
