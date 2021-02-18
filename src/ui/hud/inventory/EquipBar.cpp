//
// Created by michal on 3/26/20.
//

#include "EquipBar.h"

EquipBar::EquipBar(RPGPlayer *rpgPlayer, Assets *assets) {
    this->rpgPlayer = rpgPlayer;
    this->rpgInventory = rpgPlayer->getInventory();
    this->assets = assets;
}

EquipBar::~EquipBar() {

}

void EquipBar::renderItem(const RPGItem *item, CameraRenderer *renderer, int row) {
    SDL_Rect drawRect;
    TextureRegion *region = assets->itemRegions.at(item->getRegionIndex());
    /**
     * draw slot background
     */
    drawRect.x = boundingBox.x;
    drawRect.y = boundingBox.y + row * (SLOT_SIZE + SPACE);
    drawRect.w = SLOT_SIZE;
    drawRect.h = SLOT_SIZE;
    renderer->renderRegionImmediatelyAbsolutePos(
            assets->tileRegions.at(
                    item->getType() == RPGItem::Type::CONSUMABLE ?
                    SLOT_BG_CONSUMABLE_INDEX : (item->isEquipped())
                                               ? SLOT_BG_EQUIPPED_INDEX
                                               : SLOT_BG_INDEX),
            &drawRect);

    /**
     * draw item shadow
     */
    drawRect.w = region->getRect()->w * (48 / 16);
    drawRect.h = region->getRect()->h * (48 / 16);

    drawRect.x = boundingBox.x
                 + SLOT_SIZE / 2
                 - drawRect.w / 2;
    drawRect.y = SLOT_SIZE / 2 - drawRect.h / 2 + boundingBox.y + row * (SLOT_SIZE + SPACE);

    drawRect.x -= SLOT_SIZE / 16;
    drawRect.y += SLOT_SIZE / 16;
    renderer->renderRegionImmediatelyAbsolutePos(region,
                                                 &drawRect,
                                                 41, 29, 43);
    /**
     * draw item
     */
    drawRect.x += SLOT_SIZE / 16;
    drawRect.y -= SLOT_SIZE / 16;
    renderer->renderRegionImmediatelyAbsolutePos(region,
                                                 &drawRect,
                                                 &item->getColorTint());

}


void EquipBar::render(CameraRenderer *renderer) {
    renderItem(rpgPlayer->getPants(), renderer, 2);
    renderItem(rpgPlayer->getShirt(), renderer, 1);
    renderItem(rpgPlayer->getWeapon(), renderer, 0);
}

void EquipBar::setPosition(int x, int y) {
    boundingBox.x = x;
    boundingBox.y = y;
}

int EquipBar::getHeight() const {
    return (SPACE + SLOT_SIZE) * 3 - SPACE;
}

int EquipBar::getWidth() const {
    return SLOT_SIZE;
}

void EquipBar::updateBoundingBox() {
    boundingBox.w = getWidth();
    boundingBox.h = getHeight();
}

bool EquipBar::hit(int x, int y) {
    updateBoundingBox();
    SDL_Point point;
    point.x = x;
    point.y = y;
    return SDL_PointInRect(&point, &boundingBox);
}

void EquipBar::handleHover(int x, int y) {
    SDL_Point point{x, y};

    SDL_Rect drawRect;
    hoveredItem = nullptr;

    drawRect.x = boundingBox.x;
    drawRect.w = SLOT_SIZE;
    drawRect.h = SLOT_SIZE;

    int row = 0;
    drawRect.y = boundingBox.y + row * (SLOT_SIZE + SPACE);
    if (SDL_PointInRect(&point, &drawRect)) {
        hoveredItem = rpgPlayer->getWeapon();
    }

    row = 1;
    drawRect.y = boundingBox.y + row * (SLOT_SIZE + SPACE);
    if (SDL_PointInRect(&point, &drawRect)) {
        hoveredItem = rpgPlayer->getShirt();
    }

    row = 2;
    drawRect.y = boundingBox.y + row * (SLOT_SIZE + SPACE);
    if (SDL_PointInRect(&point, &drawRect)) {
        hoveredItem = rpgPlayer->getPants();
    }
}

void EquipBar::setNotHovered() {
    hoveredItem = nullptr;
}

RPGItem *EquipBar::getHoveredItem() {
    return hoveredItem;
}
