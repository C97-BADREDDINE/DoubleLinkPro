#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include <string.h>
#include <ctype.h>

// Structures
typedef struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

// Create a new node with the given data and return it
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertNode(Node **head, int data)
{
    Node *newNode = createNode(data);
    newNode->next = *head;
    if (*head != NULL)
    {
        (*head)->prev = newNode;
    }
    *head = newNode;
}
void deleteNode(Node **head, int data)
{
    Node *current = *head;
    while (current != NULL && current->data != data)
    {
        current = current->next;
    }
    if (current == NULL)
    {
        printf("No such node found\n");
        return;
    }

    if (current->prev != NULL)
    {
        current->prev->next = current->next;
    }
    else
    {
        *head = current->next;
    }

    if (current->next != NULL)
    {
        current->next->prev = current->prev;
    }

    free(current);
}

Node *searchNode(Node *head, int data)
{
    while (head != NULL && head->data != data)
    {
        head = head->next;
    }
    return head;
}
// Function to print the doubly linked list
void display(Node *head)
{
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
}

void swap(struct Node *a, struct Node *b)
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void sortListSelection(Node **head)
{
    Node *i, *j, *min;

    for (i = *head; i != NULL; i = i->next)
    {
        min = i;

        for (j = i->next; j != NULL; j = j->next)
        {
            if (j->data < min->data)
            {
                min = j;
            }
        }

        if (min != i)
        {
            swap(i, min);
        }
    }
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

#define MAX_INPUT_CHARS 9
#define buttonWidth 180
#define buttonHeight 70
#define DebutposX 450
#define DebutposY 800
#define ListWidth 170
#define ListHeight 200

Node *head = NULL;

Vector2 buttonPosition = {100, 100};

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
bool is_mouse_over_button(Rectangle rect)
{
    /*
        This function will check if the mouse is over the button
        button: the button to check
    */

    return CheckCollisionPointRec(GetMousePosition(), rect);
}

void DrawButton(Rectangle rect, const char *text, Color co)
{
    if (is_mouse_over_button(rect))
    {
        co = SKYBLUE;
    }

    DrawRectangleLinesEx(rect, 10, Fade(BLACK, 120));
    DrawRectangleRec(rect, isClicked(rect) ? DARKGRAY : co);                                                       // Draw button outline
    DrawText(text, rect.x + (rect.width - MeasureText(text, 20)) / 2, rect.y + (rect.height - 20) / 2, 23, WHITE); // Draw button text
}

void DrawFlechRight(int firstX, int firstY, int FinX, int finY)
{
    // Calculate arrow shaft vector
    Vector2 start = {firstX, firstY};
    Vector2 end = {FinX, finY};

    // Define arrow shaft thickness and color
    float thickness = 5.0f;
    Color color = RED;

    // Draw arrow shaft
    DrawLineEx(start, end, thickness, color);

    // Calculate arrow head vectors
    Vector2 arrowHeadSide = {end.x - 10, end.y - 10};
    Vector2 arrowHeadLeft = {end.x - 10, end.y + 10};

    // Draw arrow head (right side)
    DrawLineEx(end, arrowHeadSide, 4.0f, color);

    // Draw arrow head (left side)
    DrawLineEx(end, arrowHeadLeft, 4.0f, color);
}

void DrawFlechLeft(int firstX, int firstY, int FinX, int finY)
{
    // Calculate arrow shaft vector
    Vector2 start = {firstX, firstY};
    Vector2 end = {FinX, finY};

    // Define arrow shaft thickness and color
    float thickness = 5.0f;
    Color color = RED;

    // Draw arrow shaft
    DrawLineEx(start, end, thickness, color);

    // Calculate arrow head vectors
    Vector2 arrowHeadSide = {start.x + 10, start.y - 10};
    Vector2 arrowHeadLeft = {start.x + 10, start.y + 10};

    // Draw arrow head (right side)
    DrawLineEx(start, arrowHeadSide, 4.0f, color);

    // Draw arrow head (left side)
    DrawLineEx(start, arrowHeadLeft, 4.0f, color);
}
void drawList()
{
    Node *current = head;
    int xPos = DebutposX;
    int rectWidth = ListWidth;
    int rectHeight = ListHeight;
    int arrowSpacing = DebutposY; // Ajustez cette valeur pour séparer davantage les flèches

    while (current != NULL)
    {
        // Dessiner le rectangle avec la valeur
        Rectangle rec = {xPos, DebutposY, rectWidth, rectHeight};
        DrawButton(rec, TextFormat("%d", current->data), DARKBLUE);

        // Dessiner la flèche suivante (si elle existe)
        if (current->next != NULL)
        {
            DrawFlechRight(xPos + rectWidth, 60 + arrowSpacing, xPos + rectWidth + 80, 60 + arrowSpacing);
        }

        // Dessiner la flèche précédente (si elle existe)
        if (current->prev != NULL)
        {
            DrawFlechLeft(xPos - 80, 130 + arrowSpacing, xPos, 130 + arrowSpacing);
        }

        current = current->next;
        xPos += 250;
    }
}

void ColorBouttonMouse(Rectangle box, Color c)
{
    if (CheckCollisionPointRec(GetMousePosition(), box))
    {
        c = BLUE;

        // Check if mouse button is pressed
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            c = GREEN;
        }

        // Check if mouse button is released
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            c = RED;
        }
    }
    else
    {
        // If mouse is not over the rectangle, reset the color
        c = RED;
    }
}

