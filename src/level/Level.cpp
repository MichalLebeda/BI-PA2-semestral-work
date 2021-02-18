//
// Created by michal on 3/9/20.
//

#include <fstream>
#include "Level.h"
#include "../entities/DepthSortedSprite.h"
#include "AnimatedTile.h"
#include "DistanceTile.h"

Level::WorldContactListenerImpl::WorldContactListenerImpl(Level *level) {
    this->level = level;
}

void Level::WorldContactListenerImpl::onContact(PhysBody *bodyA, PhysBody *bodyB) {
    if (isInContact(ENTITY_TYPE::PLAYER, bodyA, bodyB)) {
        if (isInContact(ENTITY_TYPE::STAIRS_DOWN, bodyA, bodyB)) {
            level->setRequest(GO_LEVEL_DOWN);
        } else if (isInContact(ENTITY_TYPE::STAIRS_UP, bodyA, bodyB)) {
            level->setRequest(GO_LEVEL_UP);
        } else if (isInContact(ENTITY_TYPE::ITEM, bodyA, bodyB)) {
            level->setBodyUnderPlayer(getFromContact(ENTITY_TYPE::ITEM, bodyA, bodyB));
        }
    } else if (isInContact(ENTITY_TYPE::PLAYER_ATTACK_HITBOX, bodyA, bodyB)) {
        if (isInContact(ENTITY_TYPE::ENEMY, bodyA, bodyB)) {
            PhysBody *enemyBody = getFromContact(ENTITY_TYPE::ENEMY, bodyA, bodyB);

            Enemy *enemy = level->enemies->getByBody(enemyBody);
            enemy->handleDamage(level->player->getRpgComponent());

        }
    }
}

Level::Level(int index, const string &mapFilename,
             const Assets *assets,
             CameraRenderer *renderer,
             PlayerLocation location,
             RPGPlayer *rpgPlayer) :
        index(index),
        filename(mapFilename),
        assets(assets) {

    initializeWorld();

    ifstream inputFile;
    inputFile.open(mapFilename);

    if (!inputFile.is_open()) {
        cerr << "Cannot open map file: " << mapFilename << endl;
    }

    if (rpgPlayer->isFromFile() && location == LOADED_FROM_FILE) {
        player = new Player(assets, rpgPlayer->getStoredWorldX(), rpgPlayer->getStoredWorldY(), rpgPlayer, world);
    } else {
        player = new Player(assets, metersToUnits(5), metersToUnits(5), rpgPlayer, world);
    }

    enemies = new Enemies(assets, world, player);

    loadGridDimensions(inputFile);

    allocateGrid();

    loadFloorTileLayer(inputFile);

    loadSecondTileLayer(inputFile);

    loadCollisionLayer(inputFile, location);

    ifstream itemPatchFile;
    itemPatchFile.open(getPatchPath(index));

    if (itemPatchFile.is_open()) {
        loadItems(itemPatchFile);
        enemies->deserialize(itemPatchFile);
    } else {
        loadItems(inputFile);
        enemies->deserialize(inputFile);
    }

    //loading is now completed even if items were loaded from original file not patch
    inputFile.close();

    renderer->setPosition(player->getBody()->getCenterX(), player->getBody()->getCenterY());

    if (index == 1) {
        bgColor = SDL_Color{104, 111, 153, 255};
    } else {
        bgColor = SDL_Color{58, 63, 94, 255};
    }
}

Level::~Level() {
    ofstream patchFile;
    patchFile.open(getPatchPath(index));
    save(patchFile);
    patchFile.close();

    delete player;
    delete world;
    delete worldContactListener;
    delete enemies;

    for (auto it:items) {
        delete it;
    }

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            delete tiles[x][y];
        }
        delete[] tiles[x];
    }
    delete[] tiles;
}

