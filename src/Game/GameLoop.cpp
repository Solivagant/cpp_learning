//
// Created by Geraldo Nascimento on 05/08/2024.
// Using raylib
// https://www.raylib.com/cheatsheet/cheatsheet.html
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "GameLoop.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NullDereference"


int GameLoop::RunGame(int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    InitWindow(this->screenWidth, this->screenHeight, "KILLABETH");

    background = new Background();
    background->Init(screenWidth,screenHeight);
    SetTargetFPS(60);  // Set our game to run at 60 frames-per-second

    entityResolver = (EntityResolver *) malloc(sizeof(EntityResolver));
    entityResolver->InitRand(screenWidth, screenHeight);
    RegisterPlayer();

    bool hasCreated = false;
    float time = 0;
    float timeToRestart = 5;
    float timeToCreate = 2.5;

    std::thread t1(SpawnGenerateEnemies, entityResolver);
    std::thread t2(SpawnRespawn, entityResolver->GetPlayer());

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        float deltaTime = GetFrameTime();
        entityResolver->GetPlayer()->Move(deltaTime);
        MoveEnemies(deltaTime);

        BeginDrawing();
        ClearBackground(BLACK);

        background->Draw();
        entityResolver->GetPlayer()->Draw();

        DrawEnemies(deltaTime);
        ProcessCombat(deltaTime);

        EndDrawing();

        time += deltaTime;

        std::stringstream timeString;
        timeString << "time" << time;

        // TODO make a wave system out of this
        if (!hasCreated && time >= timeToCreate) {
//            std::thread t3(SpawnGenerateEnemies, entityResolver);
            hasCreated = true;
        }

        if (hasCreated && time >= timeToRestart) {
            time = 0;
            hasCreated = false;
        }
    }

    t1.join();
    t2.join();

    FreeMemory();
    CloseWindow(); // Close window and OpenGL context

    return 0;
}

//Previously I was getting memory access violation, because Player player(x, y) creates the object on the stack, which gets
//wiped when the method ends.
void GameLoop::RegisterPlayer() {
    Player *player = new Player({(float) screenWidth / 2, (float) screenHeight / 2});
    entityResolver->RegisterPlayer(player);
}

void GameLoop::MoveEnemies(float deltaTime) {
    if(entityResolver->GetPlayer()->IsDead()) return;
    for (BasicEnemy *enemy: entityResolver->GetEnemies()) {
//        std::cout << "enemy moving" << std::endl;
        enemy->Move(deltaTime, entityResolver->GetPlayer(), entityResolver->GetEnemies());
    }
}

void GameLoop::DrawEnemies(float deltaTime) {
    for (BasicEnemy *enemy: entityResolver->GetEnemies()) {
        enemy->Draw(deltaTime);
    }
}

void GameLoop::FreeMemory() {
    background->Unload();
    delete background;
    entityResolver->FreeMemory();
    free(entityResolver);
}

bool GameLoop::ProcessCombat(float deltaTime) {
    Player *player = entityResolver->GetPlayer();
    bool hasFired = player->Fire(deltaTime);

    if (hasFired) {
        auto *projectile = new Projectile(player->GetPosition(), player->GetFirePosition());
        entityResolver->RegisterProjectile(projectile);
    }

    bool enemyWasHit = false;
    bool projectileExpired = false;
    bool playerDied = false;

    for (Projectile *projectile: entityResolver->GetProjectiles()) {
        projectile->Move(deltaTime);
        projectile->Draw();

        for (BasicEnemy *enemy: entityResolver->GetEnemies()) {
            Vector2 enemyPosition = enemy->GetPosition();

            //Delete hit enemies
            //They're hit if the distance between them is smaller than or equal to their added radii
            if (Vector2Distance(enemyPosition, projectile->GetPosition()) <= BasicEnemy::Radius + Projectile::Radius) {
                enemy->MarkDying();
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

        if (Vector2Distance(enemyPosition, entityResolver->GetPlayer()->GetPosition()) <= Player::Radius) {
            //Player died!
            entityResolver->GetPlayer()->Kill();
            playerDied = true;
        }
    }

    if (enemyWasHit) {
        entityResolver->CleanEnemies();
    }

    if (projectileExpired) {
        entityResolver->CleanProjectiles();
    }

    return playerDied;
}

void SpawnGenerateEnemies(EntityResolver* entityResolver) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    entityResolver->GenerateEnemies(10);
}

void SpawnRespawn(Player* player) {
    while(!WindowShouldClose())
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if(player->IsDead())
        {
            player->Respawn();
        }
    }
}


#pragma clang diagnostic pop