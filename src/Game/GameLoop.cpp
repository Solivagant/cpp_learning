//
// Created by Geraldo Nascimento on 05/08/2024.
// Using raylib
// https://www.raylib.com/cheatsheet/cheatsheet.html
#include <iostream>
#include <cstdlib>

#include "GameLoop.h"

//Declare functions to run in thread
void SpawnRespawn(PlayerData* playerData, Player* player, EntityResolver* entityResolver);

int GameLoop::RunGame(ServiceLocator* serviceLocator) {
    entityResolver = serviceLocator->GetEntityResolver();
    gameData = serviceLocator->GetGameData();
    background = serviceLocator->GetBackgroundService();
    combatHandler = serviceLocator->GetCombatHandler();
    waveSystem = serviceLocator->GetWaveSystem();
    playerData = serviceLocator->GetPlayerData();

    int width = gameData->GetScreenWidth();
    int height = gameData->GetScreenHeight();

    gameData->SetIsRunning(true);

    InitWindow(width, height, "DOT SURVIVOR");
    SetTargetFPS(60);

    entityResolver->InitRand(width, height);
    background->Init(width, height);

    Player *player = RegisterPlayer();
    waveSystem->StartWave();

    std::thread t1 = std::thread(SpawnRespawn, playerData, player, entityResolver);
    bool playerDied = false;

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        float deltaTime = GetFrameTime();
        player->Move(deltaTime);
        MoveEnemies(deltaTime);

        BeginDrawing();
        ClearBackground(BLACK);

        background->Draw();
        player->Draw();

        DrawEnemies(deltaTime);
        playerDied = combatHandler->ProcessCombat(deltaTime);
        if(playerDied)
        {
            entityResolver->DeleteEnemies();
        }
        
        EndDrawing();
    }

    playerData->SetHealth(0);
    gameData->SetIsRunning(false);

    if(t1.joinable())
    {
        t1.join();
    }
    waveSystem->Shutdown();

    FreeMemory();
    CloseWindow(); // Close window and OpenGL context

    return 0;
}

Player* GameLoop::RegisterPlayer() {
    Player *player = new Player(playerData, gameData, {(float) gameData->GetScreenWidth() / 2, (float) gameData->GetScreenHeight() / 2});
    entityResolver->RegisterPlayer(player);
    return player;
}

void GameLoop::MoveEnemies(float deltaTime) {
    Player *player = entityResolver->GetPlayer();
    if(playerData->IsDead()) return;

    auto enemies = entityResolver->GetEnemies();
    for (BasicEnemy *enemy: enemies) {
        enemy->Move(deltaTime, player, enemies);
    }
}

void GameLoop::DrawEnemies(float deltaTime) {
    for (BasicEnemy *enemy: entityResolver->GetEnemies()) {
        enemy->Draw(deltaTime);
    }
}

void SpawnRespawn(PlayerData* playerData, Player* player, EntityResolver* entityResolver) {
    while (!WindowShouldClose()) {
        std::this_thread::sleep_for(std::chrono::milliseconds (500));
        if(playerData->IsDead())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds (500));
            player->Respawn();
        }
    }
}

void GameLoop::FreeMemory() {
    background->Unload();
    delete background;
    entityResolver->FreeMemory();
    free(entityResolver);
}
