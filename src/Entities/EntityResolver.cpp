//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include "EntityResolver.h"

std::vector <BasicEnemy*> EntityResolver::GetEnemies() {
    return enemies;
}

std::vector <Projectile*> EntityResolver::GetProjectiles() {
    return projectiles;
}

void EntityResolver::RegisterEnemy(BasicEnemy *enemy) {
    enemies.push_back(enemy);
}

void EntityResolver::RegisterPlayer(Player *player) {
    this->player = player;
}

void EntityResolver::RegisterProjectile(Projectile *projectile) {
    projectiles.push_back(projectile);
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

void EntityResolver::CleanEnemies(){
    std::vector<BasicEnemy*> newEnemies;

    for (auto enemy : enemies) {
        if(enemy->GetToDelete())
        {
            delete enemy;
        }else
        {
            newEnemies.push_back(enemy);
        }
    }

    enemies.clear();

    enemies = newEnemies;
}

//TODO could be a template method?
void EntityResolver::CleanProjectiles(){
    std::vector<Projectile*> newProjectiles;

    for (auto projectile : projectiles) {
        if(projectile->GetToDelete())
        {
            delete projectile;
        }else
        {
            newProjectiles.push_back(projectile);
        }
    }

    projectiles.clear();

    projectiles = newProjectiles;
}


void EntityResolver::DeletePlayer() {
    delete player;
}
