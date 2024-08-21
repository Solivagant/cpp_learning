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

class EntityResolver {
public:
    EntityResolver();
    void RegisterPlayer(Player* player);
    void RegisterEnemy(std::shared_ptr<BasicEnemy> enemy);
    Player* GetPlayer();
    std::vector<std::shared_ptr<BasicEnemy> > GetEnemies();
    std::vector<Projectile*> GetProjectiles();
    void DeleteEnemies();
    void CleanEnemies();
    void CleanProjectiles();

    void RegisterProjectile(Projectile* projectile);
    void FreeMemory();

    std::shared_ptr<BasicEnemy> AcquireEnemy();

private:
    EntityPool<BasicEnemy> enemyPool = EntityPool<BasicEnemy>(100);

    std::vector<std::shared_ptr<BasicEnemy>> enemies;
    std::vector<Projectile*> projectiles;
    Player* player;
    std::thread t1;
};

#endif //CPP_LEARNING_ENTITYRESOLVER_H
