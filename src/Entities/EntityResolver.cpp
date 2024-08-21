//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include "EntityResolver.h"
#include <iostream>

std::vector<std::shared_ptr<BasicEnemy>> EntityResolver::GetEnemies() {
    return enemies;
}

std::vector<std::shared_ptr<Projectile>> EntityResolver::GetProjectiles() {
    return projectiles;
}

std::shared_ptr<BasicEnemy> EntityResolver::AcquireEnemy() {
    auto enemy = enemyPool.acquire();
    enemies.push_back(enemy);
    return enemy;
}

std::shared_ptr<Projectile> EntityResolver::AcquireProjectile() {
    auto projectile = projectilePool.acquire();
    projectiles.push_back(projectile);
    return projectile;
}

void EntityResolver::RegisterPlayer(Player* player) {
    this->player = player;
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
    std::vector<std::shared_ptr<Projectile>> newProjectiles;

    for (auto projectile: projectiles) {
        if (!projectile->GetToDelete()) {
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

