//
// Created by Geraldo Nascimento on 05/08/2024.
//
#include "GameLoop.h"
#include "MathUtil.h"
#include "Player.h"

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

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        float deltaTime = GetFrameTime();

        player.DoMovement(deltaTime);

        // Draw
        BeginDrawing();
        ClearBackground(WHITE);

        // Draw the background
        DrawTexture(background, -(int)distance.x, -(int)distance.y, WHITE);

        player.DoDraw();
        EndDrawing();
    }

    //TODO add vector of starting points for enemies then randomise index access to pick
    // spawn points for new enemies that advance directly to player

    // De-Initialization
    UnloadTexture(background); // Unload background texture

    CloseWindow(); // Close window and OpenGL context

    return 0;
}