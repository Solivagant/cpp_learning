//
// Created by Geraldo Nascimento on 09/08/2024.
//

#ifndef CPP_LEARNING_COMBATHANDLER_H
#define CPP_LEARNING_COMBATHANDLER_H

#include "../Entities/EntityResolver.h"
#include "../Game/GameData.h"
#include <map>
#include <thread>
#include <mutex>

class CombatHandler {
public:
    CombatHandler(std::shared_ptr<std::mutex>& mutex, PlayerData* playerData, EntityResolver* entityResolver);
    bool ProcessCombat(float deltaTime);
private:
    EntityResolver* entityResolver;
    PlayerData* playerData;
    std::shared_ptr<std::mutex> mutex;

    float currentAngle = 0;
    float currentTime = 0;

    std::map<std::shared_ptr<BasicEnemy>, std::map<Projectile*, char>> projectile_enemy_map;
    void ProcessAbilities(float deltaTime, Player* player);
    void GenerateProjectile(Vector2 targetPos, Vector2 playerPos, int angle);
};

#endif //CPP_LEARNING_COMBATHANDLER_H
