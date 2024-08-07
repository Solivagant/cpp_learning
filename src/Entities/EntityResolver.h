//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_ENTITYRESOLVER_H
#define CPP_LEARNING_ENTITYRESOLVER_H

#include <random>
#include <vector>
#include "Player.h"
#include "BasicEnemy.h"
#include "Projectile.h"
#include "../../lib/raylib.h"
#include "../../lib/raymath.h"

// Forward declaration of BasicEnemy

class EntityResolver {
public:
    void RegisterPlayer(Player* player);
    void RegisterEnemy(BasicEnemy* enemy);
    Player* GetPlayer();
    std::vector<BasicEnemy*> GetEnemies();
    std::vector<Projectile *> GetProjectiles();
    void DeleteEnemies();
    void CleanEnemies();
    void CleanProjectiles();

    void DeletePlayer();
    void RegisterProjectile(Projectile *projectile);
    void FreeMemory();
    void GenerateEnemies(int count);
    void InitRand(int screenWidth, int screenHeight);
private:
    std::vector<BasicEnemy*> enemies;
    std::vector<Projectile*> projectiles;
    Player* player;
    int screenWidth;
    int screenHeight;
};

#endif //CPP_LEARNING_ENTITYRESOLVER_H
