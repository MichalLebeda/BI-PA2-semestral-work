//
// Created by michal on 5/27/20.
//

#include <fstream>
#include "Menu.h"

Menu::Menu(int windowWidth, int windowHeight, const Assets *assets, TTF_Font *font)
        : bgRegion(assets->menuBg),
          loadGameButton(windowWidth / 2 - 120,
                         windowHeight / 2 - 200,
                         240,
                         120,
                         string("Načíst hru"),
                         assets,
                         font),
          newGameButton(windowWidth / 2 - 120,
                        windowHeight / 2 - 60,
                        240,
                        120,
                        string("Začít novou hru"),
                        assets,
                        font) {
    SDL_Rect *regionRect = assets->menuBg->getRect();
    targetBgRect = {
            0,
            0,
            (int) ((double) regionRect->w / (double) regionRect->h * (double) windowHeight),
            windowHeight
    };
    refreshLoadOption();
}

void Menu::render(CameraRenderer *renderer) {
    renderer->renderRegionImmediatelyAbsolutePos(bgRegion, &targetBgRect);
    if (canLoadGame) {
        loadGameButton.render(renderer);
    }
    newGameButton.render(renderer);

    renderer->renderText(
            "Ovládání:     WASD - pohyb             šipky - útok             E - sebrat věc             P - debug", 15,
            targetBgRect.h - 30);
}

Menu::Action Menu::handleClick(int x, int y) {
    if (canLoadGame) {
        if (loadGameButton.hit(x, y)) {
            return Menu::LOAD_GAME;
        }
    }

    if (newGameButton.hit(x, y)) {
        return Menu::NEW_GAME;
    }

    return Menu::NOTHING;
}

void Menu::refreshLoadOption() {
    ifstream playerFile;
    playerFile.open(PLAYER_FILENAME);

    if (playerFile.is_open()) {
        canLoadGame = true;
        playerFile.close();
    } else {
        canLoadGame = false;
    }
}

void Menu::handleHover(int x, int y) {
    loadGameButton.handleHover(x, y);
    newGameButton.handleHover(x, y);
}
