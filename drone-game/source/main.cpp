// drone-game.cpp : Defines the entry point for the application.
//
#pragma comment (lib, "raylib.lib")
#include "../headers/PhysicsManager.h"
#include "../headers/RenderManager.h"
#include "../headers/CharacterController.h"
#include "../headers/Enemy.h"
#include <raylib.h>
#include <iostream>
using namespace std;

int main()
{
    bool enableDrawing = true; //temporary switch to allow turning off raylib for debugging underlying physics

    //set up screen settings
    const int screenWidth = 800;
    const int screenHeight = 450;

    if (enableDrawing) { InitWindow(screenWidth, screenHeight, "GAME"); }
    if (enableDrawing) { SetTargetFPS(60);}

    //configure camera and rendering
    Camera3D cam = Camera3D{ 0 };
    cam.position = { 1, 2, 1 };
    //cam.target = { 0,0,0 };
    cam.up = { 0,1,0 };
    cam.fovy = 45;
    cam.projection = CAMERA_PERSPECTIVE;
    RenderManager rend = RenderManager(&cam);
    GameObject player = GameObject({0,0,0},"none");//todo: create character class that handles rendering differently
    CharacterController playerController = CharacterController(&player,&cam);
    //simulate physics in seperate thread
    PhysicsManager phys;


    phys.simulate();
    // Main game loop
    Vector3 test_pos = { 1,1,1 };
    Enemy test_object = Enemy(10,test_pos, "../../../resources/1.png",Enemy::TEST);
    phys.addObject(&test_object);
    rend.addObject(test_object);
    test_object.force = { 0.0,0.0,1 };
    while (!WindowShouldClose()&&enableDrawing)    // Detect window close button or ESC key
    {
        //cam.target = test_object.pos;
        
        playerController.applyGameTick(phys.getObjects());
        BeginDrawing();
        BeginMode3D(cam);
        DrawGrid(10, 1);
        rend.render();
        ClearBackground(RAYWHITE);
        EndMode3D();
        playerController.renderUI();
        DrawText("PLACEHOLDER UI", 190, 200, 20, LIGHTGRAY);
        //test_object.active = false;
        EndDrawing();
    }

    // De-Initialization
    phys.endSimulation();
    printf("simulation ended");
    CloseWindow();        // Close window and OpenGL context
    

    return 0;
}
