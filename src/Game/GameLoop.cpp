//
// Created by Geraldo Nascimento on 05/08/2024.
// Using raylib
// https://www.raylib.com/cheatsheet/cheatsheet.html
#include <iostream>
#include <cstdlib>

#include "GameLoop.h"

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

    InitWindow(width, height, ".SURVIVORS");
    SetTargetFPS(60);

    entityResolver->InitRand(width, height);
    background->Init(width, height, playerData);

    player = RegisterPlayer();
    waveSystem->StartWave();

    std::thread t1 = std::thread(&GameLoop::SpawnRespawn, this);

    Camera2D camera = { 0 };
    camera.target = player->GetPosition();
    camera.offset = (Vector2){ width/2.0f, height/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    int playerCurrentLevel = 1;

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        float deltaTime = GetFrameTime();

        if (!playerData->IsDead()) {
            player->Move(deltaTime);
            playerData->UpdatePosition(player->GetPosition());
            MoveEnemies(deltaTime);
        }

        camera.target = player->GetPosition();

        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(BLACK);

        background->Draw(deltaTime);

        DrawEnemies(deltaTime);
        player->Draw();

        if (!playerData->IsDead()) {
            combatHandler->ProcessCombat(deltaTime);
        }

        EndMode2D();
        EndDrawing();

        if(playerData->GetLevel() > playerCurrentLevel)
        {
            playerCurrentLevel = playerData->GetLevel();
            background->StartTransition();
        }
    }

    gameData->SetIsRunning(false);

    if (t1.joinable()) {
        t1.join();
    }
    waveSystem->Shutdown();
    entityResolver->Shutdown();

    FreeMemory();
    CloseWindow();

    return 0;
}

Player* GameLoop::RegisterPlayer() {
    Player* player = new Player(playerData, gameData,
                                {(float) gameData->GetScreenWidth() / 2, (float) gameData->GetScreenHeight() / 2});
    entityResolver->RegisterPlayer(player);
    return player;
}

void GameLoop::MoveEnemies(float deltaTime) {
    Player* player = entityResolver->GetPlayer();
    if (playerData->IsDead()) return;

    auto enemies = entityResolver->GetEnemies();
    for (EnemyA* enemy: enemies) {
        enemy->Move(playerData->GetLevel(), deltaTime, player, enemies);
    }
}

void GameLoop::DrawEnemies(float deltaTime) {
    for (EnemyA* enemy: entityResolver->GetEnemies()) {
        enemy->Draw(deltaTime);
    }
}

void GameLoop::SpawnRespawn() {
    while (!WindowShouldClose()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if (playerData->IsDead()) {
            waveSystem->BlowUpEnemies();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
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
