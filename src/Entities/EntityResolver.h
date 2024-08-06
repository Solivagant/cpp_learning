//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_ENTITYRESOLVER_H
#define CPP_LEARNING_ENTITYRESOLVER_H

#include <vector>
#include "Player.h"
#include "BasicEnemy.h"

// Forward declaration of BasicEnemy

class EntityResolver {
public:
    void RegisterPlayer(Player* player);
    void RegisterEnemy(BasicEnemy* enemy);
    Player* GetPlayer();
    std::vector<BasicEnemy*> GetEnemies();
    void DeleteEnemies();

    void DeletePlayer();
private:
    std::vector<BasicEnemy*> enemies;
    Player* player;
};

#endif //CPP_LEARNING_ENTITYRESOLVER_H
