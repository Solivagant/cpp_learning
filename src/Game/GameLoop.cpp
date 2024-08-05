//
// Created by Geraldo Nascimento on 05/08/2024.
//
#include "GameLoop.h"
#include "MathUtil.h"
#include "../Entities/Player.h"
#include "../Entities/BasicEnemy.h"
#include "../Entities/EntityResolver.h"

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

    // Define the player character
    Player player({(float) screenWidth / 2, (float) screenHeight / 2});

    entityResolver.RegisterPlayer(&player);

    BasicEnemy basicEnemy1(&entityResolver, Vector2 {(float) screenWidth / 2, 0});
    BasicEnemy basicEnemy2(&entityResolver, Vector2 {(float) screenWidth / 2, (float)screenHeight});

    entityResolver.RegisterEnemy(&basicEnemy1);
    entityResolver.RegisterEnemy(&basicEnemy2);

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        float deltaTime = GetFrameTime();
        entityResolver.GetPlayer()->Move(deltaTime);
        MoveEnemies(deltaTime);

        // Draw
        BeginDrawing();
        ClearBackground(WHITE);

        // Draw the background
        DrawTexture(background, -(int)distance.x, -(int)distance.y, WHITE);
        entityResolver.GetPlayer()->Draw();

        DrawEnemies();
        EndDrawing();
    }

    //TODO add vector of starting points for enemies then randomise index access to pick
    // spawn points for new enemies that advance directly to player

    // De-Initialization
    UnloadTexture(background); // Unload background texture

    CloseWindow(); // Close window and OpenGL context

    return 0;
}

void GameLoop::MoveEnemies(float deltaTime) {
    for (BasicEnemy* enemy: entityResolver.GetEnemies()) {
        enemy->Move(deltaTime);
    }
}

void GameLoop::DrawEnemies() {
    for (BasicEnemy* enemy: entityResolver.GetEnemies()) {
        enemy->Draw();
    }
}
