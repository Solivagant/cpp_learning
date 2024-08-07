//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include "EntityResolver.h"
#include <iostream>
#include <sstream>

std::vector<BasicEnemy *> EntityResolver::GetEnemies() {
    return enemies;
}

std::vector<Projectile *> EntityResolver::GetProjectiles() {
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

void EntityResolver::DeleteEnemies() {
    for (auto enemy: enemies) {
        delete enemy;
    }

    //alternative to calling .clear(): swap with the contents of an empty vector
    std::vector<BasicEnemy *>().swap(enemies);

    std::vector<BasicEnemy *> newEnemies;
    enemies = newEnemies;
}

void EntityResolver::CleanEnemies() {
    std::vector<BasicEnemy *> newEnemies;

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

//TODO could be a template method?
void EntityResolver::CleanProjectiles() {
    std::vector<Projectile *> newProjectiles;

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

void EntityResolver::GenerateEnemies(int count) {
    std::random_device rd;
    std::mt19937 e{rd()};
    std::uniform_int_distribution<int> distW = std::uniform_int_distribution<int>(0, screenWidth);
    std::uniform_int_distribution<int> distH = std::uniform_int_distribution<int>(0, screenHeight);

    for (int i = 0; i < count; ++i) {
        Vector2 randomPosition{float(distW(e)), float(distH(e))};

        while (Vector2Distance(randomPosition, GetPlayer()->GetPosition()) <=
               (Player::Radius + Projectile::Radius + Projectile::AvoidanceBonus)) {
            randomPosition = Vector2{float(distW(e)), float(distH(e))};
        }

        auto *basicEnemy = new BasicEnemy(randomPosition);
        RegisterEnemy(basicEnemy);
    }
}
