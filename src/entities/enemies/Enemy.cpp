//
// Created by michal on 4/26/20.
//

#include "Enemy.h"
#include "../../Game.h"

Enemy::Enemy(const Assets *assets, Animation<TextureRegion> *anim,
             int x, int y,
             int bodyWidth, int bodyHeight,
             int health,
             int healthMax,
             int defense,
             int attack,
             PhysWorld *world, Player *player) : PhysicalEntity(anim->getFrame(0),
                                                                x, y,
                                                                bodyWidth, bodyHeight,
                                                                true,
                                                                world),
                                                 shadowRegion(assets->shadowRegion),
                                                 anim(anim),
                                                 player(player),
                                                 assets(assets) {

    body->setIdentifier(ENTITY_TYPE::ENEMY);
    alignSpriteTopCenter();

    rpgCharacter = new RPGCharacter();
    rpgCharacter->setMaxHealth(healthMax);
    rpgCharacter->setHealth(health);
    rpgCharacter->setDefense(defense);
    rpgCharacter->setAttack(attack);

    prepareNextAttack();
}

float Enemy::toPlayerDistance() {
    float deltaX, deltaY;
    deltaX = (float) (player->getBody()->getCenterX() - body->getCenterX());
    deltaY = (float) (player->getBody()->getCenterY() - body->getCenterY());

    return sqrt(deltaX * deltaX + deltaY * deltaY);
}

SDL_Point Enemy::getVecToPlayer() {
    float deltaX, deltaY;
    deltaX = (float) (player->getBody()->getCenterX() - body->getCenterX());
    deltaY = (float) (player->getBody()->getCenterY() - body->getCenterY());

    float length = toPlayerDistance();
    float ratio = length / 10;

    int velX = deltaX / ratio;
    int velY = deltaY / ratio;

    SDL_Point vec{velX, velY};
    return vec;
}

void Enemy::prepareNextAttack() {
    timeUntilNextAttack = 100 + random() % 500;
}

void Enemy::approachPlayer() {
    SDL_Point vec = getVecToPlayer();
    body->setVelocity(vec.x, vec.y);
}

void Enemy::attack() {
    player->getRpgComponent()->handleDamage(rpgCharacter->getAttack());
}

void Enemy::render(CameraRenderer *renderer) {
    switch (state) {
        case WAITING:
            if (toPlayerDistance() < (float) metersToUnits(4)) {
                setState(APPROACHING);
            }
            break;
        case APPROACHING:
            if (toPlayerDistance() < (float) metersToUnits(0.8f) && player->getRpgComponent()->alive()) {
                timeUntilNextAttack -= tickDelta;
                if (timeUntilNextAttack < 0) {
                    prepareNextAttack();
                    setState(ATTACKING);
                }
            } else {
                prepareNextAttack();
                approachPlayer();
            }
            break;
        case ATTACKING:
            if (time > anim->getLength()) {
                setState(APPROACHING);

                attack();
            }
            break;
        case SHOCKED:
            setState(APPROACHING);
            break;
        case DYING:
            break;
    }

    if (rpgCharacter->getHealth() <= 0) {
        setState(DYING);
    }

    time += tickDelta;
    sprite->setRegion(anim->getFrame(time));

    renderer->renderRegionImmediately(shadowRegion, sprite->getX(),
                                      sprite->getY() + sprite->getWidth() / 2,
                                      sprite->getWidth(),
                                      sprite->getHeight());
    PhysicalEntity::render(renderer);

    if (rpgCharacter->alive()) {
        drawHealthBar(renderer);
    }
}

void Enemy::drawHealthBar(CameraRenderer *renderer) {
    SDL_Rect healthBar{sprite->getX() + sprite->getWidth() / 2 - metersToUnits(1) / 2,
                       sprite->getY() - metersToUnits(1) / 10,
                       metersToUnits(1),
                       metersToUnits(1) / 10};

    renderer->renderLaterDepthSorted(assets->healthBarEmptyRegion, healthBar, metersToUnits(999));

    healthBar.w = (int) ((float) healthBar.w * (float) rpgCharacter->getHealth() /
                         (float) rpgCharacter->getMaxHealth());
    renderer->renderLaterDepthSorted(assets->healthBarRegion, healthBar, metersToUnits(1000));

}

RPGCharacter *Enemy::getRpgComponent() {
    return rpgCharacter;
}

Enemy::~Enemy() {
    delete rpgCharacter;
}

void Enemy::handleDamage(RPGCharacter *character) {
    if (state != State::DYING) {
        rpgCharacter->handleDamage(character->getAttack());

        if (rpgCharacter->alive()) {
            setState(SHOCKED);
        } else {
            setState(DYING);
        }

        SDL_Point vec = getVecToPlayer();
        body->setVelocity(-3 * vec.x, -3 * vec.y);
    }
}

void Enemy::setState(Enemy::State nextState) {
    switch (state) {
        case WAITING:
            break;
        case SHOCKED:
            if (state == nextState) {
                time = 0;
                return;
            }
            if (nextState != DYING && time < anim->getLength()) {
                return;
            }
            break;
        case APPROACHING:
            break;
        case DYING:
            return;
        case ATTACKING:
            if (nextState == SHOCKED || nextState == DYING) {
                break;
            }

            if (time < anim->getLength()) {
                return;
            }
            break;
    }

    time = 0;
    switch (nextState) {
        case WAITING:
            break;
        case SHOCKED:
            anim = getShockedAnim();
            break;
        case APPROACHING:
            anim = getApproachingAnim();
            break;
        case DYING:
            anim = getDyingAnim();
            break;
        case ATTACKING:
            anim = getAttackingAnim();
            break;
    }

    state = nextState;
}

bool Enemy::toBeRemoved() {
    return state == DYING && time > getDyingAnim()->getLength();
}
