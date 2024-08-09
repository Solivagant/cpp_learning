//
// Created by Geraldo Nascimento on 09/08/2024.
//

#include "CombatHandler.h"

CombatHandler::CombatHandler(GameData* gameData, PlayerData* playerData, EntityResolver *entityResolver) {
    this->gameData = gameData;
    this->playerData = playerData;
    this->entityResolver = entityResolver;
}

bool CombatHandler::ProcessCombat(float deltaTime) {
    Player *player = entityResolver->GetPlayer();
    bool hasFired = player->Fire(deltaTime);

    if (hasFired) {
        //Projectile Down
        auto *projectile = new Projectile(player->GetPosition(), Vector2Add(player->GetPosition(), Vector2{0, 10}));
        entityResolver->RegisterProjectile(projectile);

        //Projectile Up
        if(playerData->GetLevel() > 1)
        {
            auto *projectile1 = new Projectile(player->GetPosition(), Vector2Add(player->GetPosition(), Vector2{0, -10}));
            entityResolver->RegisterProjectile(projectile1);
        }

        //Projectile Right
        if(playerData->GetLevel() > 2)
        {
            auto *projectile2 = new Projectile(player->GetPosition(), Vector2Add(player->GetPosition(), Vector2{10, 0}));
            entityResolver->RegisterProjectile(projectile2);
        }

        if(playerData->GetLevel() > 3)
        {
            auto *projectile3 = new Projectile(player->GetPosition(), Vector2Add(player->GetPosition(), Vector2{-10, 0}));
            entityResolver->RegisterProjectile(projectile3);
        }
    }

    bool enemyWasHit = false;
    bool projectileExpired = false;

    for (Projectile *projectile: entityResolver->GetProjectiles()) {
        projectile->Move(playerData->GetLevel(), deltaTime);
        projectile->Draw();

        for (BasicEnemy *enemy: entityResolver->GetEnemies()) {
            Vector2 enemyPosition = enemy->GetPosition();

            //Delete hit enemies
            //They're hit if the distance between them is smaller than or equal to their added radii
            if (Vector2Distance(enemyPosition, projectile->GetPosition()) <= BasicEnemy::Radius + Projectile::Radius) {
                DealDamage(enemy, 1);
                playerData->SetXP(playerData->GetXP()+1);

                enemyWasHit = true;
                projectile->MarkForDeletion();
            }

            if (enemy->GetToDelete()) {
                enemyWasHit = true;
            }
        };

        if (projectile->GetToDelete()) {
            projectileExpired = true;
        }
    }

    for (BasicEnemy *enemy: entityResolver->GetEnemies()) {
        Vector2 enemyPosition = enemy->GetPosition();

        if (!enemy->GetIsDying() && Vector2Distance(enemyPosition, entityResolver->GetPlayer()->GetPosition()) <= BasicEnemy::Radius + Player::Radius) {
            //Player hit
            DealDamage(player, 1);

            //Kill enemy as well
            DealDamage(enemy, 1);
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

void CombatHandler::DealDamage(AEntity* x, int amount) {
    x->DealDamage(amount);
}





