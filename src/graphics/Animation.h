//
// Created by michal on 3/11/20.
//

#ifndef SEMESTRAL_WORK_ANIMATION_H
#define SEMESTRAL_WORK_ANIMATION_H


#include "TextureRegion.h"
#include <vector>

using namespace std;

/**
 * Template class representing animation
 * @tparam T
 */
template<class T>
class Animation {
public:

    /**
     *
     * @param frames frames of animaiton
     * @param deltaMs delta between frames in milliseconds
     * @param repeats number of repeats, 0 for infinity
     */
    Animation(vector<T *> *frames, uint32_t deltaMs, int repeats);

    /**
     * @brief Get animation frame at reference time
     * @param referenceTime Time reference which frame is based on
     * @return Animation frame
     */
    T *getFrame(uint32_t referenceTime);

    /**
     * @brief Get animation length
     * @return Total duration in milliseconds with repeats took into account (if infinite returns one cycle duration)
     */
    uint32_t getLength();

    /**
     * @brief Get length of animation without repeats
     * @return
     */
    uint32_t getLengthNoRepeats();

private:
    int repeats = 1;
    uint32_t deltaMs;
    vector<T *> *frames;
};


#endif //SEMESTRAL_WORK_ANIMATION_H
