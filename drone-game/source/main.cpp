// drone-game.cpp : Defines the entry point for the application.
//
#pragma comment (lib, "raylib.lib")
#include "../headers/PhysicsManager.h"
#include "../headers/RenderManager.h"
#include <raylib.h>
#include <iostream>

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
    Camera3D cam = Camera3D{ 0 };
    cam.position = { 5, 2, 4 };
    cam.target = { 0,0,0 };
    cam.up = { 0,1,0 };
    cam.fovy = 45;
    cam.projection = CAMERA_PERSPECTIVE;
    RenderManager rend = RenderManager(cam);
    phys.simulate();
    // Main game loop
    Vector3 test_pos = { 1,1,1 };
    GameObject test_object = GameObject(test_pos, "../../../resources/1.png");
    phys.addObject(test_object);
    rend.addObject(test_object);
    while (!WindowShouldClose()&&enableDrawing)    // Detect window close button or ESC key
    {
        BeginDrawing();
        BeginMode3D(cam);
        DrawGrid(10, 1);
        rend.render();
        ClearBackground(RAYWHITE);
        EndMode3D();
        DrawText("PLACEHOLDER UI", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    // De-Initialization
    phys.endSimulation();
    printf("simulation ended");
    CloseWindow();        // Close window and OpenGL context
    

    return 0;
}
