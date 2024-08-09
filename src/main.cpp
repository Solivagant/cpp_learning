#include "Game/GameLoop.h"
#include "Game/GameData.h"
#include "Combat/CombatHandler.h"
#include "ServiceLocator.h"

int main() {

    //Create dependencies
    ServiceLocator serviceLocator = ServiceLocator();
    serviceLocator.Init();

    //Explicit memory allocation just because.
    GameLoop* gameLoopPtr;
    gameLoopPtr = (GameLoop*)malloc(sizeof(GameLoop));
    int exitCode = gameLoopPtr->RunGame(&serviceLocator);

    free(gameLoopPtr);
    return exitCode;
}
