//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_ENTITYRESOLVER_H
#define CPP_LEARNING_ENTITYRESOLVER_H

#include <vector>
#include "Player.h"
#include "BasicEnemy.h"
#include "Projectile.h"
#include "../../lib/raylib.h"
#include "../../lib/raymath.h"
#include "../Util/EntityPool.h"
#include <iostream>

class EntityResolver {
public:
    void RegisterPlayer(Player* player);
    Player* GetPlayer();
    std::vector<std::shared_ptr<BasicEnemy>> GetEnemies();
    std::vector<std::shared_ptr<Projectile>> GetProjectiles();
    void DeleteEnemies();
    void CleanEnemies();
    void CleanProjectiles();

    void RegisterProjectile(std::shared_ptr<Projectile> projectile);
    void FreeMemory();

    std::shared_ptr<BasicEnemy> AcquireEnemy();
    std::shared_ptr<Projectile> AcquireProjectile();

private:
    EntityPool<BasicEnemy> enemyPool = EntityPool<BasicEnemy>(100);
    EntityPool<Projectile> projectilePool = EntityPool<Projectile>(100);

    std::vector<std::shared_ptr<BasicEnemy>> enemies;
    std::vector<std::shared_ptr<Projectile>> projectiles;
    Player* player;
    std::thread t1;
};

#endif //CPP_LEARNING_ENTITYRESOLVER_H
