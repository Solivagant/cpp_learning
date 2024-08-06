//
// Created by Geraldo Nascimento on 05/08/2024.
//
#include <format>
#include <random>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "GameLoop.h"
#include "../Util/MathUtil.h"
#include "../Entities/BasicEnemy.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NullDereference"

int GameLoop::RunGame(int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    InitWindow(this->screenWidth, this->screenHeight, "KILLABETH");

    // Load background texture
    Texture2D background = LoadTexture("assets/background.png");

    SetTargetFPS(60);  // Set our game to run at 60 frames-per-second

    //CalculateCenter background in window
    auto distance = CalculateCenter(Vector2{(float) background.width, (float) background.height},
                                    Vector2{(float) screenWidth, (float) screenHeight});

    RegisterPlayer();

    bool hasCreated = false;
    float time = 0;
    float timeToDestroy = 10;
    float timeToCreate = 5;

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        float deltaTime = GetFrameTime();
        entityResolver->GetPlayer()->Move(deltaTime);
        MoveEnemies(deltaTime);

        // Draw
        BeginDrawing();
        ClearBackground(WHITE);

        // Draw the background
        DrawTexture(background, -(int) distance.x, -(int) distance.y, WHITE);
        entityResolver->GetPlayer()->Draw();

        DrawEnemies();
        EndDrawing();

        time += deltaTime;

        std::stringstream timeString;
        timeString << "time" << time;

//        std::cout << timeString.str() << std::endl;

        // TODO make a wave system out of this
        if (!hasCreated && time >= timeToCreate) {
            GenerateEnemies(20);
            hasCreated = true;
        }

//        if (hasCreated && time >= timeToDestroy) {
//            entityResolver->DeleteEnemies();
//            time = 0;
//            hasCreated = false;
//        }
    }

    //TODO let's unload the memory of the enemies etc
    // De-Initialization
    FreeMemory();
    UnloadTexture(background); // Unload background texture
    CloseWindow(); // Close window and OpenGL context

    return 0;
}

//Previously I was getting memory access violation, because Player player(x, y) creates the object on the stack, which gets
//wiped when the method ends.
void GameLoop::RegisterPlayer() {
    Player *player = new Player({(float) screenWidth / 2, (float) screenHeight / 2});
    entityResolver = (EntityResolver *) malloc(sizeof(EntityResolver));
    entityResolver->RegisterPlayer(player);
}

void GameLoop::MoveEnemies(float deltaTime) {
    for (BasicEnemy *enemy: entityResolver->GetEnemies()) {
//        std::cout << "enemy moving" << std::endl;
        enemy->Move(deltaTime, entityResolver->GetPlayer(), entityResolver->GetEnemies());
    }
}

void GameLoop::DrawEnemies() {
    for (BasicEnemy *enemy: entityResolver->GetEnemies()) {
        enemy->Draw();
    }
}

void GameLoop::GenerateEnemies(int count) {
    std::random_device rd;
    std::mt19937 e{rd()};
    std::uniform_int_distribution<int> distW{0, screenWidth};
    std::uniform_int_distribution<int> distH{0, screenHeight};

    for (int i = 0; i < count; ++i) {
        Vector2 randomPosition{float(distW(e)), float(distH(e))};

        while (Vector2Distance(randomPosition, entityResolver->GetPlayer()->GetPosition()) <= 30) {
            randomPosition = Vector2{float(distW(e)), float(distH(e))};
        }

        auto *basicEnemy = new BasicEnemy(randomPosition);
        entityResolver->RegisterEnemy(basicEnemy);
    }
}

void GameLoop::FreeMemory() {
    entityResolver->DeletePlayer();
    free(entityResolver);
}

#pragma clang diagnostic pop