cmake_minimum_required(VERSION 3.28)
project(cpp_learning)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_learning src/main.cpp
        src/StdSample.cpp
        src/StdSample.h
        src/VHS/VideoClub.cpp
        src/VHS/VideoClub.h
        src/VHS/Rental.cpp
        src/VHS/User.cpp
        src/VHS/User.h
        src/VHS/Video.cpp
        src/VHS/Video.h
        src/VHS/Registration.cpp
        src/VHS/Registration.h
        lib/raylib.h
        lib/raymath.h
        src/SampleMain.cpp
        src/Game/GameLoop.cpp
        src/Game/GameLoop.h
        src/Game/MathUtil.cpp
        src/Game/MathUtil.h
        src/Entities/Player.cpp
        src/Entities/Player.h
        src/Entities/IEntity.h
        src/Entities/BasicEnemy.cpp
        src/Entities/BasicEnemy.h
        src/Entities/EntityResolver.cpp
        src/Entities/EntityResolver.h
)

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