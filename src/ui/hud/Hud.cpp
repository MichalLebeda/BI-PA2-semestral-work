//
// Created by michal on 3/26/20.
//

#include "Hud.h"

Hud::Hud(int windowWidth, int windowHeight, RPGPlayer *rpgPlayer, Assets *assets) :
        equipBar(rpgPlayer, assets), consumablesBar(rpgPlayer, assets) {
    this->rpgPlayer = rpgPlayer;
    this->assets = assets;
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    consumablesBar.setPosition(8, windowHeight - consumablesBar.getHeight() - 8);
    equipBar.setPosition(windowWidth - equipBar.getWidth() - 8, windowHeight - equipBar.getHeight() - 8);
    info.setPosition(8, windowHeight - consumablesBar.getHeight() - 8);
    underPlayerItemInfo.setPosition(8, 32);
    underPlayerItemInfo.setAlignBottom(false);
    underPlayerItemInfo.setExtraText("seberte [E]");
}

Hud::~Hud() {

}

void Hud::render(CameraRenderer *renderer) {
    renderHealthBar(renderer);
    equipBar.render(renderer);
    info.render(renderer);
    underPlayerItemInfo.render(renderer);
    consumablesBar.render(renderer);

    renderer->renderText(
            (string("❤") + to_string(rpgPlayer->getHealth()) + '/' + to_string(rpgPlayer->getMaxHealth())).c_str(),
            windowWidth - 130, 30);
    renderer->renderText((string("⛨") + to_string(rpgPlayer->getDefense())).c_str(), windowWidth - 130, 70);
    renderer->renderText((string("⚔") + to_string(rpgPlayer->getAttack())).c_str(), windowWidth - 130, 110);
    renderer->renderText((string("  X   ") + to_string(rpgPlayer->getKilledEnemyCount())).c_str(), windowWidth - 130, 150);
}

void Hud::renderHealthBar(CameraRenderer *renderer) {
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.h = 16;
    rect.w = windowWidth;
    renderer->renderRegionImmediatelyAbsolutePos(assets->healthBarEmptyRegion, &rect);

    if (virtualHealth != rpgPlayer->getHealth()) {
        if (virtualHealth < rpgPlayer->getHealth()) {
            virtualHealth++;
        } else {
            virtualHealth--;
        }
    }

    rect.w = (int) (windowWidth * (((double) virtualHealth) / ((double) rpgPlayer->getMaxHealth())));
    renderer->renderRegionImmediatelyAbsolutePos(assets->healthBarRegion, &rect);
}

void Hud::handleClick(int x, int y) {
    if (consumablesBar.hit(x, y)) {
        consumablesBar.handleClick(x, y);
        info.setItem(consumablesBar.getHoveredItem());
    }
}

void Hud::handleHover(int x, int y) {
    if (consumablesBar.hit(x, y)) {
        consumablesBar.handleHover(x, y);
    } else {
        consumablesBar.setNotHovered();
        if (equipBar.hit(x, y)) {
            equipBar.handleHover(x, y);
        } else {
            equipBar.setNotHovered();
        }
    }

    RPGItem *item = consumablesBar.getHoveredItem();
    if (item != nullptr) {
        info.setItem(item);
    } else {
        item = equipBar.getHoveredItem();
        info.setItem(item);
    }
}

void Hud::setItemUnderPlayer(const RPGItem *item) {
    underPlayerItemInfo.setItem(item);
}
