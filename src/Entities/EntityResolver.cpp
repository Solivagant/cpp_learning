//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include "EntityResolver.h"
#include "../Util/EntityPool.h"
#include <iostream>

EntityResolver::EntityResolver(){
}

std::vector<std::shared_ptr<BasicEnemy>> EntityResolver::GetEnemies() {
    return enemies;
}

std::vector<Projectile*> EntityResolver::GetProjectiles() {
    return projectiles;
}

std::shared_ptr<BasicEnemy> EntityResolver::AcquireEnemy()
{
    return enemyPool.acquire();
}

void EntityResolver::RegisterEnemy(std::shared_ptr<BasicEnemy>  enemy) {
    enemies.push_back(enemy);
}

void EntityResolver::RegisterPlayer(Player* player) {
    this->player = player;
}

void EntityResolver::RegisterProjectile(Projectile* projectile) {
    projectiles.push_back(projectile);
}

Player* EntityResolver::GetPlayer() {
    return player;
}

void EntityResolver::DeleteEnemies() {
    enemies.clear();
}

void EntityResolver::CleanEnemies() {
    std::vector<std::shared_ptr<BasicEnemy>> newEnemies;
    newEnemies.clear();

    for (auto enemy: enemies) {
        if (!enemy->GetToDelete()) {
            newEnemies.push_back(enemy);
        }
    }

    enemies.clear();

    enemies = newEnemies;
}

void EntityResolver::CleanProjectiles() {
    std::vector<Projectile*> newProjectiles;

    for (auto projectile: projectiles) {
        if (projectile->GetToDelete()) {
            delete projectile;
        } else {
            newProjectiles.push_back(projectile);
        }
    }

    projectiles.clear();
    projectiles = newProjectiles;
}

void EntityResolver::FreeMemory() {
    delete player;

    DeleteEnemies();
}

