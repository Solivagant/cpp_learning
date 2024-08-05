#include "Game/GameLoop.h"

int main() {
    //This could be:
    // Game gameLoop();
    // return gameLoop.RunGame();
    //
    //But I wanted to manually allocate memory.
    //
    GameLoop* gameLoopPtr;
    gameLoopPtr = (GameLoop*)malloc(sizeof(GameLoop));
    int exitCode = gameLoopPtr->RunGame(1024,760);

    free(gameLoopPtr);
    return exitCode;
}
