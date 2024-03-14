#include "raylib.h"
#include "raymath.h"

int main() {
    // Initialization
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60); // Set target frames-per-second

    // Triangle vertex positions
    Vector2 vertex1 = { -50, -50 };
    Vector2 vertex2 = { 0, 50 };
    Vector2 vertex3 = { 50, -50 };
    float rotation = 0.0f;

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key
        // Update
        rotation += 1.0f;

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode2D((Camera2D){0});
        DrawTriangle(
            Vector2Add((Vector2){ screenWidth/2, screenHeight/2 }, Vector2Rotate(vertex1, rotation)),
            Vector2Add((Vector2){ screenWidth/2, screenHeight/2 }, Vector2Rotate(vertex2, rotation)),
            Vector2Add((Vector2){ screenWidth/2, screenHeight/2 }, Vector2Rotate(vertex3, rotation)),
            RED
        );
        EndMode2D();

        DrawText("Spinning triangle", 10, 10, 20, DARKGRAY);

        //DrawText("First window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    // De-initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
