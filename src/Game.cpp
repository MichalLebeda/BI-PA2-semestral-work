//
// Created by michal on 3/10/20.
//

#include "Game.h"
#include "Util.h"

#include <fstream>
#include <SDL2/SDL_ttf.h>

using namespace std;
Uint32 tickDelta = 0;

Game::Game(const int width, const int height) : width(width), height(height) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Michal Lebeda - Semestrální práce");
    running = true;
    count = 0;

    SDL_Rect windowRect;
    windowRect.x = 0;
    windowRect.y = 0;
    windowRect.w = width;
    windowRect.h = height;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    cameraRenderer = new CameraRenderer(renderer, windowRect);
    assets = new Assets(renderer);

    menu = new Menu(windowRect.w, windowRect.h, assets, cameraRenderer->getFont());

    oldKeyStates = new Uint8[numberOfKeys];
}

Game::~Game() {
    delete menu;
    delete assets;
    delete cameraRenderer;
    delete hud;
    delete level;
    delete[] oldKeyStates;

    if (rpgPlayer != nullptr) {
        ofstream playerFile;
        playerFile.open(PLAYER_FILENAME);
        if (playerFile.is_open()) {
            rpgPlayer->serialize(playerFile);
            playerFile.close();
            cout << "Successfully saved player" << endl;
        } else {
            cerr << "Cannot save player, is folder writable?" << endl;
        }
    }
    delete rpgPlayer;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void Game::loop() {
    while (running) {
        lastFrameTicks = SDL_GetTicks();
        static unsigned int lastTime;
        if (lastFrameTicks >= (lastTime + 1000)) {
            lastTime = lastFrameTicks;
            frameCount = 0;
            count++;
        }

        input();
        switch (state) {
            case PLAY:
                renderGame();
                break;
            case FADING:
                renderGame();
                fade();
                break;
            case GAME_OVER:
                if (rpgPlayer->hasWin()) {
                    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
                    SDL_RenderClear(renderer);


                    cameraRenderer->renderText("Vyhráli jste", 470, 350, 100, 100, 100);
                    cameraRenderer->renderText("stiskněte mezerník", 434, 400, 100, 100, 100);
                } else {
                    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
                    SDL_RenderClear(renderer);

                    cameraRenderer->renderText("Prohráli jste", 464, 350);
                    cameraRenderer->renderText("stiskněte mezerník", 434, 400);
                }
                break;
            case MENU:
                SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
                SDL_RenderClear(renderer);

                menu->render(cameraRenderer);
                break;
        }

        SDL_RenderPresent(renderer);

        frameCount++;
        tickDelta = SDL_GetTicks() - lastFrameTicks;

        if (tickDelta < (1000 / 60)) {
            int delay = (1000 / 60) - tickDelta;
            tickDelta += delay;
            SDL_Delay(delay);
        }
    }
}

void Game::input() {
    const Uint8 *keystates(SDL_GetKeyboardState(nullptr));

    //Single click action keys
    while (SDL_PollEvent(&event)) {
        //Close game if requested by user
        if (event.type == SDL_QUIT) {
            running = false;
            return;
        }

        if (state == State::PLAY) {
            if (rpgPlayer->alive() && !rpgPlayer->hasWin()) {
                if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        case SDLK_EQUALS:
                            cameraRenderer->setZoom(cameraRenderer->currentZoom + 0.03f);
                            break;
                        case SDLK_MINUS:
                            cameraRenderer->setZoom(cameraRenderer->currentZoom - 0.1f);
                            break;
                        case SDLK_p:
                            debug = !debug;
                            break;
                        case SDLK_e:
                            level->pickupItemUnderPlayer();
                            break;
                        default:
                            break;
                    }
                } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    hud->handleClick(event.button.x, event.button.y);
                    break;
                }
            }
        } else if (state == State::GAME_OVER) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        startFromBeginning();
                        break;
                }
            }
        } else if (state == State::MENU) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                Menu::Action action = menu->handleClick(event.button.x, event.button.y);
                switch (action) {
                    case Menu::Action::NOTHING:
                        //intentionally do nothing
                        break;
                    case Menu::Action::NEW_GAME:
                        startFromBeginning();
                        break;
                    case Menu::Action::LOAD_GAME:
                        state = State::PLAY;

                        ifstream playerFile;
                        playerFile.open(PLAYER_FILENAME);

                        rpgPlayer = new RPGPlayer();
                        rpgPlayer->deserialize(playerFile);

                        currentLevelIndex = rpgPlayer->getLevelIndex();
                        level = new Level(currentLevelIndex, "assets/" + to_string(currentLevelIndex) + ".map",
                                          assets,
                                          cameraRenderer,
                                          Level::PlayerLocation::LOADED_FROM_FILE, rpgPlayer);

                        hud = new Hud(width, height, rpgPlayer, assets);
                }
            }
        }
    }

    //handle mouse hover
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    switch (state) {
        case State::PLAY:
            hud->handleHover(x, y);
            break;
        case State::MENU:
            menu->handleHover(x, y);
            break;
        case State::FADING:
            break;
        case State::GAME_OVER:
            break;
    }

    //Hold action keys
    if (state == State::PLAY) {
        if (rpgPlayer->alive() && !rpgPlayer->hasWin()) {

            if (keystates[SDL_SCANCODE_W]) {
                level->player->goUp();
            }
            if (keystates[SDL_SCANCODE_S]) {
                level->player->goDown();
            }
            if (keystates[SDL_SCANCODE_A]) {
                level->player->goLeft();
            }
            if (keystates[SDL_SCANCODE_D]) {
                level->player->goRight();
            }

            if (keystates[SDL_SCANCODE_LEFT] && !oldKeyStates[SDL_SCANCODE_LEFT]) {
                level->player->attackLeft();
            }
            if (keystates[SDL_SCANCODE_RIGHT] && !oldKeyStates[SDL_SCANCODE_RIGHT]) {
                level->player->attackRight();
            }
            if (keystates[SDL_SCANCODE_UP] && !oldKeyStates[SDL_SCANCODE_UP]) {
                level->player->attackUp();
            }
            if (keystates[SDL_SCANCODE_DOWN] && !oldKeyStates[SDL_SCANCODE_DOWN]) {
                level->player->attackDown();
            }
        }
    }

    setOldKeyStates(keystates);
}

