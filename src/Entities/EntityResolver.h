//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_ENTITYRESOLVER_H
#define CPP_LEARNING_ENTITYRESOLVER_H

#include <vector>
#include "Player.h"

// Forward declaration of BasicEnemy
class BasicEnemy;

class EntityResolver {
public:
    void RegisterPlayer(Player* player);
    void RegisterEnemy(BasicEnemy* enemy);
    Player* GetPlayer();
    std::vector<BasicEnemy*> GetEnemies();

private:
    std::vector<BasicEnemy*> enemies;
    Player* player;
};

#endif //CPP_LEARNING_ENTITYRESOLVER_H
