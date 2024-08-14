//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include "EntityResolver.h"
#include <iostream>
#include <sstream>

std::vector<EnemyA*> EntityResolver::GetEnemies() {
    return enemies;
}

std::vector<Projectile*> EntityResolver::GetProjectiles() {
    return projectiles;
}

void EntityResolver::RegisterEnemy(EnemyA* enemy) {
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
    for (auto enemy: enemies) {
        delete enemy;
    }

    //alternative to calling .clear(): swap with the contents of an empty vector
    std::vector<EnemyA*>().swap(enemies);
    std::vector<EnemyA*> newEnemies;
    enemies = newEnemies;
}

void EntityResolver::CleanEnemies() {
    std::vector<EnemyA*> newEnemies;

    for (auto enemy: enemies) {
        if (enemy->GetToDelete()) {
            delete enemy;
        } else {
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

void EntityResolver::InitRand(int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
}

void EntityResolver::Shutdown() {
}
