#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "include/raylib.h"

#include <raylib.h>

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

Node *head = NULL;

void insertNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = head;

    if (head != NULL) {
        head->prev = newNode;
    }

    head = newNode;
}

void deleteNode() {
    if (head != NULL) {
        Node *temp = head;
        head = head->next;

        if (head != NULL) {
            head->prev = NULL;
        }

        free(temp);
    }
}

void drawList() {
    Node *current = head;
    int xPos = 10;
    int rectWidth = 20;
    int rectHeight = 20;
    int arrowSpacing = 20; // Ajustez cette valeur pour séparer davantage les flèches

    while (current != NULL) {
        // Dessiner le rectangle avec la valeur
        DrawRectangle(xPos, 50, rectWidth, rectHeight, LIGHTGRAY);
        DrawText(TextFormat("%d", current->data), xPos + 5, 55, 10, BLACK);

        // Dessiner la flèche suivante (si elle existe)
        if (current->next != NULL) {
            DrawLine(xPos + rectWidth, 60 - arrowSpacing, xPos + rectWidth + 20, 60 - arrowSpacing, BLACK);  // ligne horizontale
            DrawLine(xPos + rectWidth + 20, 60 - arrowSpacing, xPos + rectWidth + 15, 55 - arrowSpacing, BLACK);  // flèche vers le haut
            DrawLine(xPos + rectWidth + 20, 60 - arrowSpacing, xPos + rectWidth + 15, 65 - arrowSpacing, BLACK);  // flèche vers le bas
        }

        // Dessiner la flèche précédente (si elle existe)
        if (current->prev != NULL) {
            DrawLine(xPos, 60 + arrowSpacing, xPos - 20, 60 + arrowSpacing, BLACK);  // ligne horizontale
            DrawLine(xPos - 20, 60 + arrowSpacing, xPos - 15, 55 + arrowSpacing, BLACK);  // flèche vers le haut
            DrawLine(xPos - 20, 60 + arrowSpacing, xPos - 15, 65 + arrowSpacing, BLACK);  // flèche vers le bas
        }

        current = current->next;
        xPos += 50;
    }
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib Double Linked List");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsKeyPressed(KEY_SPACE)) {
            int data = GetRandomValue(1, 100);
            insertNode(data);
        }

        if (IsKeyPressed(KEY_D)) {
            deleteNode();
        }

        drawList();

        EndDrawing();
    }

    CloseWindow();

    return 0;