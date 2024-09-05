// drone-game.cpp : Defines the entry point for the application.
//
#pragma comment (lib, "raylib.lib")
#include "../headers/main.h"
#include "../headers/PhysicsManager.h"
#include <raylib.h>


using namespace std;

int main()
{
    bool enableDrawing = true; //temporary switch to allow turning off raylib for debugging underlying physics

    const int screenWidth = 800;
    const int screenHeight = 450;

    if (enableDrawing) { InitWindow(screenWidth, screenHeight, "GAME"); }
    if (enableDrawing) { SetTargetFPS(60);}


    //test creating game object

    //simulate physics in seperate thread
    PhysicsManager phys;
    phys.simulate();
    // Main game loop
    phys.addObject(new GameObject({ 0,0 }));

    while (!WindowShouldClose()&&enableDrawing)    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    // De-Initialization
    phys.endSimulation();
    printf("simulation ended");
    CloseWindow();        // Close window and OpenGL context
    

    return 0;
}
