#include <iostream>
#include "../lib/raylib.h"
#include "../lib/raymath.h"

void RunGame();

int main() {
    RunGame();
    return 0;
}

void RunGame() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Simple Raylib Game");

    // Load background texture
    Texture2D background = LoadTexture("assets/background.png");

    // Define the player character
    Vector2 playerPosition = {(float) screenWidth / 2, (float) screenHeight / 2};
    float playerSpeed = 200.0f;
    SetTargetFPS(60);  // Set our game to run at 60 frames-per-second

    //Center background in window
    Vector2 backgroundCenter = Vector2{(float)background.width / 2, (float)background.height / 2};
    Vector2 screenCenter = Vector2{(float)screenWidth / 2, (float)screenHeight / 2};
    Vector2 distance = Vector2Subtract(backgroundCenter, screenCenter);

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

    // De-Initialization
    UnloadTexture(background); // Unload background texture

    CloseWindow(); // Close window and OpenGL context
}