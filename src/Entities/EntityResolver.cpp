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
