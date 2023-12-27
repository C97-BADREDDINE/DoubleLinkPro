#include "raylib.h"

#define MAX_INPUT_CHARS 9

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "My Full-Screen Interface");

    char name[MAX_INPUT_CHARS + 1] = "\0"; // Buffer to store input text (plus null terminator)
    int letterCount = 0;                   // Current input text length

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        if (IsKeyPressed(KEY_F11))
        { // Toggle fullscreen on F11
            ToggleFullscreen();
        }
        // Check for input to add characters to the text
        if (letterCount < MAX_INPUT_CHARS)
        {
            int key = GetKeyPressed();

            if (key != 0)
            {
                // Only add ASCII characters
                if ((key >= 32) && (key <= 125))
                {
                    name[letterCount] = (char)key;
                    letterCount++;
                }
            }
        }

        // Check for backspace key to remove characters from the text
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            if (letterCount > 0)
            {
                letterCount--;
                name[letterCount] = '\0';
            }
        }

        // Draw

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw text input rectangle
        DrawRectangle(screenWidth / 2 - 150, screenHeight / 2 - 30, 300, 60, LIGHTGRAY);
        DrawRectangleLines(screenWidth / 2 - 150, screenHeight / 2 - 30, 300, 60, GRAY);

        // Draw text
        DrawText(name, screenWidth / 2 - MeasureText(name, 20) / 2, screenHeight / 2 - 10, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
