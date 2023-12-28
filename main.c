#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct Node
{
    Rectangle rect;
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

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

void SwapNodes(Node **head, Node *node1, Node *node2)
{
    // Vérifier si les noeuds sont les memes
    if (node1 == node2)
        return;

    // Vérifier si l'un des noeuds est NULL
    if (node1 == NULL || node2 == NULL)
        return;

    // Trouver les noeuds voisins
    Node *prevNode1 = node1->prev;
    Node *nextNode1 = node1->next;
    Node *prevNode2 = node2->prev;
    Node *nextNode2 = node2->next;

    // Mettre à jour les liens pour le noeud 1
    if (prevNode1 != NULL)
    {
        prevNode1->next = node2;
    }
    else
    {
        *head = node2; // Si le nœud 1 est la tête de la liste
    }

    node2->prev = prevNode1;
    node2->next = nextNode1;

    // Mettre à jour les liens pour le nœud 2
    if (prevNode2 != NULL)
    {
        prevNode2->next = node1;
    }
    else
    {
        *head = node1; // Si le nœud 2 est la tête de la liste
    }

    node1->prev = prevNode2;
    node1->next = nextNode2;
}

void TriListDoublement(Node **head)
{
    if (*head == NULL || (*head)->next == NULL)
    {
        return;
    }
    Node *current = *head;
    Node *suiv;
    while (current->next != NULL)
    {
        suiv = current->next;
        while (suiv != NULL)
        {
            if (current->data > suiv->data)
            {
                SwapNodes(head, current, suiv);
            }
            else
            {
                suiv = suiv->next;
            }
        }
    }
}

#define MAX_INPUT_CHARS 9
#define buttonWidth 180
#define buttonHeight 70
#define DebutposX 600
#define DebutposY 800
#define ListWidth 170
#define ListHeight 200

Vector2 buttonPosition = {100, 100};

void DrawButton(Rectangle rect, const char *text, Color co)
{
    DrawRectangleLinesEx(rect, 3, BLANK);
    DrawRectangleRec(rect, co);                                                                                    // Draw button outline
    DrawText(text, rect.x + (rect.width - MeasureText(text, 20)) / 2, rect.y + (rect.height - 20) / 2, 21, WHITE); // Draw button text
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
    int arrowSpacing = 50; // Ajustez cette valeur pour séparer davantage les flèches

    while (current != NULL)
    {
        // Dessiner le rectangle avec la valeur
        Rectangle rec ={xPos, DebutposY, rectWidth, rectHeight};
        DrawButton(rec,TextFormat("%d", current->data),LIME);

        // Dessiner la flèche suivante (si elle existe)
        if (current->next != NULL)
        {
            DrawFlechRight(xPos + rectWidth,60 - arrowSpacing,xPos + rectWidth + 80, 60 - arrowSpacing);
        }

        // Dessiner la flèche précédente (si elle existe)
        if (current->prev != NULL)
        {
            DrawFlechLeft(xPos - 80, 70 + arrowSpacing, xPos ,70 + arrowSpacing);
        }

        current = current->next;
        xPos += 250;
    }
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

    Rectangle scroller = {50, 200, 200, 100};
    int scrollSpeed = 5;

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

        if (IsKeyDown(KEY_RIGHT))
        {
            scroller.x += scrollSpeed;
        }

        if (IsKeyDown(KEY_LEFT))
        {
            scroller.x -= scrollSpeed;
        }

        // Draw
        BeginDrawing();

        ClearBackground(BLACK);
        DrawRectangle(1500 - 2200 / 2, 1000 - 1500 / 2, 2200, 1500, RAYWHITE);
        DrawRectangleRec(scroller, BLUE);

        /*
        for (int i = 0; i < GetScreenWidth(); i += 20)
        {
            DrawLine(i, 0, i, GetScreenHeight(), LIGHTGRAY);
        }

        for (int i = 0; i < GetScreenHeight(); i += 20)
        {
            DrawLine(0, i, GetScreenWidth(), i, LIGHTGRAY);
        }

        // Get mouse coordinates
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();

        // Draw mouse coordinates
        DrawText(TextFormat("Mouse X: %03d", mouseX), GetScreenWidth() - 300, 30, 30, YELLOW);
        DrawText(TextFormat("Mouse Y: %03d", mouseY), GetScreenWidth() - 250, 50, 35, YELLOW);
        */
        // Draw text input rectangle
        DrawButton(buttonCreate, "Create", GREEN);
        DrawButton(buttoninsert, "Insert", GOLD);
        DrawButton(buttonRecherche, "Rechercher", ORANGE);
        DrawButton(buttonDelete, "Delete", RED);
        DrawRectangle(600, 800, 170, 200, LIME);

        /*
        // Draw premiere Flech
        DrawFlech(500, 500, 700, 500);
        DrawFlechLeft(500, 550, 700, 550);
        */

        EndDrawing();
    }
    // close fenètre
    CloseWindow();

    return 0;
}