void Level::render(CameraRenderer *renderer) {
    setBodyUnderPlayer(nullptr);

    world->step();

    renderer->lookAt(player->getBody()->getCenterX(),
                     player->getBody()->getCenterY());
    renderer->updateRect();

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            tiles[x][y]->render(renderer);
        }
    }

    for (size_t i = 0; i < items.size(); i++) {
        Item *item = items.at(i);
        if (item->getBody()->isToBeRemoved()) {
            delete item;
            items.erase(items.begin() + i);
            i--;
        } else {
            item->render(renderer);
        }
    }

    enemies->render(renderer);

    player->render(renderer);

    renderer->renderZOrdered();


    if (bodyUnderPlayer != nullptr && bodyUnderPlayer->isToBeRemoved()) {
        setBodyUnderPlayer(nullptr);
    }
    world->removeJunkBodies();
}

void Level::renderDebug(CameraRenderer *renderer) {
    worldDebugRenderer.render(renderer);
}

int Level::getWidth() const {
    return width;
}

int Level::getHeight() const {
    return height;
}

PhysWorld *Level::getWorld() const {
    return world;
}

Level::Request Level::getRequest() const {
    return request;
}

void Level::setRequest(Level::Request request) {
    Level::request = request;
}

void Level::loadInt(ifstream &stream, int &read) {
    stream >> read;

    if ((stream.fail() || stream.bad())) {
        badMap();
    }
}

void Level::loadGridDimensions(ifstream &file) {
    loadInt(file, width);
    loadInt(file, height);
}

void Level::allocateGrid() {
    //initialize tile grid
    tiles = new Tile **[width];
    for (int x = 0; x < width; x++) {
        tiles[x] = new Tile *[height];
    }
}

void Level::loadFloorTileLayer(ifstream &stream) {
    int read;

    //load tiles
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            loadInt(stream, read);

            if (read == 103) {
                tiles[x][y] = new DistanceTile(assets->tile103Anim,
                                               metersToUnits(x),
                                               metersToUnits(y), player);
            } else if (read == 222) {
                tiles[x][y] = new AnimatedTile(assets->tile222Anim,
                                               metersToUnits(x),
                                               metersToUnits(y));

            } else if (read == 237) {
                tiles[x][y] = new DistanceTile(assets->tile237Anim,
                                               metersToUnits(x),
                                               metersToUnits(y), player);
            } else {
                tiles[x][y] = new Tile(assets->tileRegions.at(read - 1),
                                       metersToUnits(x),
                                       metersToUnits(y));
            }
        }
    }
}

void Level::badMap() {
    throw runtime_error("Error reading map. There is something wrong with the map file. Try reinstalling");
}

void Level::initializeWorld() {
    world = new PhysWorld();
    worldContactListener = new WorldContactListenerImpl(this);
    world->setContactListener(worldContactListener);
    worldDebugRenderer.setWorld(world);
}

void Level::loadSecondTileLayer(ifstream &stream) {
    int read;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            loadInt(stream, read);

            if (read == 0) {
                continue;
            }

            try {

                DepthSortedSprite *item = new DepthSortedSprite(assets->wallRegions.at(read - 1),
                                                                metersToUnits(x),
                                                                metersToUnits(y - 1));
                tiles[x][y]->setWall(item);
            } catch (const std::out_of_range &e) {
                badMap();
            }
        }
    }
}

