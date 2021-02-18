//
// Created by michal on 3/25/20.
//

#include "Item.h"

Item::Item(int tileX, int tileY, RPGItem *rpgItem, PhysWorld *physWorld, const Assets *assets)
        : PhysicalEntity(assets->itemRegions.at(rpgItem->getRegionIndex())),
          tileX(tileX), tileY(tileY), assets(assets) {

    body = new PhysBody(tileX, tileY, UNITS_PER_METER * 1, UNITS_PER_METER * 1);
    body->setDynamic(false);
    body->setIdentifier(ENTITY_TYPE::ITEM);
    body->setSensor(true);
    body->setItem(rpgItem);
    physWorld->addBody(body);

    body->setWidth(pixelsToUnits(sprite->getRegion()->getRect()->w));
    body->setHeight(pixelsToUnits(sprite->getRegion()->getRect()->h));

    body->setPosition(tileX + pixelsToUnits(16) / 2 - body->getWidth() / 2,
                      tileY + pixelsToUnits(16) / 2 - body->getHeight() / 2);

    alignSpriteCenter();
}

void Item::render(CameraRenderer *renderer) {
    sprite->setRegion(assets->itemRegions.at(body->getItem()->getRegionIndex()));
    updateSpritePosition();

    renderer->setShapeColor(body->getItem()->getColorTint());

    SDL_SetTextureAlphaMod(sprite->getRegion()->getTexture(), 50);
    sprite->translate(pixelsToUnits(-1), pixelsToUnits(1));
    renderer->renderRegionImmediately(sprite->getRegion(), sprite->getRect(), 0, 0, 0);
    sprite->translate(pixelsToUnits(1), pixelsToUnits(-1));
    SDL_SetTextureAlphaMod(sprite->getRegion()->getTexture(), 255);

    renderer->renderRegionImmediately(sprite->getRegion(), sprite->getRect(), &body->getItem()->getColorTint());
}

int Item::getId() {
    return body->getItem()->getId();
}

int Item::getTileX() {
    return tileX;
}

int Item::getTileY() {
    return tileY;
}
