#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include <string.h>
#include <ctype.h>

// Structure
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
// ajouter un noeud
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
// suprimer un noeud
void deleteNode(Node **head, int data)
{
    Node *current = *head;
    while (current != NULL && current->data != data)
    {
        current = current->next;
    }
    if (current == NULL)
    {
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
// rechercher une valeur dans la liste
bool searchNode(Node *head, int data)
{
    while (head != NULL && head->data != data)
    {
        head = head->next;
    }
    return head != NULL;
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

// fonction de permutation
void swap(struct Node *a, struct Node *b)
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// fonction de tri croissant
void sortListSelectionAscending(Node **head)
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

// fonction de tri decroissant
void sortListSelectionDescending(Node **head)
{
    Node *i, *j, *max;

    for (i = *head; i != NULL; i = i->next)
    {
        max = i;

        for (j = i->next; j != NULL; j = j->next)
        {
            if (j->data > max->data)
            {
                max = j;
            }
        }

        if (max != i)
        {
            swap(i, max);
        }
    }
}

// fonction pour suprimer la premier valeur
void DeletePremiereValeur(struct Node **head)
{
    if (*head == NULL)
    {
        return;
    }

    struct Node *temp = *head;

    *head = (*head)->next;
    if (*head != NULL)
    {
        (*head)->prev = NULL;
    }

    free(temp);
}

// Fonction pour supprimer la dernière valeur d'une liste doublement chaînée
void supprimerDerniereValeur(struct Node **head)
{
    if (*head == NULL)
    {
        return;
    }

    struct Node *current = *head;

    // Parcourir la liste jusqu'au dernier élément
    while (current->next != NULL)
    {
        current = current->next;
    }

    // Si la liste a plus d'un élément
    if (current->prev != NULL)
    {
        current->prev->next = NULL;
    }
    else
    {
        // Si la liste a un seul élément
        *head = NULL;
    }

    free(current);

    printf("La dernière valeur a été supprimée avec succès.\n");
}
// Function to insert a new node at the end of the doubly linked list
void insertAtend(Node **head, int newData)
{
    // Allocate memory for the new node
    Node *newNode = (Node *)malloc(sizeof(Node));

    // Set the data of the new node
    newNode->data = newData;

    // The new node will be the last node, so set its next to NULL
    newNode->next = NULL;

    // If the list is empty, make the new node the head
    if (*head == NULL)
    {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    // Traverse the list to find the last node
    Node *last = *head;
    while (last->next != NULL)
    {
        last = last->next;
    }

    // Update the next of the last node to point to the new node
    last->next = newNode;

    // Set the previous of the new node to the last node
    newNode->prev = last;
}

// fonction pour verifier si l'index est valide
int isValidIndex(Node **head)
{

    Node *current = *head;
    int length = 0;
    while (current != NULL)
    {
        length++;
        current = current->next;
    }

    return length + 1;
}

// Function to add data at a specific index in a doubly linked list
void insertAtIndex(Node **head, int data, int Index)
{
    Node *current = *head;

    // If the list is empty or index is 0, insert at the beginning
    if (*head == NULL || Index == 0)
    {
        insertNode(head, data);
        return;
    }

    // Traverse to the node at index - 1
    for (int i = 0; i < Index - 1 && current != NULL; ++i)
    {
        current = current->next;
    }

    // If index is greater than the number of nodes, insert at the end
    if (current == NULL)
    {
        insertAtend(head, data);
        return;
    }

    // Insert the new node
    Node *newNode = createNode(data);

    newNode->next = current->next;
    newNode->prev = current;
    if (current->next != NULL)
    {
        current->next->prev = newNode;
    }
    current->next = newNode;
}

int countElements(Node **head)
{
    int count = 0;
    Node *current = *head;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

#define MAX_INPUT_CHARS 5
#define buttonWidth 180
#define buttonHeight 70
#define DebutposX 450
#define DebutposY GetScreenHeight() / 2
#define ListWidth 170
#define ListHeight 170

Node *head = NULL;

Vector2 buttonPosition = {100, 100};
int countList = 0;
int AllScreenButton;
int c;

//-------------------------- function check is button clicked ! --------------------------------------
bool isClicked(Rectangle rec)
{
    return CheckCollisionPointRec(GetMousePosition(), rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    // GetMousePosition(): this function is likely getting the current position of the mouse cursor
    // CheckCollisionPointRec(GetMousePosition(), rec) : ceci vérifie si le curseur de la souris se trouve dans les limites du rectangle spécifié (rec)
    // IsMouseButtonPressed(MOUSE_LEFT_BUTTON): this checks if the left mouse button is pressed.
}

//------------------------check mouse is over button ! -----------------------------------------------
bool is_mouse_over_button(Rectangle rect)
{
    /*
        This function will check if the mouse is over the button
        button: the button to check
    */

    return CheckCollisionPointRec(GetMousePosition(), rect);
}

// L'apparence du bouton change selon que la souris se trouve sur le bouton ou si l'utilisateur clique sur le bouton.
void DrawButton(Rectangle rect, const char *text, Color co)
{
    // checks if the mouse cursor is over the button
    if (is_mouse_over_button(rect))
    {
        // changes the color (co) to SKYBLUE and draws a slightly larger, semi-transparent black rectangle around the button
        co = SKYBLUE;
        DrawRectangle(rect.x - 7, rect.y - 7, rect.width + 14, rect.height + 14, (Color){0, 0, 0, 5});
    }

    DrawRectangleRec(rect, isClicked(rect) ? DARKGRAY : co);                                                       // Draw button outline
    DrawText(text, rect.x + (rect.width - MeasureText(text, 20)) / 2, rect.y + (rect.height - 20) / 2, 23, WHITE); // Draw button text
}

// fonction qui designer le rectangle de input pour entrer la valeur à rechercher ou à inseret
void DrawButtonInput(Rectangle rect, const char *text, Color co)
{
    if (is_mouse_over_button(rect))
    {
        SetMouseCursor(2);
        co = SKYBLUE;
    }
    else
    {
        SetMouseCursor(0);
    }

    if (isClicked(rect))
    {
        co = BLANK;
    }

    DrawRectangleLinesEx(rect, 10, BEIGE);
    DrawRectangleRec(rect, isClicked(rect) ? LIGHTGRAY : co); // Draw button outline
    DrawRectangle(rect.x + 10, rect.y + 10, rect.width - 20, rect.height - 20, WHITE);
    DrawText(text, rect.x + (rect.width - MeasureText(text, 20)) / 2, rect.y + (rect.height - 20) / 2, 40, BLACK);    // Draw button text
    DrawText("Entrer Le Numbre :", rect.x - 530 + (rect.width) / 2, rect.y - 20 + (rect.height - 20) / 2, 35, BLACK); // Draw button text
}

// fonction qui designer le rectangle de input pour entrer l'index
void DrawButtonInput2(Rectangle rect, const char *text, Color co)
{
    if (is_mouse_over_button(rect))
    {
        co = SKYBLUE;
    }

    if (isClicked(rect))
    {
        co = BLANK;
    }

    DrawRectangleLinesEx(rect, 10, BEIGE);
    DrawRectangleRec(rect, isClicked(rect) ? LIGHTGRAY : co); // Draw button outline
    DrawRectangle(rect.x + 10, rect.y + 10, rect.width - 20, rect.height - 20, WHITE);
    DrawText(text, rect.x + (rect.width - MeasureText(text, 20)) / 2, rect.y + (rect.height - 20) / 2, 40, BLACK); // Draw button text
    DrawText("Entrer Indice:", rect.x - 530 + (rect.width) / 2, rect.y - 20 + (rect.height - 20) / 2, 35, BLACK);  // Draw button text
}

// fonction qui designer les fleches entre les noeud de la liste (le suivant)
void DrawFlechRight(int firstX, int firstY, int FinX, int finY)
{
    // Calculate arrow shaft vector
    Vector2 start = {firstX, firstY};
    Vector2 end = {FinX, finY};

    // Define arrow shaft thickness and color
    float thickness = 5.0f;
    Color color = BEIGE;

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

// fonction qui designer les fleches entre les noeud de la liste (le precedent)
void DrawFlechLeft(int firstX, int firstY, int FinX, int finY)
{
    // Calculate arrow shaft vector
    Vector2 start = {firstX, firstY};
    Vector2 end = {FinX, finY};

    // Define arrow shaft thickness and color
    float thickness = 5.0f;
    Color color = BEIGE;

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

int debut = 0;
void drawList()
{
    Node *current = head;
    int xPos = debut;
    int rectWidth = ListWidth;
    int rectHeight = ListHeight;
    int arrowSpacing = DebutposY; // Ajustez cette valeur pour séparer davantage les flèches

    while (current != NULL)
    {
        // Dessiner le rectangle avec la valeur
        Rectangle rec = {xPos, DebutposY, rectWidth, rectHeight};
        DrawButton(rec, TextFormat("%d", current->data), (Color){0, 121, 211, 200});

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

    countList = countElements(&head);
    AllScreenButton = xPos;

    if (countList != c)
    {
        c = countList;
        debut = (GetScreenWidth() - (AllScreenButton - debut)) / 2;
    }
}

float fontSize = 20;
float zoomSpeed = 0.01f;
float zoomFactor = 1.0f;

// fonction POUR réinitialiser certaines variables liées à l'animation
void animationreset()
{
    fontSize = 20;
    zoomSpeed = 0.02f;
    zoomFactor = 1.0f;
}

// fonction pour dessiner le texte message qui effectue un zoom avant et arrière à mesure qu'il monte sur l'écran
void DrawZoomingText(const char *text, Vector2 *position, float *fontSize, float *zoomFactor, float zoomSpeed, int screenWidth, Color color)
{
    // Update zoom factor
    if (position->y > DebutposY + 250)
    {
        if (*fontSize < 70)
        {

            (*zoomFactor) += zoomSpeed;

            // Check for zoom boundaries
            if ((*zoomFactor) > 2.0f || (*zoomFactor) < 1.0f)
                zoomSpeed *= -1;

            // Calculate new font size
            (*fontSize) = 20 * (*zoomFactor);
        }
        // Calculate new text position based on zoom
        position->x = (GetScreenWidth() - MeasureText(text, (*fontSize))) / 2;
        position->y -= 2;

        // Draw the zooming text
        DrawText(text, (int)position->x, (int)position->y, (int)(*fontSize), color);
    }
    else
    {
        position->y = GetScreenHeight();
        animationreset();
    }
}

// fonction pour créer une liste qui contient des valeur random
void RandomNodes()
{
    int n = GetRandomValue(0, 9);
    for (int i = 0; i < n; i++)
    {
        insertNode(&head, GetRandomValue(0, 99));
    }
}

int createMode = -1; // 0: random, 1: insert at end, 2: insert at beginning

// fonction pour créer le menu de la fonction creation
void createChoicesMenu(Rectangle Rand, Rectangle End, Rectangle Begin)
{
    if (isClicked(Rand))
        createMode = 0;
    if (isClicked(End))
        createMode = 1;
    if (isClicked(Begin))
        createMode = 2;
}

// Function to delete all nodes in the linked list
void deleteAllNodes(Node **head)
{
    Node *current = *head;
    Node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

// exaiting++++++++++++++++++========================---------------------------

void formatter(char c[MAX_INPUT_CHARS + 1])
{
    for (int i = 0; i < MAX_INPUT_CHARS + 1; i++)
    {
        c[i] = '\0';
    }
}

//---------------------------------------------------------------------------------------------------------
//((((((((((((((((((((((((((((((((((((((((((((((((((((()))))))))))))))))))))))))))))))))))))))))))))))))))))
//---------------------------------------------------------------------------------------------------------

int main(void)
{
    int screenWidth = GetMonitorWidth(1);
    int screenHeight = GetMonitorHeight(1);

    bool actionRecherche = false;
    bool ActionDelete = false;
    bool ActionInsert = false;
    bool actionRechercheDelete = false;
    bool rechercher = false;
    bool createMenuActive = false;
    bool Actionsort = false;
    bool insertdebut = false;
    bool insertfin = false;
    bool insertind = false;
    bool insertval = false;

    int index = 0;
    int resultaRechercher = -1;
    int clemessage = -1;

    SetConfigFlags(FLAG_MSAA_4X_HINT); // Enable Multi Sampling Anti Aliasing 4x

    char name[MAX_INPUT_CHARS + 1] = "\0"; // Buffer to store input text (plus null terminator)
    int letterCount = 0;

    // declaration for using animation text
    const char *text = "Please entrer numbre";
    Vector2 textPosition = {(float)(screenWidth - MeasureText(text, 20)) / 2, DebutposY + 250};

    // Setup init configuration flags (view FLAGS) ========================init window ===============================

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Raylib Demo");
    ToggleFullscreen();

    Rectangle buttonCreate = {-(buttonWidth + 100), buttonPosition.y, buttonWidth, buttonHeight};
    Rectangle buttoninsert = {-(buttonWidth + 100), buttonPosition.y + buttonHeight + 10, buttonWidth, buttonHeight};
    Rectangle buttonRecherche = {-(buttonWidth + 100), buttonPosition.y + 2 * (buttonHeight + 10), buttonWidth, buttonHeight};
    Rectangle buttonDelete = {-(buttonWidth + 100), buttonPosition.y + 3 * (buttonHeight + 10), buttonWidth, buttonHeight};
    Rectangle buttonTRI = {-(buttonWidth + 100), buttonPosition.y + 4 * (buttonHeight + 10), buttonWidth, buttonHeight};

    Rectangle inputing = {(GetScreenWidth() - 350) / 2, buttonRecherche.y, 350, 100};

    Rectangle randomButton = {buttonPosition.x + buttonWidth + 10, buttonPosition.y, buttonWidth, buttonHeight};
    Rectangle endButton = {buttonPosition.x + (buttonWidth + 10) * 2, buttonPosition.y, buttonWidth + 20, buttonHeight};
    Rectangle beginningButton = {buttonPosition.x + (buttonWidth + 10) * 3 + 20, buttonPosition.y, buttonWidth + 80, buttonHeight};

    Rectangle insertDebut = {buttonPosition.x + buttonWidth + 10, buttonPosition.y + buttonHeight + 10, buttonWidth + 15, buttonHeight};
    Rectangle insertFin = {buttonPosition.x + (buttonWidth + 10) * 2 + 15, buttonPosition.y + buttonHeight + 10, buttonWidth, buttonHeight};
    Rectangle insertindex = {buttonPosition.x + (buttonWidth + 10) * 3 + 25, buttonPosition.y + buttonHeight + 10, buttonWidth + 15, buttonHeight};

    Rectangle deletedebut = {buttonPosition.x + buttonWidth + 10, buttonPosition.y + 3 * (buttonHeight + 10), buttonWidth + 10, buttonHeight};
    Rectangle deleteFin = {buttonPosition.x + (buttonWidth + 10) * 2 + 10, buttonPosition.y + 3 * (buttonHeight + 10), buttonWidth + 10, buttonHeight};
    Rectangle deleteRecherche = {buttonPosition.x + (buttonWidth + 10) * 3 + 20, buttonPosition.y + 3 * (buttonHeight + 10), buttonWidth + 30, buttonHeight};
    Rectangle deleteAll = {buttonPosition.x + (buttonWidth + 10) * 4 + 50, buttonPosition.y + 3 * (buttonHeight + 10), buttonWidth + 30, buttonHeight};

    Rectangle TriCroissant = {buttonPosition.x + buttonWidth + 10, buttonPosition.y + 4 * (buttonHeight + 10), buttonWidth + 10, buttonHeight};
    Rectangle Tridecroissant = {buttonPosition.x + (buttonWidth + 10) * 2 + 10, buttonPosition.y + 4 * (buttonHeight + 10), buttonWidth + 10, buttonHeight};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        if (IsKeyPressed(KEY_ENTER))
        {
            textPosition.y = GetScreenHeight();
            animationreset();
        }

        //************************************ begin animation ****************
        if (buttonCreate.x <= 100)
        {
            buttonCreate.x += 2;
            buttoninsert.x += 2;
            buttonRecherche.x += 2;
            buttonDelete.x += 2;
            buttonTRI.x += 2;
        }

        // move list "Left" or "Right" and where click "Space"
        if (IsKeyDown(KEY_LEFT))
        {
            debut -= 10.f;
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            debut += 10.f;
        }
        if (IsKeyPressed(KEY_SPACE))
        {
            debut = (GetScreenWidth() - (AllScreenButton - debut)) / 2;
        }

        // add minimize and maximize
        if (IsWindowResized())
        {
            // Update content or layout based on new window size
            // You can get the new width and height using:
            screenWidth = 2000;
            screenHeight = 1500;
        }

        //=====================================================insert button===========================

        if (isClicked(buttoninsert))
        {
            createMenuActive = false;
            actionRecherche = false;
            actionRechercheDelete = false;
            ActionDelete = false;
            rechercher = false;
            insertind = false;
            insertval = false;
            Actionsort = false;
            ActionInsert = !ActionInsert;
            clemessage = -1;
        }

        if (isClicked(insertDebut) && ActionInsert)
        {
            actionRecherche = !actionRecherche;
            insertdebut = actionRecherche;
            insertfin = false;
            rechercher = false;
            insertind = false;
            insertval = false;
            formatter(name);
            letterCount = 0;
            clemessage = -1;
        }

        if (insertdebut && ActionInsert)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                animationreset();
                if (letterCount == 0)
                {
                    clemessage = 0;
                }
                else
                {
                    insertNode(&head, atoi(name));
                    formatter(name);
                    letterCount = 0;
                    clemessage = -1;
                }
            }
        }

        if (isClicked(insertFin) && ActionInsert)
        {
            actionRecherche = !actionRecherche;
            insertfin = actionRecherche;
            rechercher = false;
            insertind = false;
            insertval = false;
            insertdebut = false;
            formatter(name);
            letterCount = 0;
            clemessage = -1;
        }

        if (insertfin)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                animationreset();
                if (letterCount == 0)
                {
                    clemessage = 0;
                }
                else
                {
                    insertAtend(&head, atoi(name));
                    formatter(name);
                    letterCount = 0;
                    clemessage = -1;
                }
            }
        }

        if (isClicked(insertindex) && ActionInsert)
        {
            insertfin = false;
            insertdebut = false;
            actionRecherche = false;
            insertind = !insertind;
            formatter(name);
            letterCount = 0;
            clemessage = -1;
        }

        if (insertind)
        {

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
            }
            //------------------while entrer index---------------------------
            if (IsKeyPressed(KEY_ENTER))
            {
                if (letterCount == 0)
                {
                    clemessage = 0;
                }
                else if (isValidIndex(&head) > atoi(name))
                {
                    index = atoi(name);
                    insertval = true;
                    formatter(name);
                    letterCount = 0;
                    insertind = false;
                    actionRecherche = true;
                    clemessage = -1;
                }
                else
                {
                    clemessage = 1;
                    formatter(name);
                    letterCount = 0;
                }
            }
        }
        // Search in list by index
        if (insertval)
        {
            if (IsKeyPressedRepeat(KEY_ENTER))
            {
                if (letterCount == 0)
                {
                    clemessage = 0;
                }
                else
                {
                    insertAtIndex(&head, atoi(name), index);
                    formatter(name);
                    letterCount = 0;
                    insertval = false;
                    actionRecherche = false;
                    clemessage = -1;
                }
            }
        }

        //====================================== Create Button =======================================
        if (isClicked(buttonCreate))
        {
            actionRecherche = false;
            createMenuActive = !createMenuActive;
            ActionDelete = false;
            ActionInsert = false;
            rechercher = false;
            insertind = false;
            insertval = false;
            Actionsort = false;
            clemessage = -1;
        }

        if (createMenuActive)
        {
            createChoicesMenu(randomButton, endButton, beginningButton);
        }

        if (createMode == 0)
        {
            deleteAllNodes(&head);
            RandomNodes();
            createMode = -1; // Reset for next creation
        }
        else if (createMode == 1)
        {
            // Insert at end
            insertAtend(&head, GetRandomValue(0, 99));
            createMode = -1;
        }
        else if (createMode == 2)
        {
            // Insert at beginning
            insertNode(&head, GetRandomValue(0, 99));
            createMode = -1;
        }

        //----------------------------------------------Delete Button--------------------------------------------

        // click button Delete and active Action Delete
        if (isClicked(buttonDelete))
        {
            // unactiver les button autres
            actionRecherche = false;
            rechercher = false;
            ActionInsert = false;
            createMenuActive = false;
            insertind = false;
            insertval = false;
            insertdebut = false;
            insertfin = false;
            actionRechercheDelete = false;
            ActionDelete = !ActionDelete;
            Actionsort = false;
            clemessage = -1;
        }

        // click button Rechercher Valur in List===================================
        if (isClicked(buttonRecherche))
        {
            // desaciver button is is On
            ActionDelete = false;
            ActionInsert = false;
            createMenuActive = false;
            insertind = false;
            insertval = false;
            insertfin = false;
            insertdebut = false;
            actionRechercheDelete = false;
            resultaRechercher = -1;
            clemessage = -1;
            Actionsort = false;

            actionRecherche = !actionRecherche;
            rechercher = actionRecherche;
            formatter(name);
            letterCount = 0;
        }

        // ================================ activer signal recherche ========================
        if (rechercher)
        {
            if (IsKeyReleased(KEY_ENTER))
            {

                if (letterCount == 0)
                {
                    resultaRechercher = 2; // entrz le nombre
                }
                else if (head == NULL)
                {
                    resultaRechercher = 3;
                }
                else if (searchNode(head, atoi(name)))
                {
                    resultaRechercher = 0; // value is found
                }
                else
                {
                    resultaRechercher = 1; // Value not found
                }

                formatter(name);
                letterCount = 0;
            }
        }

        // tri list if click button Tri ======================================
        if (isClicked(buttonTRI))
        {
            // turn off other button
            ActionDelete = false;
            actionRecherche = false;
            ActionInsert = false;
            rechercher = false;
            createMenuActive = false;
            insertind = false;
            insertval = false;
            Actionsort = !Actionsort;
            clemessage = -1;
        }

        // input numbre ====================================================
        if (actionRecherche)
        {
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
            }
        }

        // supprimer la première valeur d'une liste doublement chaînée
        if (isClicked(deletedebut) && ActionDelete)
        {
            actionRecherche = false;
            if (head == NULL)
            {
                clemessage = 0;
            }
            else
            {
                DeletePremiereValeur(&head);
                clemessage = -1;
            }
        }

        // supprimer la dernière valeur d'une liste doublement chaînée
        if (isClicked(deleteFin) && ActionDelete)
        {
            actionRecherche = false;
            if (head == NULL)
            {
                clemessage = 0;
            }
            else
            {
                supprimerDerniereValeur(&head);
                clemessage = -1;
            }
        }

        // click delete Recherche ===============================================
        if (isClicked(deleteRecherche) && ActionDelete)
        {
            actionRechercheDelete = !actionRechercheDelete;
            actionRecherche = actionRechercheDelete;
            formatter(name);
            letterCount = 0;
            clemessage = -1;
        }

        // activer la recherche pour delete
        if (actionRechercheDelete)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                if (head == NULL)
                {
                    clemessage = 0;
                }
                else if (letterCount == 0)
                {
                    clemessage = 1;
                }
                else if (!searchNode(head, atoi(name)))
                {
                    clemessage = 2;
                }
                else
                {
                    deleteNode(&head, atoi(name));
                    clemessage = -1;
                }

                formatter(name);
                letterCount = 0;
            }
        }

        // supprimer tout les valeurs d'une liste doublement chaînée
        if (isClicked(deleteAll) && ActionDelete)
        {
            actionRecherche = false;
            if (head == NULL)
            {
                clemessage = 0;
            }
            else
            {
                deleteAllNodes(&head);
                clemessage = -1;
            }
        }
        // Tri croissant la liste doublement chaînée
        if (isClicked(TriCroissant) && Actionsort)
        {
            if (head == NULL)
            {
                clemessage = 0;
            }
            else
            {
                sortListSelectionAscending(&head);
                clemessage = -1;
            }
        }
        // Tri Decroissant la liste doublement chaînée
        if (isClicked(Tridecroissant) && Actionsort)
        {
            if (head == NULL)
            {
                clemessage = 0;
            }
            else
            {
                sortListSelectionDescending(&head);
                clemessage = -1;
            }
        }

        //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$   Begin Draw   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
        BeginDrawing();

        // init Background
        ClearBackground(DARKGRAY);

        // =============================================Draw Button==================================

        DrawButton(buttonCreate, "Create", DARKGREEN);
        DrawButton(buttoninsert, "Insert", GOLD);
        DrawButton(buttonRecherche, "Rechercher", ORANGE);
        DrawButton(buttonDelete, "Delete", RED);
        DrawButton(buttonTRI, "Sort", GREEN);

        //_______________________________________________<input number>___________________________________
        if (actionRecherche)
            DrawButtonInput(inputing, name, BLACK);

        // _____________________________________< draw buttons creat >______________________________________
        if (createMenuActive)
        {
            DrawButton(randomButton, "Random", DARKGREEN);
            DrawButton(endButton, "Insert at End", DARKGREEN);
            DrawButton(beginningButton, "Insert at Beginning", DARKGREEN);
        }
        //_______________________________________________<draw Buttons Delete>_______________________________________
        if (ActionDelete)
        {
            DrawButton(deletedebut, "Delete Debut", RED);
            DrawButton(deleteFin, "Delete Fin", RED);
            DrawButton(deleteRecherche, "Del Rechercher", RED);
            DrawButton(deleteAll, "Delete All", RED);

            if (clemessage == 0)
            {
                DrawZoomingText("List is empty", &textPosition, &fontSize, &zoomFactor, zoomSpeed, screenWidth, RED);
            }
            else if (clemessage == 1)
            {
                DrawZoomingText("Please entrer numbre", &textPosition, &fontSize, &zoomFactor, zoomSpeed, screenWidth, BLACK);
            }
            else if (clemessage == 2)
            {
                DrawZoomingText("No such found Value", &textPosition, &fontSize, &zoomFactor, zoomSpeed, screenWidth, RED);
            }
            else
            {
                DrawZoomingText("", &textPosition, &fontSize, &zoomFactor, zoomSpeed, screenWidth, BLACK);
            }
        }
        //_______________________________________________<draw Buttons Insert>______________________________________
        if (ActionInsert)
        {
            DrawButton(insertDebut, "Insert Debut", GOLD);
            DrawButton(insertFin, "Insert Fin", GOLD);
            DrawButton(insertindex, "Insert Indice", GOLD);
        }

        //_____________________________________________draw Buttons Tri______________________________________________
        if (Actionsort)
        {
            DrawButton(TriCroissant, "Croissant", GREEN);
            DrawButton(Tridecroissant, "Decreasing", GREEN);
        }
        //_____________________________________________draw input Rechercher______________________________________________
        if (rechercher)
        {
            if (resultaRechercher == 0)
            {
                DrawZoomingText("Value is found", &textPosition, &fontSize, &zoomFactor, zoomSpeed, screenWidth, GREEN);
            }
            else if (resultaRechercher == 1)
            {
                DrawZoomingText("Value not Found", &textPosition, &fontSize, &zoomFactor, zoomSpeed, screenWidth, RED);
            }
            else if (resultaRechercher == 2)
            {
                DrawZoomingText("Please entrer numbre", &textPosition, &fontSize, &zoomFactor, zoomSpeed, screenWidth, BLACK);
            }
            else if (resultaRechercher == 3)
            {
                DrawZoomingText("List is Empty", &textPosition, &fontSize, &zoomFactor, zoomSpeed, screenWidth, RED);
            }
            else
            {

                DrawZoomingText("", &textPosition, &fontSize, &zoomFactor, zoomSpeed, screenWidth, BLACK);
            }
        }

        //===========================message insert debut======================================
        if (insertdebut)
        {
            if (clemessage == 0)
            {
                DrawZoomingText("Please entrer numbre", &textPosition, &fontSize, &zoomFactor, zoomSpeed, screenWidth, BLACK);
            }
            else
            {
                DrawZoomingText("", &textPosition, &fontSize, &zoomFactor, zoomSpeed, screenWidth, BLACK);
            }
        }

        //========================  message insert fin ==========================================
        if (insertfin)
        {
            if (clemessage == 0)
            {
                DrawZoomingText("Please entrer numbre", &textPosition, &fontSize, &zoomFactor, zoomSpeed, screenWidth, BLACK);
            }
            else
            {
                DrawZoomingText("", &textPosition, &fontSize, &zoomFactor, zoomSpeed, screenWidth, BLACK);
            }
        }
        //______________________________________________<draw index Button>___________________________
        if (insertind)
        {
            DrawButtonInput2(inputing, name, BLACK);
            if (clemessage == 0)
            {
                DrawZoomingText("Please entrer numbre index", &textPosition, &fontSize, &zoomFactor, zoomSpeed, screenWidth, BLACK);
            }
            else if (clemessage == 1)
            {
                DrawZoomingText("index plus grand la taile list", &textPosition, &fontSize, &zoomFactor, zoomSpeed, screenWidth, RED);
            }
            else
            {
                DrawZoomingText("", &textPosition, &fontSize, &zoomFactor, zoomSpeed, screenWidth, BLACK);
            }
        }

        if (insertval)
        {
            if (clemessage == 0)
            {
                DrawZoomingText("Please entrer numbre", &textPosition, &fontSize, &zoomFactor, zoomSpeed, screenWidth, BLACK);
            }
            else
            {
                DrawZoomingText("", &textPosition, &fontSize, &zoomFactor, zoomSpeed, screenWidth, BLACK);
            }
        }
        if (Actionsort)
        {
            if (clemessage == 0)
            {
                DrawZoomingText("List is Empty", &textPosition, &fontSize, &zoomFactor, zoomSpeed, screenWidth, RED);
            }
            else
            {
                DrawText("", inputing.x, DebutposY + 220, 50, RED);
            }
        }
        //((((((((((((((((((((((((((<<<<<<<<<<<<<<<<<<Draw List<<<<<<<<<<<<<<<<<)))))))))))))))))))))))))))))
        drawList();

        //===============================Close camera=============================================
        DrawFPS(10, 10);

        EndDrawing();
    }
    // close fenètre
    CloseWindow();

    return 0;
}