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
    CombatHandler(std::shared_ptr<std::mutex>& vectorMutex, GameData* gameData, PlayerData* playerData, EntityResolver* entityResolver);
    bool ProcessCombat(float deltaTime);
    void DealDamage(AEntity* x, int amount);
private:
    EntityResolver* entityResolver;
    GameData* gameData;
    PlayerData* playerData;
    std::shared_ptr<std::mutex> vectorMutex;

    float currentAngle = 0;
    float currentTime = 0;

    std::map<AEntity*, std::map<Projectile*, char>> projectile_enemy_map;
};

#endif //CPP_LEARNING_COMBATHANDLER_H
