//
// Created by michal on 3/10/20.
//
#include "Util.h"

int metersToUnits(float meters) {
    return meters * UNITS_PER_METER;
}

int metersToUnits(int meters) {
    return meters * UNITS_PER_METER;
}

int pixelsToUnits(int pixels) {
    return pixels * UNITS_PER_METER / PIXELS_PER_METER;
}

float lerp(float start, float end, float percents) {
    return (start * (1.0 - percents)) + (end * percents);
}
