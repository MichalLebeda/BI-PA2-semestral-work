//
// Created by michal on 3/11/20.
//

#include "Player.h"
#include "../Game.h"

Player::Player(const Assets *assets, int x, int y, RPGPlayer *rpgPlayer, PhysWorld *world)
        : PhysicalEntity(assets->playerIdleDownAnim->getFrame(0)->bodyRegion,
                         x,
                         y,
                         metersToUnits(0.6f),
                         metersToUnits(0.4f),
                         true,
                         world),
          weaponSprite(assets->itemRegions.at(rpgPlayer->getWeapon()->getId())),
          world(world) {
    this->rpgPlayer = rpgPlayer;
    alignSpriteTopCenter();

    body->setAutoFreeze(true);
    body->setIdentifier(ENTITY_TYPE::PLAYER);

    this->assets = assets;
    this->animation = assets->playerIdleDownAnim;
}

Player::~Player() {
    rpgPlayer->setWorldPosition(body->getX(), body->getY());
}

void Player::render(CameraRenderer *renderer) {
    sprite->setXCenterBased(body->getCenterX());
    sprite->setY(body->getCenterY() - sprite->getHeight());

    switch (state) {
        case IDLE:
            if (abs(body->getLastStepVelocityX()) + abs(body->getLastStepVelocityY()) > 1) {
                setState(RUNNING);
            }
            break;
        case RUNNING:
            if ((abs(body->getLastStepVelocityX()) + abs(body->getLastStepVelocityY()) <= 1)) {
                setState(IDLE);
            } else {
                if (direction == UP || direction == RIGHT) {
                    animation = assets->playerRunningUpAnim;
                } else {
                    animation = assets->playerRunningDownAnim;
                }
            }
            break;
        case ATTACKING:
            if (time > animation->getLength()) {
                setState(IDLE);
            }
    }

    time += tickDelta;
    sprite->setRegion(animation->getFrame(time)->bodyRegion);
    updateSpritePosition();

    renderer->renderRegionImmediately(assets->shadowRegion, sprite->getX(),
                                      sprite->getY() + sprite->getWidth() / 2,
                                      sprite->getWidth(),
                                      sprite->getWidth());

    if (state != ATTACKING) {
        weaponSprite.setRegion(assets->itemRegions.at(rpgPlayer->getWeapon()->getRegionIndex()));

        if (direction == UP || direction == RIGHT) {
            weaponSprite.setPosition(sprite->getX()
                                     + pixelsToUnits(11)
                                     + pixelsToUnits(ceil(weaponSprite.getRegion()->getRect()->w / 2)),
                                     sprite->getY());
        } else {
            weaponSprite.setPosition(sprite->getX()
                                     + pixelsToUnits(ceil(weaponSprite.getRegion()->getRect()->w / 2)),
                                     sprite->getY());
        }

        renderer->renderLaterDepthSorted(weaponSprite.getRegion(), *(weaponSprite.getRect()),
                                         sprite->getY() + sprite->getHeight() - 1);
    }

    renderer->renderLaterDepthSorted(sprite->getRegion(), *sprite->getRect());
    sprite->setRegion(animation->getFrame(time)->shirtRegion);
    renderer->renderLaterDepthSorted(sprite->getRegion(), *sprite->getRect(), rpgPlayer->getShirt()->getColorTint());
    sprite->setRegion(animation->getFrame(time)->pantsRegion);
    renderer->renderLaterDepthSorted(sprite->getRegion(), *sprite->getRect(), rpgPlayer->getPants()->getColorTint());
}

void Player::setState(Player::State nextState) {
    if (state != nextState) {
        if (state == ATTACKING && time < animation->getLength()) {
            return;
        }

        switch (nextState) {
            case IDLE:
                if (direction == UP || direction == RIGHT) {
                    animation = assets->playerIdleUpAnim;
                } else {
                    animation = assets->playerIdleDownAnim;
                }
                break;
            case RUNNING:
                if (direction == UP || direction == RIGHT) {
                    animation = assets->playerRunningUpAnim;
                } else {
                    animation = assets->playerRunningDownAnim;
                }
                break;
            case ATTACKING:
                switch (direction) {
                    case LEFT:
                        animation = assets->playerAttackLeftAnim;
                        break;
                    case RIGHT:
                        animation = assets->playerAttackRightAnim;
                        break;
                    case UP:
                        animation = assets->playerAttackUpAnim;
                        break;
                    case DOWN:
                        animation = assets->playerAttackDownAnim;
                        break;
                }
        }

        state = nextState;
        time = 0;
    }
}

void Player::setPosition(int worldX, int worldY) {
    body->setPosition(worldX, worldY);
}

RPGPlayer *Player::getRpgComponent() {
    return rpgPlayer;
}

PhysBody *Player::createAttackHitbox() {
    PhysBody *attackHitbox = new PhysBody(body->getCenterX() - metersToUnits(0.8f) / 2,
                                          body->getCenterY() - metersToUnits(0.8f) / 2,
                                          metersToUnits(0.8f), metersToUnits(0.8f));
    attackHitbox->setSensor(true);
    attackHitbox->setIdentifier(ENTITY_TYPE::PLAYER_ATTACK_HITBOX);
    attackHitbox->setToBeRemoved(true);
    world->addBody(attackHitbox);
    return attackHitbox;
}

void Player::attackLeft() {
    if (state != ATTACKING) {
        createAttackHitbox()->setLeft(body->getShape());
        direction = LEFT;
        setState(ATTACKING);
    }
}

void Player::attackRight() {
    if (state != ATTACKING) {
        createAttackHitbox()->setRight(body->getShape());
        direction = RIGHT;
        setState(ATTACKING);
    }
}

void Player::attackUp() {
    if (state != ATTACKING) {
        createAttackHitbox()->setTop(body->getShape());
        direction = UP;
        setState(ATTACKING);
    }
}

void Player::attackDown() {
    if (state != ATTACKING) {
        createAttackHitbox()->setBottom(body->getShape());
        direction = DOWN;
        setState(ATTACKING);
    }
}

void Player::goLeft() {
    direction = LEFT;
    body->setVelocityX(-PLAYER_UNITS_PER_TICK);
}

void Player::goRight() {
    direction = RIGHT;
    body->setVelocityX(PLAYER_UNITS_PER_TICK);
}

void Player::goDown() {
    direction = DOWN;
    body->setVelocityY(PLAYER_UNITS_PER_TICK);
}

void Player::goUp() {
    direction = UP;
    body->setVelocityY(-PLAYER_UNITS_PER_TICK);
}
