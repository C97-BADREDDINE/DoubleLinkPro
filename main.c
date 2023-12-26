#include "raylib.h"
#include "stdio.h"

#define Screen_Width 1800
#define Screen_Height 900

int main()
{
    // intialize a window
    InitWindow(Screen_Width, Screen_Height, "first window");

    // Reder loop
    while (!WindowShouldClose())
    {
        // UPDATE
        // Render
        BeginDrawing();
        ClearBackground(WHITE);
        // Draw
        EndDrawing();
    }
    // intialized openGL contexte.
    CloseWindow();
}