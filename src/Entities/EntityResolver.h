//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_ENTITYRESOLVER_H
#define CPP_LEARNING_ENTITYRESOLVER_H

#include <random>
#include <vector>
#include "Player.h"
#include "Enemies/EnemyA.h"
#include "Projectile.h"
#include "../../lib/raylib.h"
#include "../../lib/raymath.h"

// Forward declaration of EnemyA

class EntityResolver {
public:
    void RegisterPlayer(Player* player);
    void RegisterEnemy(EnemyA* enemy);
    Player* GetPlayer();
    std::vector<EnemyA*> GetEnemies();
    std::vector<Projectile*> GetProjectiles();
    void DeleteEnemies();
    void CleanEnemies();
    void CleanProjectiles();

    void DeletePlayer();
    void RegisterProjectile(Projectile* projectile);
    void FreeMemory();
    void InitRand(int screenWidth, int screenHeight);
    void Shutdown();
private:
    std::vector<EnemyA*> enemies;
    std::vector<Projectile*> projectiles;
    Player* player;
    int screenWidth;
    int screenHeight;
    std::thread t1;
};

#endif //CPP_LEARNING_ENTITYRESOLVER_H
