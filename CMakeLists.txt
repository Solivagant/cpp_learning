cmake_minimum_required(VERSION 3.28)
project(cpp_learning)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/rxcpp)

add_executable(cpp_learning src/main.cpp
        lib/raylib.h
        lib/raymath.h
        src/Game/GameLoop.cpp
        src/Game/GameLoop.h
        src/Util/MathUtil.cpp
        src/Util/MathUtil.h
        src/Entities/Player.cpp
        src/Entities/Player.h
        src/Entities/AEntity.h
        src/Entities/Enemies/EnemyA.cpp
        src/Entities/Enemies/EnemyA.h
        src/Entities/EntityResolver.cpp
        src/Entities/EntityResolver.h
        src/Entities/Projectile.cpp
        src/Entities/Projectile.h
        src/Game/BackgroundService.cpp
        src/Game/BackgroundService.h
        src/Abilities/HealthRegen.cpp
        src/Abilities/HealthRegen.h
        src/Stats/PlayerData.cpp
        src/Stats/PlayerData.h
        src/Game/GameData.cpp
        src/Game/GameData.h
        src/Entities/Enemies/EnemyB.cpp
        src/Entities/Enemies/EnemyB.h
        src/Combat/WaveSystem.cpp
        src/Combat/WaveSystem.h
        src/Combat/CombatHandler.cpp
        src/Combat/CombatHandler.h
        src/ServiceLocator.cpp
        src/ServiceLocator.h
)

target_link_libraries(cpp_learning rxcpp)

# Only Tested on Mac, correct way would conditionally link to the Windows equivalents, if on Windows
target_link_libraries(cpp_learning "-framework CoreVideo")
target_link_libraries(cpp_learning "-framework IOKit")
target_link_libraries(cpp_learning "-framework Cocoa")
target_link_libraries(cpp_learning "-framework GLUT")
target_link_libraries(cpp_learning "-framework OpenGL")
target_link_libraries(cpp_learning ${CMAKE_CURRENT_SOURCE_DIR}/lib/libraylib.a)

add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(cpp_learning copy_assets)