//
// Created by Geraldo Nascimento on 09/08/2024.
//

#ifndef CPP_LEARNING_COMBATHANDLER_H
#define CPP_LEARNING_COMBATHANDLER_H

#include "../Entities/EntityResolver.h"
#include "../Game/GameData.h"

class CombatHandler {
public:
    CombatHandler(GameData* gameData, EntityResolver* entityResolver);
    bool ProcessCombat(float deltaTime);
    void DealDamage(AEntity* x, int amount);
private:
    EntityResolver* entityResolver;
    GameData* gameData;
};

#endif //CPP_LEARNING_COMBATHANDLER_H
