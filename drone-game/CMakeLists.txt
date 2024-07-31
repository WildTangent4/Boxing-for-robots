# CMakeList.txt : CMake project for drone-game, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("drone-game")

include_directories(${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/include)
find_package(raylib CONFIG REQUIRED)

# Add source to this project's executable.
add_executable (drone-game "source/main.cpp" "headers/main.h" "headers/GameObject.h" "source/GameObject.cpp" "headers/DataTypes.h")

# TODO: Add tests and install targets if needed.
target_link_libraries("drone-game" PRIVATE raylib)
