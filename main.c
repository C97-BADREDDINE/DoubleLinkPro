#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#define MAX_INPUT_CHARS 9
#define buttonWidth  180
#define buttonHeight  70

Vector2 buttonPosition = {100, 100};

void DrawButton(Rectangle rect, const char *text,Color co)
{
    DrawRectangleLinesEx(rect, 3, BLANK);
    DrawRectangleRec(rect, co);                                                                                 // Draw button outline
    DrawText(text, rect.x + (rect.width - MeasureText(text, 20)) / 2, rect.y + (rect.height - 20) / 2, 21, WHITE); // Draw button text
}

bool isClicked(Rectangle rec)
{
    if (CheckCollisionPointRec(GetMousePosition(), rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(void)
{

    InitWindow(GetScreenWidth(), GetScreenHeight(), "Raylib Demo");
    



    Rectangle buttonCreate = {buttonPosition.x, buttonPosition.y, buttonWidth, buttonHeight};
    Rectangle buttoninsert = {buttonPosition.x, buttonPosition.y + buttonHeight + 10, buttonWidth, buttonHeight};
    Rectangle buttonRecherche = {buttonPosition.x, buttonPosition.y + 2 * (buttonHeight + 10), buttonWidth, buttonHeight};
    Rectangle buttonDelete = {buttonPosition.x, buttonPosition.y + 3 * (buttonHeight + 10), buttonWidth, buttonHeight};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        if (IsKeyPressed(KEY_F11))
        { // Toggle fullscreen on F11
            ToggleFullscreen();
        }

        // Draw
        BeginDrawing();

        ClearBackground(BLACK);

        // Draw text input rectangle
        DrawButton(buttonCreate, "Create",GREEN);
        DrawButton(buttoninsert, "Insert",YELLOW);
        DrawButton(buttonRecherche, "Rechercher",ORANGE);
        DrawButton(buttonDelete, "Delete",RED);

        if(isClicked(buttoninsert)){
            DrawRectangle(900,300,buttonWidth,buttonHeight,VIOLET);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
