//
// Created by Geraldo Nascimento on 05/08/2024.
//
#include "GameLoop.h"
#include "MathUtil.h"

int GameLoop::RunGame(int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    InitWindow(this->screenWidth, this->screenHeight, "KILLABETH");

    // Load background texture
    Texture2D background = LoadTexture("assets/background.png");

    // Define the player character
    Vector2 playerPosition = {(float) screenWidth / 2, (float) screenHeight / 2};
    float playerSpeed = 200.0f;
    SetTargetFPS(60);  // Set our game to run at 60 frames-per-second

    //CalculateCenter background in window
    auto distance = CalculateCenter(Vector2{(float) background.width, (float) background.height},
                                    Vector2{(float) screenWidth, (float) screenHeight});

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        float deltaTime = GetFrameTime();

        // Move player with arrow keys
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) playerPosition.x += playerSpeed * deltaTime;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) playerPosition.x -= playerSpeed * deltaTime;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) playerPosition.y -= playerSpeed * deltaTime;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) playerPosition.y += playerSpeed * deltaTime;

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the background
        DrawTexture(background, -distance.x, -distance.y, WHITE);

        // Draw the player character (a simple circle)
        DrawCircleV(playerPosition, 25, BLUE);
        EndDrawing();
    }

    //TODO add vector of starting points for enemies then randomise index access to pick
    // spawn points for new enemies that advance directly to player

    // De-Initialization
    UnloadTexture(background); // Unload background texture

    CloseWindow(); // Close window and OpenGL context

    return 0;
}