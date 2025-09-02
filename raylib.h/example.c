#include "raylib.h"

int main(void) {
    // Init window
    InitWindow(800, 600, "Raylib 3D Cube Example");

    // Define a camera
    Camera camera = { 0 };
    camera.position = (Vector3){ 4.0f, 4.0f, 4.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };   // Where it looks
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };       // "Up" direction
    camera.fovy = 45.0f;                             // Field of view
    camera.projection = CAMERA_PERSPECTIVE;          // 3D perspective

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update camera with WASD + mouse
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Start 3D mode
            BeginMode3D(camera);

                // Draw a cube at origin
                DrawCube((Vector3){ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, RED);
                DrawCubeWires((Vector3){ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, BLACK);

            EndMode3D();

            DrawText("Raylib 3D Cube!", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