void Game::setOldKeyStates(const Uint8 *keyStates) {
    copy(keyStates, keyStates + numberOfKeys, oldKeyStates);
}

void Game::renderGame() {
    SDL_Color &bgColor = level->getBgColor();

    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, 255);
    SDL_RenderClear(renderer);
    level->render(cameraRenderer);

    if (debug) {
        level->renderDebug(cameraRenderer);
    }

    switch (level->getRequest()) {
        case Level::DO_NOTHING:
            break;
        case Level::GO_LEVEL_DOWN:
            levelDown();
            break;
        case Level::GO_LEVEL_UP:
            levelUp();
            break;
    }

    hud->setItemUnderPlayer(level->getItemUnderPlayer());
    hud->render(cameraRenderer);

    if (!rpgPlayer->alive() || rpgPlayer->hasWin()) {
        state = State::FADING;
    }
}

void Game::startFromBeginning() {
    state = State::PLAY;
    fadeoutProgress = 0;

    delete hud;
    delete level;
    delete rpgPlayer;

    //clean old savefiles
    remove(PLAYER_FILENAME.c_str());
    for (int i = 0; i < LEVELS_TOTAL; i++) {
        string path = Level::getPatchPath(i);
        if (remove(path.c_str()) != 0) {
            perror(string("Cannot delete file (ok if doesn't exist): ").append(string(path).c_str()).c_str());
        } else {
            cout << "Deleting file: " << path << endl;
        }
    }

    rpgPlayer = new RPGPlayer();
    rpgPlayer->setMaxHealth(100);
    rpgPlayer->setHealth(rpgPlayer->getMaxHealth());
    rpgPlayer->setAttack(0);
    rpgPlayer->setDefense(0);

    auto weapon = (RPGItem::createItem(0));
    auto shirt = (RPGItem::createItem(24));
    auto pants = (RPGItem::createItem(25));
    rpgPlayer->equip(weapon);
    rpgPlayer->equip(shirt);
    rpgPlayer->equip(pants);

    currentLevelIndex = 0;

    hud = new Hud(width, height, rpgPlayer, assets);

    level = new Level(currentLevelIndex, "assets/" + to_string(currentLevelIndex) + ".map", assets,
                      cameraRenderer,
                      Level::PlayerLocation::NEXT_TO_STAIRS_UP, rpgPlayer);
}

void Game::levelDown() {
    if (currentLevelIndex + 1 != LEVELS_TOTAL) {
        currentLevelIndex++;
        rpgPlayer->setLevelIndex(currentLevelIndex);

        delete level;
        level = new Level(currentLevelIndex, "assets/" + to_string(currentLevelIndex) + ".map", assets,
                          cameraRenderer,
                          Level::PlayerLocation::NEXT_TO_STAIRS_UP, rpgPlayer);
    } else {
        rpgPlayer->setWin(true);
    }
}

void Game::levelUp() {
    if (currentLevelIndex - 1 >= 0) {
        currentLevelIndex--;
        rpgPlayer->setLevelIndex(currentLevelIndex);

        delete level;
        level = new Level(currentLevelIndex, "assets/" + to_string(currentLevelIndex) + ".map", assets,
                          cameraRenderer,
                          Level::PlayerLocation::NEXT_TO_STAIRS_DOWN, rpgPlayer);
    }
}

void Game::fade() {
    SDL_Rect rect{0, 0, width, height};
    SDL_SetTextureAlphaMod(assets->shadowRegion->getTexture(), (Uint8) fadeoutProgress);
    cameraRenderer->renderRegionImmediatelyAbsolutePos(assets->darkRegion, &rect);
    fadeoutProgress += 5;
    if (fadeoutProgress >= 255) {
        state = State::GAME_OVER;
    }
    SDL_SetTextureAlphaMod(assets->darkRegion->getTexture(), 255);
}
