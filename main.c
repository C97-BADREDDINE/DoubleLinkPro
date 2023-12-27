#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct Node
{
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
    while (current != NULL)
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

Vector2 buttonPosition = {100, 100};

void DrawButton(Rectangle rect, const char *text, Color co)
{
    DrawRectangleLinesEx(rect, 3, BLANK);
    DrawRectangleRec(rect, co);                                                                                    // Draw button outline
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
        DrawButton(buttonCreate, "Create", GREEN);
        DrawButton(buttoninsert, "Insert", YELLOW);
        DrawButton(buttonRecherche, "Rechercher", ORANGE);
        DrawButton(buttonDelete, "Delete", RED);

        if (isClicked(buttoninsert))
        {
            DrawRectangle(900, 300, buttonWidth, buttonHeight, VIOLET);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
