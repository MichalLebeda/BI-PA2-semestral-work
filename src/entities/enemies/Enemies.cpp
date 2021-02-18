//
// Created by michal on 4/27/20.
//

#include "Enemies.h"
#include "Bird.h"
#include "Ghost.h"

Enemies::Enemies(const Assets *assets, PhysWorld *world, Player *player) :
        assets(assets),
        world(world),
        player(player) {

}

void Enemies::render(CameraRenderer *renderer) {
    for (auto it = enemies.cbegin(); it != enemies.cend();) {
        if (it->second->toBeRemoved()) {
            it->second->getBody()->setToBeRemoved(true);
            delete it->second;
            enemies.erase(it++);
            player->getRpgComponent()->incrementKilledEnemyCount();
        } else {
            it->second->render(renderer);
            ++it;
        }
    }
}

void Enemies::addEnemy(Enemy *enemy) {
    enemies.insert(make_pair(enemy->getBody(), enemy));
}

Enemy *Enemies::getByBody(PhysBody *body) {
    auto it = enemies.find(body);

    if (it == enemies.end()) {
        throw runtime_error("No enemy found with this body addr: ");
    }

    return it->second;
}

void Enemies::serialize(std::ostream &os) const {
    os << enemies.size() << endl;

    for (auto it:enemies) {
        os << it.second->getId() << " ";
        os << it.second->getBody()->getX() << " ";
        os << it.second->getBody()->getY() << " ";
        os << it.second->getRpgComponent()->getHealth() << endl;
    }
}

void Enemies::deserialize(std::istream &is) {
    int amount;

    int id;
    int x;
    int y;
    int health;

    is >> amount;

    for (int i = 0; i < amount; i++) {
        is >> id;
        is >> x;
        is >> y;
        is >> health;

        if (health < 0) {
            addEnemy(id, x, y);
        } else {
            addEnemy(id, x, y, health);
        }
    }
}

Enemy *Enemies::addEnemy(int id, int x, int y) {
    Enemy *enemy;
    switch (id) {
        case BIRD:
            enemy = new Bird(assets, x, y, world, player);
            break;
        case GHOST:
            enemy = new Ghost(assets, x, y, world, player);
            break;
        default:
            throw runtime_error(string("No such enemy for id: ").append(to_string(id).c_str()));
    }

    addEnemy(enemy);
    return enemy;
}

Enemy *Enemies::addEnemy(int id, int x, int y, int health) {
    Enemy *enemy = addEnemy(id, x, y);
    enemy->getRpgComponent()->setHealth(health);
    return enemy;
}

Enemies::~Enemies() {
    for (auto it: enemies) {
        delete it.second;
    }
}

