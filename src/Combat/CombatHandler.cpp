//
// Created by Geraldo Nascimento on 09/08/2024.
//

#include "CombatHandler.h"

CombatHandler::CombatHandler(std::shared_ptr<std::mutex> &mutex, PlayerData* playerData,
                             EntityResolver* entityResolver) {
    this->playerData = playerData;
    this->entityResolver = entityResolver;
    this->mutex = mutex;
}

bool CombatHandler::ProcessCombat(float deltaTime) {
    std::lock_guard<std::mutex> lock(*mutex);

    Player* player = entityResolver->GetPlayer();

    ProcessAbilities(deltaTime, player);

    bool enemyWasHit = false;
    bool projectileExpired = false;

    for (auto projectile: entityResolver->GetProjectiles()) {
        projectile->Move(deltaTime);
        projectile->Draw();

        for (auto enemy: entityResolver->GetEnemies()) {
            if (enemy->GetIsDying()) continue;

            Vector2 enemyPosition = enemy->GetPosition();

            //Delete hit enemies
            //They're hit if the distance between them is smaller than or equal to their added radii
            //The projectile_enemy_map helps keep track if a projectile has hit a player, so it doesn't deal double damage
            if (Vector2Distance(enemyPosition, projectile->GetPosition()) <= enemy->GetRadius() + Projectile::Radius) {
                enemyWasHit = true;

                if (projectile_enemy_map.contains(enemy)) {
                    if (!projectile_enemy_map[enemy].contains(projectile)) {
                        DealDamageToEnemy(enemy, projectile);
                    }
                } else {
                    projectile_enemy_map[enemy] = std::map<std::shared_ptr<Projectile>, char>();
                    DealDamageToEnemy(enemy, projectile);
                }
            }

            //We have to erase the entry in the map for the enemy when its dead, otherwise it will hold on to the smart pointer
            //and never clean it when it dies, leading to the enemy object pool to keep increasing infinitely.
            if (enemy->GetIsDying() || enemy->GetToDelete()) {
                enemyWasHit = true;
                projectile_enemy_map.erase(enemy);
            }

            if (!enemy->GetIsDying() && Vector2Distance(enemyPosition, entityResolver->GetPlayer()->GetPosition()) <=
                                        enemy->GetRadius() + Player::Radius) {
                //Player hit
                player->DealDamage(1);

                //Kill enemy as well
                enemy->KillFromHittingPlayer();
                enemyWasHit = true;
                if (playerData->IsDead()) {
                    return true;
                }
            }
        };

        if (projectile->GetToDelete()) {
            projectileExpired = true;
            //We could loop through all enemies to find projectiles, but we're counting on those already hit
            //enemies to die soon, so we can ignore it
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

void CombatHandler::DealDamageToEnemy(std::shared_ptr<BasicEnemy> enemy, std::shared_ptr<Projectile> projectile) {
    enemy->DealDamage(1);
    if (enemy->GetIsDying()) {
        playerData->SetXP(playerData->GetXP() + 1);
    }
    projectile_enemy_map[enemy][projectile] = ' ';
}

void CombatHandler::ProcessAbilities(float deltaTime, Player* player) {
    bool hasFired = player->Fire(deltaTime);

    if (hasFired) {
        Vector2 playerPos = player->GetPosition();

        currentTime += deltaTime;
        if (currentTime > 1) currentTime = 0;

        currentAngle = 360 * currentTime;

        //Projectile Down
        GenerateProjectile(Vector2{0, -10}, playerPos, 0);

        //Projectile Up
        if (playerData->GetLevel() >= 5) {
            GenerateProjectile(Vector2{0, 10}, playerPos, 180);
        }

        //Projectile Right
        if (playerData->GetLevel() >= 10) {
            GenerateProjectile(Vector2{10, 0}, playerPos, 90);
        }

        //Projectile Left
        if (playerData->GetLevel() >= 15) {
            GenerateProjectile(Vector2{-10, 0}, playerPos, 270);
        }
    }
}

void CombatHandler::GenerateProjectile(Vector2 targetPos, Vector2 playerPos, int angle) {
    if (playerData->GetLevel() >= 20) {
        targetPos = Vector2Rotate(targetPos, currentAngle + angle);
    }
    auto projectile = entityResolver->AcquireProjectile();
    projectile->Init(playerPos, Vector2Add(playerPos, targetPos));
}





