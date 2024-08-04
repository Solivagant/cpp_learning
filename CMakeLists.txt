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
)

target_link_libraries(cpp_learning "-framework CoreVideo")
target_link_libraries(cpp_learning "-framework IOKit")
target_link_libraries(cpp_learning "-framework Cocoa")
target_link_libraries(cpp_learning "-framework GLUT")
target_link_libraries(cpp_learning "-framework OpenGL")
target_link_libraries(cpp_learning ${CMAKE_CURRENT_SOURCE_DIR}/lib/libraylib.a)