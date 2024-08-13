//
// Created by Geraldo Nascimento on 09/08/2024.
//

#include "CombatHandler.h"
#include <iostream>
#include <sstream>

CombatHandler::CombatHandler(std::shared_ptr<std::mutex>& mutex, GameData* gameData, PlayerData* playerData, EntityResolver *entityResolver) {
    this->gameData = gameData;
    this->playerData = playerData;
    this->entityResolver = entityResolver;
    this->mutex = mutex;
}

bool CombatHandler::ProcessCombat(float deltaTime) {
    std::lock_guard<std::mutex> lock(*mutex);

    Player *player = entityResolver->GetPlayer();
    bool hasFired = player->Fire(deltaTime);

    if (hasFired) {
        currentTime += deltaTime;
        if(currentTime > 1)
        {
            currentTime = 0;
        }
        currentAngle = 360 * currentTime;

        //Projectile Down
        auto vector2 = Vector2{0, 10};

        if(playerData->GetLevel() > 4)
        {
            vector2 = Vector2Rotate(vector2, currentAngle + 180);
        }

        auto *projectile = new Projectile(player->GetPosition(), Vector2Add(player->GetPosition(), vector2));

        entityResolver->RegisterProjectile(projectile);

        //Projectile Up
        if(playerData->GetLevel() > 1)
        {
            auto vector2= Vector2{0, -10};
            if(playerData->GetLevel() > 4)
            {
                vector2 = Vector2Rotate(vector2, currentAngle);
            }

            auto *projectile = new Projectile(player->GetPosition(), Vector2Add(player->GetPosition(), vector2));
            entityResolver->RegisterProjectile(projectile);
        }

        //Projectile Right
        if(playerData->GetLevel() > 2)
        {
            auto vector2 = Vector2{10, 0};
            if(playerData->GetLevel() > 4)
            {
                vector2 = Vector2Rotate(vector2, currentAngle + 90);
            }
            auto *projectile = new Projectile(player->GetPosition(), Vector2Add(player->GetPosition(), vector2));

            entityResolver->RegisterProjectile(projectile);
        }

        if(playerData->GetLevel() > 3)
        {
            auto vector2 = Vector2{-10, 0};
            if(playerData->GetLevel() > 4)
            {
                vector2 = Vector2Rotate(vector2, currentAngle + 270);
            }
            auto *projectile = new Projectile(player->GetPosition(), Vector2Add(player->GetPosition(), vector2));
            entityResolver->RegisterProjectile(projectile);
        }
    }

    bool enemyWasHit = false;
    bool projectileExpired = false;

    for (Projectile *projectile: entityResolver->GetProjectiles()) {
        projectile->Move(playerData->GetLevel(), deltaTime);
        projectile->Draw();

        //TODO needs to be thread safe
        for (EnemyA *enemy: entityResolver->GetEnemies()) {
            if(enemy->GetIsDying()) continue;

            Vector2 enemyPosition = enemy->GetPosition();

            //Delete hit enemies
            //They're hit if the distance between them is smaller than or equal to their added radii
            if (Vector2Distance(enemyPosition, projectile->GetPosition()) <= EnemyA::Radius + Projectile::Radius) {
                if(projectile_enemy_map.contains(enemy))
                {
                    if(!projectile_enemy_map[enemy].contains(projectile))
                    {
                        enemy->DealDamage(1);
                        if(enemy->GetIsDying())
                        {
                            playerData->SetXP(playerData->GetXP()+1);
                        }
                        enemyWasHit = true;
                        projectile_enemy_map[enemy][projectile] = ' ';
                    }
                }
                else
                {
                    enemy->DealDamage(1);
                    if(enemy->GetIsDying())
                    {
                        playerData->SetXP(playerData->GetXP()+1);
                    }
                    projectile_enemy_map[enemy] = std::map<Projectile*, char>();
                    projectile_enemy_map[enemy][projectile] = ' ';
                }
            }

            if (enemy->GetToDelete()) {
                enemyWasHit = true;
            }
        };

        if (projectile->GetToDelete()) {
            projectileExpired = true;
        }
    }

    for (EnemyA *enemy: entityResolver->GetEnemies()) {
        Vector2 enemyPosition = enemy->GetPosition();

        if (!enemy->GetIsDying() && Vector2Distance(enemyPosition, entityResolver->GetPlayer()->GetPosition()) <= EnemyA::Radius + Player::Radius) {
            //Player hit
            player->DealDamage(1);

            //Kill enemy as well
            enemy->KillFromHittingPlayer();
            enemyWasHit = true;
            if(playerData->IsDead())
            {
                return true;
            }
        }
    }

    if (enemyWasHit) {
        entityResolver->CleanEnemies();
    }

    if (projectileExpired) {
        entityResolver->CleanProjectiles();
    }

    return false;
}





