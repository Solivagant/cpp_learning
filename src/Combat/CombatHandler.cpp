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
        auto *projectile = new Projectile(player->GetPosition(), player->GetFirePosition());
        entityResolver->RegisterProjectile(projectile);
    }

    bool enemyWasHit = false;
    bool projectileExpired = false;

    for (Projectile *projectile: entityResolver->GetProjectiles()) {
        projectile->Move(deltaTime);
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





