//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include "EntityResolver.h"
#include <iostream>
#include <sstream>

void SpawnBlowUpEnemies(Vector2 position, std::vector<BasicEnemy*> enemies, EntityResolver* entityResolver);

std::vector<BasicEnemy*> EntityResolver::GetEnemies() {
    return enemies;
}

std::vector<Projectile*> EntityResolver::GetProjectiles() {
    return projectiles;
}

void EntityResolver::RegisterEnemy(BasicEnemy* enemy) {
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
    std::vector<BasicEnemy*>().swap(enemies);

    std::vector<BasicEnemy*> newEnemies;
    enemies = newEnemies;
}

void EntityResolver::CleanEnemies() {
    std::vector<BasicEnemy*> newEnemies;

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

void EntityResolver::GenerateEnemies(int count) {
    std::random_device rd;
    std::mt19937 e{rd()};

    //Points above player
    auto playerPos = player->GetPosition();

//    All points above player at this y (with a 20 pixels deviation added later)
    auto abovePlayer = playerPos.y - (float) screenHeight / 2.0f;
    auto belowPlayer = playerPos.y + (float) screenHeight / 2.0f;

    auto leftOfPlayer = playerPos.x - (float) screenWidth / 2.0f;
    auto rightOfPlayer = playerPos.x + (float) screenWidth / 2.0f;

    //and between this x
    auto widthAroundPlayer = playerPos.x - (float) screenWidth / 2.0f + playerPos.x + (float) screenWidth / 2.0f;

    std::uniform_int_distribution<int> abovePlayerDist = std::uniform_int_distribution<int>((int) abovePlayer,
                                                                                            (int) abovePlayer + 20);
    std::uniform_int_distribution<int> belowPlayerDist = std::uniform_int_distribution<int>((int) belowPlayer,
                                                                                            (int) belowPlayer + 20);
    std::uniform_int_distribution<int> aroundPlayerXDist = std::uniform_int_distribution<int>((int) leftOfPlayer,
                                                                                              (int) rightOfPlayer);

    std::uniform_int_distribution<int> leftOfPlayerDist = std::uniform_int_distribution<int>((int) leftOfPlayer,
                                                                                             (int) leftOfPlayer + 20);
    std::uniform_int_distribution<int> rightOfPlayerDist = std::uniform_int_distribution<int>((int) rightOfPlayer,
                                                                                              (int) rightOfPlayer + 20);
    std::uniform_int_distribution<int> aroundPlayerYDist = std::uniform_int_distribution<int>((int) abovePlayer,
                                                                                              (int) belowPlayer);

    for (int i = 0; i < count; ++i) {
        //Random position above the screen
        Vector2 randomPosAbove{float(aroundPlayerXDist(e)), float(abovePlayerDist(e))};
        auto* basicEnemy = new BasicEnemy(randomPosAbove);
        RegisterEnemy(basicEnemy);

        //Random position below the screen
        Vector2 randomPosBelow{float(aroundPlayerXDist(e)), float(belowPlayerDist(e))};
        basicEnemy = new BasicEnemy(randomPosBelow);
        RegisterEnemy(basicEnemy);

        //Random position to the left of the screen
        Vector2 randomPosLeft{float(leftOfPlayerDist(e)), float(aroundPlayerYDist(e))};
        basicEnemy = new BasicEnemy(randomPosLeft);
        RegisterEnemy(basicEnemy);

        //Random position to the right of the screen
        Vector2 randomPosRight{float(rightOfPlayerDist(e)), float(aroundPlayerYDist(e))};
        basicEnemy = new BasicEnemy(randomPosRight);
        RegisterEnemy(basicEnemy);
    }
}

void EntityResolver::BlowUpEnemies() {
    t1 = std::thread(SpawnBlowUpEnemies, player->GetPosition(), enemies, this);
    t1.join();
}

void EntityResolver::Shutdown() {
}

bool CompareByDistance(BasicEnemy* a, BasicEnemy* b, Vector2 referencePoint) {
    float distanceA = Vector2Distance(a->GetPosition(), referencePoint);
    float distanceB = Vector2Distance(b->GetPosition(), referencePoint);
    return distanceA < distanceB;
}

void SpawnBlowUpEnemies(Vector2 position, std::vector<BasicEnemy*> enemies, EntityResolver* entityResolver) {
    //Sort enemies by position closest to player
    std::sort(enemies.begin(), enemies.end(), [&](BasicEnemy* a, BasicEnemy* b) {
        return CompareByDistance(a, b, position);
    });

    for (auto enemy: enemies) {
        enemy->MarkDying(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(enemies.size() / 10));
    }
    entityResolver->DeleteEnemies();
}