void Level::loadCollisionLayer(ifstream &stream, PlayerLocation location) {
    int numberOfCollisionRects;
    int x;
    int y;
    int rectW;
    int rectH;
    int id;

    loadInt(stream, numberOfCollisionRects);

    for (int i = 0; i < numberOfCollisionRects; i++) {
        loadInt(stream, x);
        loadInt(stream, y);
        loadInt(stream, rectW);
        loadInt(stream, rectH);
        loadInt(stream, id);

        switch (id) {
            //WALL
            case 0: {
                auto *body = new PhysBody(PIXELS_PER_METER * x,
                                          PIXELS_PER_METER * y,
                                          PIXELS_PER_METER * rectW,
                                          PIXELS_PER_METER * rectH);
                body->setDynamic(false);
                world->addBody(body);
                break;
            }
                //STAIRS DOWN
            case -1: {
                auto *body = new PhysBody(PIXELS_PER_METER * x,
                                          PIXELS_PER_METER * y,
                                          PIXELS_PER_METER * rectW,
                                          PIXELS_PER_METER * rectH);

                if (location == PlayerLocation::NEXT_TO_STAIRS_DOWN) {
                    if (body->getWidth() > body->getHeight()) {
                        player->setPosition(body->getX() + body->getWidth() / 2 - player->getBody()->getHeight() / 2,
                                            body->getY() + body->getHeight());
                    } else {
                        player->setPosition(body->getX() + body->getWidth() + metersToUnits(0.1f),
                                            body->getY() + body->getHeight() / 2 - player->getBody()->getHeight() / 2);
                    }
                }
                body->setDynamic(false);
                body->setIdentifier(ENTITY_TYPE::STAIRS_DOWN);
                world->addBody(body);
                break;
            }
                //STAIRS UP
            case 1: {
                auto *body = new PhysBody(PIXELS_PER_METER * x,
                                          PIXELS_PER_METER * y,
                                          PIXELS_PER_METER * rectW,
                                          PIXELS_PER_METER * rectH);

                if (location == PlayerLocation::NEXT_TO_STAIRS_UP) {
                    if (body->getWidth() > body->getHeight()) {
                        player->setPosition(body->getX() + body->getWidth() / 2 - player->getBody()->getHeight() / 2,
                                            body->getY() - player->getBody()->getHeight());
                    } else {
                        player->setPosition(body->getX() - player->getBody()->getWidth() - metersToUnits(0.1f),
                                            body->getY() + body->getHeight() / 2 - player->getBody()->getHeight() / 2);
                    }
                }
                body->setDynamic(false);
                body->setIdentifier(ENTITY_TYPE::STAIRS_UP);
                world->addBody(body);
                break;
            }
            default:
                badMap();
        }
    }
}

Player *Level::getPlayer() {
    return player;
}

void Level::setBodyUnderPlayer(PhysBody *body) {
    bodyUnderPlayer = body;
}

void Level::pickupItemUnderPlayer() {
    if (bodyUnderPlayer != nullptr) {
        RPGItem *item = bodyUnderPlayer->getItem();
        RPGPlayer *rpgPlayer = getPlayer()->getRpgComponent();

        if (item->getType() == RPGItem::CONSUMABLE) {
            rpgPlayer->getInventory()->add(item);
            bodyUnderPlayer->setItem(nullptr);
            bodyUnderPlayer->setToBeRemoved(true);
        } else {
            RPGItem *replacedItem;

            switch (item->getType()) {
                case RPGItem::PANTS:
                    replacedItem = rpgPlayer->getPants();
                    break;
                case RPGItem::WEAPON:
                    replacedItem = rpgPlayer->getWeapon();
                    break;
                case RPGItem::SHIRT :
                    replacedItem = rpgPlayer->getShirt();
                    break;
                default:
                    throw runtime_error(string("error, no such item type").append(to_string(item->getType()).c_str()));
            }

            rpgPlayer->equip(item);

            if (replacedItem->isTemporal()) {
                bodyUnderPlayer->setItem(nullptr);
                bodyUnderPlayer->setToBeRemoved(true);
                delete replacedItem;
            } else {
                bodyUnderPlayer->setItem(replacedItem);
            }
        }
    }
}

const RPGItem *Level::getItemUnderPlayer() {
    if (bodyUnderPlayer != nullptr) {
        return bodyUnderPlayer->getItem();
    }

    return nullptr;
}

void Level::save(ostream &os) {
    saveItems(os);
    enemies->serialize(os);
}

void Level::saveItems(ostream &os) {
    os << items.size() << endl;

    for (auto it:items) {
        os << it->getId() << " ";
        os << (it->getTileX()) << " ";
        os << (it->getTileY()) << " " << endl;
    }
    os << " " << endl;
}

void Level::loadItems(istream &is) {
    int amount;

    int id;
    int x;
    int y;

    is >> amount;

    for (int i = 0; i < amount; i++) {
        is >> id;
        is >> x;
        is >> y;
        RPGItem *rpgItem = RPGItem::createItem(id);

        Item *item = new Item(x, y, rpgItem, world, assets);
        items.push_back(item);
    }
}

SDL_Color &Level::getBgColor() {
    return bgColor;
}

string Level::getPatchPath(int index) {
    return std::string("save/").append(
            std::to_string(index).append(".patch"));
}
