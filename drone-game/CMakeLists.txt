# CMakeList.txt : CMake project for drone-game, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("drone-game")
include(FetchContent)
include_directories(${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/include)
set(RAYLIB_VERSION 5.0)
set(RAYLIB_URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz)
FetchContent_Declare(
    raylib
    FIND_PACKAGE_ARGS ${RAYLIB_VERSION} EXACT
    URL ${RAYLIB_URL}
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

# Add source to this project's executable.
add_executable (drone-game "source/main.cpp"  "headers/GameObject.h" "source/GameObject.cpp" "headers/DataTypes.h" "headers/PhysicsManager.h" "headers/Input.h" "source/PhysicsManager.cpp" "headers/RenderManager.h" "source/RenderManager.cpp"   "headers/CharacterController.h" "source/CharacterController.cpp" "headers/Enemy.h" "source/Enemy.cpp" "headers/SpriteSet.h"  "headers/Damagable.h" "source/Damagable.cpp" "headers/Player.h" "source/Player.cpp" "source/UIController.cpp" "headers/UIController.h")

# TODO: Add tests and install targets if needed.
#target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries("drone-game" PRIVATE raylib)
