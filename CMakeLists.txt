cmake_minimum_required(VERSION 3.28)
project(cpp_learning)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_learning src/main.cpp
        lib/raylib.h
        lib/raymath.h
        src/Game/GameLoop.cpp
        src/Game/GameLoop.h
        src/Entities/Player.cpp
        src/Entities/Player.h
        src/Entities/BasicEnemy.cpp
        src/Entities/BasicEnemy.h
        src/Entities/EntityResolver.cpp
        src/Entities/EntityResolver.h
        src/Entities/Projectile.cpp
        src/Entities/Projectile.h
        src/Game/BackgroundService.cpp
        src/Game/BackgroundService.h
        src/Stats/PlayerData.cpp
        src/Stats/PlayerData.h
        src/Game/GameData.cpp
        src/Game/GameData.h
        src/Combat/WaveSystem.cpp
        src/Combat/WaveSystem.h
        src/Combat/CombatHandler.cpp
        src/Combat/CombatHandler.h
        src/Game/ServiceLocator.cpp
        src/Game/ServiceLocator.h
        src/Util/EntityPool.h
)

# Only Tested on Mac, correct way would conditionally link to the Windows equivalents, if on Windows
target_link_libraries(cpp_learning "-framework CoreVideo")
target_link_libraries(cpp_learning "-framework IOKit")
target_link_libraries(cpp_learning "-framework Cocoa")
target_link_libraries(cpp_learning "-framework GLUT")
target_link_libraries(cpp_learning "-framework OpenGL")
target_link_libraries(cpp_learning ${CMAKE_CURRENT_SOURCE_DIR}/lib/libraylib.a)