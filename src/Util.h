//
// Created by michal on 3/10/20.
//
#include <string>

#ifndef SEMESTRAL_WORK_UTIL_H
#define SEMESTRAL_WORK_UTIL_H

enum ENTITY_TYPE {
    STAIRS_DOWN, STAIRS_UP, PLAYER, ITEM, ENEMY, PLAYER_ATTACK_HITBOX
};

static const double DEFAULT_ZOOM = 0.24f;
static const int UNITS_PER_METER = 256;
static const int PIXELS_PER_METER = 16;
static const int PLAYER_UNITS_PER_TICK = UNITS_PER_METER / PIXELS_PER_METER * 1;

static const int COLLISION_SPACE = 1;

static const int LEVELS_TOTAL = 5;

static const float DISTANCE_TILE_MIN_DIST = 300;
static const float DISTANCE_TILE_MAX_DIST = 500;

static const int SLOT_BG_INDEX = 81;
static const int SLOT_BG_EQUIPPED_INDEX = 82;
static const int SLOT_BG_CONSUMABLE_INDEX = 83;

static const std::string PLAYER_FILENAME = "save/player.save";

/**
 * @brief Convert meters to game units
 * @param meters    Meters to convert
 * @return Game units
 */
int metersToUnits(float meters);

/**
 * @brief Convert meters to game units
 * @param meters    Meters to convert
 * @return game units
 */
int metersToUnits(int meters);

/**
 * @brief Convert pixels to units
 * @param pixels Pixelart pixels to convert
 * @return game units
 */
int pixelsToUnits(int pixels);

/**
 * @brief Interpolate between two values based on percentage
 * @param start Start value
 * @param end End value
 * @param percents Percentage in range <0,1>
 * @return
 */
float lerp(float start, float end, float percents);

#endif //SEMESTRAL_WORK_UTIL_H
