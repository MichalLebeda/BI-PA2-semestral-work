//
// Created by michal on 3/11/20.
//

#include <SDL_timer.h>
#include "Animation.h"
#include "PlayerAnimFrame.h"

template
class Animation<TextureRegion>;

template
class Animation<PlayerAnimFrame>;

template<class T>
Animation<T>::Animation(vector<T *> *frames, uint32_t deltaMs, int repeats):
        repeats(repeats),
        deltaMs(deltaMs),
        frames(frames) {
}

template<class T>
T *Animation<T>::getFrame(uint32_t referenceTime) {
    if (repeats != 0 && referenceTime >= getLength()) {
        return frames->back();
    }

    return frames->at((referenceTime / deltaMs) % frames->size());
}

template<class T>
uint32_t Animation<T>::getLength() {
    if (repeats == 0) {
        return getLengthNoRepeats();
    }

    return deltaMs * frames->size() * repeats;
}

template<class T>
uint32_t Animation<T>::getLengthNoRepeats() {
    return deltaMs * frames->size();
}