void RandomNodes()
{
    int n = GetRandomValue(0, 9);
    for (int i = 0; i < n; i++)
    {
        insertNode(&head, GetRandomValue(0, 99));
    }
}

void InsertNodes(int data)
{
    insertNode(&head, data);
}

bool IsNumber(const char *text)
{
    while (*text)
    {
        if (!isdigit(*text))
        {
            return false;
        }
        text++;
    }
    return true;
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

int main(void)
{
    bool actionRecherche = false;

    char name[MAX_INPUT_CHARS + 1] = "\0"; // Buffer to store input text (plus null terminator)
    int letterCount = 0;

    Rectangle scroller = {5, 1800, 500, 30};
    int scrollSpeed = 10;

    Camera2D camera = {0};
    camera.target = (Vector2){0, 0};
    camera.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    InitWindow(GetScreenWidth(), GetScreenHeight(), "Raylib Demo");

    Rectangle buttonCreate = {buttonPosition.x, buttonPosition.y, buttonWidth, buttonHeight};
    Rectangle buttoninsert = {buttonPosition.x, buttonPosition.y + buttonHeight + 10, buttonWidth, buttonHeight};
    Rectangle buttonRecherche = {buttonPosition.x, buttonPosition.y + 2 * (buttonHeight + 10), buttonWidth, buttonHeight};
    Rectangle buttonDelete = {buttonPosition.x, buttonPosition.y + 3 * (buttonHeight + 10), buttonWidth, buttonHeight};
    Rectangle buttonTRI = {buttonPosition.x, buttonPosition.y + 4 * (buttonHeight + 10), buttonWidth, buttonHeight};
    Rectangle inpDelt = {buttonRecherche.x + 200, buttonRecherche.y, 350, 170};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        if (IsKeyPressed(KEY_F11))
        { // Toggle fullscreen on F11
            ToggleFullscreen();
        }

        if (isClicked(buttonCreate))
        {
            RandomNodes();
        }

        if (isClicked(buttoninsert))
        {
            InsertNodes(GetRandomValue(0, 50));
        }

        if (isClicked(buttonDelete))
        {
            // on devloped
        }

        if (isClicked(buttonRecherche))
        {
            actionRecherche = !actionRecherche;
        }

        if (isClicked(buttonTRI))
        {
            sortListSelection(&head);
        }

        if (IsKeyDown(KEY_RIGHT))
        {
            if (camera.target.x >= 0)
            {
                camera.target.x += 10.0f;
                scroller.x += scrollSpeed;
            }
        }
        else if (IsKeyDown(KEY_LEFT))
        {
            if (camera.target.x > 0)
                camera.target.x -= 10.0f;
                if(scroller.x > 0){
            scroller.x -= scrollSpeed;}
        }

        /*if (actionRecherche == true)
        {

            strcpy(text, "0");

            // Check for number key presses (0-9)
            for (int key = KEY_ZERO; key <= KEY_NINE; key++)

                if (IsKeyPressed(key))
                {
                    int len = strlen(text);
                    if (len < MAX_INPUT_CHARS)
                    {
                        // Concatenate pressed key to the input text
                        text[len] = (char)('0' + (key - KEY_ZERO));
                        text[len + 1] = '\0';
                    }
                }

            // Check for backspace key press
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                int len = strlen(text);
                if (len > 0)
                {
                    // Remove the last character from the input text
                    text[len - 1] = '\0';
                }
            }

            // Draw button
            DrawRectangleRec(inpDelt, isClicked(inpDelt) ? DARKGRAY : LIGHTGRAY);
            DrawText("Enter Number", (int)(inpDelt.x + inpDelt.width / 2 - MeasureText("Enter Number", textSize) / 2), (int)(inpDelt.y + inpDelt.height / 2 - textSize / 2), textSize, isClicked(inpDelt) ? RAYWHITE : GRAY);

            // Draw input text
            DrawText(text, 600 / 2 - MeasureText(text, textSize) / 2, 400 / 2 + 30, textSize, BLACK);
        }

        // Check for input to add characters to the text
        if (letterCount < MAX_INPUT_CHARS)
        {
            int key = GetKeyPressed();

            if (key != 0)
            {
                // Only add ASCII characters
                if ((key >= 48) && (key <= 57))
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
        }*/

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);
        // DrawRectangle(1500 - 2200 / 2, 1000 - 1500 / 2, 2200, 1500, RAYWHITE);
        DrawRectangleRec(scroller, DARKGRAY);
        BeginMode2D(camera);

        // Draw text input rectangle
        DrawButton(buttonCreate, "Create",DARKGREEN);
        DrawButton(buttoninsert, "Insert", GOLD);
        DrawButton(buttonRecherche, "Rechercher", ORANGE);
        DrawButton(buttonDelete, "Delete", RED);
        DrawButton(buttonTRI, "Tri", GREEN);

        //draw list
        drawList();

        EndMode2D();
        DrawFPS(10, 10);

        EndDrawing();
    }
    // close fenètre
    CloseWindow();

    return 0;
}
