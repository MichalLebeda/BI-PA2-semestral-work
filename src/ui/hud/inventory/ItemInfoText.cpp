//
// Created by michal on 3/28/20.
//

#include "ItemInfoText.h"

ItemInfoText::ItemInfoText() {

}

ItemInfoText::~ItemInfoText() {

}

void ItemInfoText::render(CameraRenderer *renderer) {
    if (item != nullptr) {
        if (alignBottom) {
            int i = 1;
            if (item->getAttackEffect() != 0) {
                renderer->renderText((string("⚔")
                                      + std::to_string(item->getAttackEffect())).c_str(),
                                     position.x,
                                     position.y - TEXT_SPACE * i);
                i++;
            }
            if (item->getDefenseEffect() != 0) {

                renderer->renderText((string("⛨")
                                      + std::to_string(item->getDefenseEffect())).c_str(),
                                     position.x,
                                     position.y - TEXT_SPACE * i);
                i++;
            }
            if (item->getHealthEffect() != 0) {
                renderer->renderText((string("❤")
                                      + std::to_string(item->getHealthEffect())).c_str(),
                                     position.x,
                                     position.y - TEXT_SPACE * i);
                i++;
            }

            renderer->renderText(item->getName().c_str(),
                                 position.x,
                                 position.y - TEXT_SPACE * i);
            if (!extraText.empty()) {
                i++;
                renderer->renderText(extraText.c_str(),
                                     position.x,
                                     position.y - TEXT_SPACE * i);
            }
        } else {
            int i = 0;
            if (!extraText.empty()) {

                renderer->renderText(extraText.c_str(),
                                     position.x,
                                     position.y + TEXT_SPACE * i);
                i++;
            }
            renderer->renderText(item->getName().c_str(),
                                 position.x,
                                 position.y + TEXT_SPACE * i);
            i++;
            if (item->getAttackEffect() != 0) {
                renderer->renderText((string("⚔ ")
                                      + std::to_string(item->getAttackEffect())).c_str(),
                                     position.x,
                                     position.y + TEXT_SPACE * i);
                i++;
            }
            if (item->getDefenseEffect() != 0) {

                renderer->renderText((string("⛨ ")
                                      + std::to_string(item->getDefenseEffect())).c_str(),
                                     position.x,
                                     position.y + TEXT_SPACE * i);
                i++;
            }
            if (item->getHealthEffect() != 0) {
                renderer->renderText((string("❤ ")
                                      + std::to_string(item->getHealthEffect())).c_str(),
                                     position.x,
                                     position.y + TEXT_SPACE * i);
            }
        }
    }
}

void ItemInfoText::setItem(const RPGItem *item) {
    this->item = item;
}

void ItemInfoText::setPosition(int x, int y) {
    position = {x, y};
}

void ItemInfoText::setAlignBottom(bool bottom) {
    alignBottom = bottom;
}

void ItemInfoText::setExtraText(string text) {
    extraText = text;
}
