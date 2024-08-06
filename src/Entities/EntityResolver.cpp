//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include "EntityResolver.h"

std::vector <BasicEnemy*> EntityResolver::GetEnemies() {
    return enemies;
}

void EntityResolver::RegisterEnemy(BasicEnemy *enemy) {
    enemies.push_back(enemy);
}

void EntityResolver::RegisterPlayer(Player *player) {
    this->player = player;
}

Player *EntityResolver::GetPlayer() {
    return player;
}

void EntityResolver::DeleteEnemies(){
    for (auto enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

    std::vector<BasicEnemy*> newEnemies;
    enemies = newEnemies;
}

void EntityResolver::DeletePlayer() {
    delete player;
}
