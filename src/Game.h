//
// Created by michal on 3/10/20.
//

#ifndef SEMESTRAL_WORK_GAME_H
#define SEMESTRAL_WORK_GAME_H

#include <SDL2/SDL.h>
#include "Assets.h"
#include "level/Level.h"
#include "ui/hud/Hud.h"
#include "ui/Menu.h"


extern Uint32 tickDelta;

/**
 * Core class, handles game loop (input, rendering) and calls level loading methods
 */
class Game {

public:
    /**
     *
     * @param width     Window width
     * @param height    Window height
     */
    Game(const int width, const int height);

    ~Game();

    /**
     * @brief Start input/render loop
     */
    void loop();

    /**
     * @brief Draw fading animation on top of whatever is on screen, then changes state to GAME_OVER
     */
    void fade();

    /**
     * @brief Check input from keyboard and mouse
     */
    void input();

    /**
     * @brief Render everything including level and hud
     */
    void renderGame();

    /**
     * @brief Open level lower by one (if exists)
     */
    void levelDown();

    /**
     * @brief Open level higher by one (if exists)
     */
    void levelUp();

private:
    enum State {
        FADING, PLAY, MENU, GAME_OVER
    };

    void setOldKeyStates(const Uint8 *keyStates);

    void startFromBeginning();

    State state = State::MENU;

    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Event event;

    CameraRenderer *cameraRenderer;
    Assets *assets;

    Level *level = nullptr;
    Hud *hud = nullptr;
    RPGPlayer *rpgPlayer = nullptr;
    Menu *menu;

    int width;
    int height;

    int fadeoutProgress = 0;

    bool running;
    bool debug = false;
    int count;
    Uint32 frameCount, lastFrameTicks;

    int numberOfKeys = 100;
    Uint8 *oldKeyStates;

    int currentLevelIndex = 0;
};


#endif //SEMESTRAL_WORK_GAME_H
