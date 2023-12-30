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
#define DebutposY GetScreenHeight() / 2
#define ListWidth 170
#define ListHeight 200

Node *head = NULL;

Vector2 buttonPosition = {100, 100};
int AllScreenButton = 1920;

bool isClicked(Rectangle rec)
{
    return CheckCollisionPointRec(GetMousePosition(), rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
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

    DrawRectangleLinesEx(rect, 10, Fade(BLANK, 120));
    DrawRectangleRec(rect, isClicked(rect) ? DARKGRAY : co);                                                       // Draw button outline
    DrawText(text, rect.x + (rect.width - MeasureText(text, 20)) / 2, rect.y + (rect.height - 20) / 2, 23, WHITE); // Draw button text
}

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
    DrawRectangleRec(rect, isClicked(rect) ? DARKGRAY : co); // Draw button outline
    DrawRectangle(rect.x + 10, rect.y + 10, rect.width - 20, rect.height - 20, GRAY);
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
    AllScreenButton = xPos;
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







// ... (existing code)

int createMode = -1; // 0: random, 1: insert at end, 2: insert at beginning

void createChoicesMenu() {
    Rectangle randomButton = {buttonPosition.x+buttonWidth+10, buttonPosition.y, buttonWidth, buttonHeight};
    Rectangle endButton = {buttonPosition.x +(buttonWidth+10)*2+10, buttonPosition.y, buttonWidth, buttonHeight};
    Rectangle beginningButton = {buttonPosition.x +(buttonWidth+10)*3+20, buttonPosition.y, buttonWidth + 70, buttonHeight};

    if (isClicked(randomButton)) createMode = 0;
    if (isClicked(endButton)) createMode = 1;
    if (isClicked(beginningButton)) createMode = 2;

    DrawButton(randomButton, "Random", DARKGREEN);
    DrawButton(endButton, "Insert at End", DARKGREEN);
    DrawButton(beginningButton, "Insert at Beginning", DARKGREEN);
}




// Function to insert a node at the beginning of the list
void insertAtBeginning(Node** head, int data) {
    data = GetRandomValue(0, 99);
    Node* newNode = createNode(data);
    newNode->next = *head;
    if (*head != NULL) (*head)->prev = newNode;
    *head = newNode;
}

// Function to insert a node at the end of the list
void insertAtEnd(Node** head, int data) {
    data = GetRandomValue(0, 99);
    Node* newNode = createNode(data);

    // If the list is empty, make the new node the head
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // Traverse to the last node
    Node* last = *head;
    while (last->next != NULL) {
        last = last->next;
    }

    last->next = newNode;
    newNode->prev = last;
}


// ... (existing code)









//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

int main(void)
{
    int screenWidth = 1500;
    int screenHeight = 1500;

    bool actionRecherche = false;
    bool Actionscroller = false;
    bool ActionDelete =false;
    bool ActionInsert=false;

    SetConfigFlags(FLAG_MSAA_4X_HINT); // Enable Multi Sampling Anti Aliasing 4x

    char name[MAX_INPUT_CHARS + 1] = "\0"; // Buffer to store input text (plus null terminator)
    int letterCount = 0;

    int scrollSpeed = 10;
    Vector2 mousePosition;

    Camera2D camera = {0};
    camera.target = (Vector2){0, 0};
    camera.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Raylib Demo");

    Rectangle buttonCreate = {buttonPosition.x, buttonPosition.y, buttonWidth, buttonHeight};
    Rectangle buttoninsert = {buttonPosition.x, buttonPosition.y + buttonHeight + 10, buttonWidth, buttonHeight};
    Rectangle buttonRecherche = {buttonPosition.x, buttonPosition.y + 2 * (buttonHeight + 10), buttonWidth, buttonHeight};
    Rectangle buttonDelete = {buttonPosition.x, buttonPosition.y + 3 * (buttonHeight + 10), buttonWidth, buttonHeight};
    Rectangle buttonTRI = {buttonPosition.x, buttonPosition.y + 4 * (buttonHeight + 10), buttonWidth, buttonHeight};
    Rectangle inputing = {GetScreenWidth() / 2, buttonRecherche.y, 350, 100};
    Rectangle scroller = {5, 1800, 550, 30};
    Rectangle deletedebut ={buttonPosition.x+buttonWidth+10, buttonPosition.y + 3 * (buttonHeight + 10), buttonWidth+10, buttonHeight};
    Rectangle deleteFin ={buttonPosition.x+(buttonWidth+10)*2+10, buttonPosition.y + 3 * (buttonHeight + 10), buttonWidth+10, buttonHeight};
    Rectangle deleteRecherche ={buttonPosition.x+(buttonWidth+10)*3+20, buttonPosition.y + 3 * (buttonHeight + 10), buttonWidth+30, buttonHeight};

    SetTargetFPS(60);

// ... (existing code)
    bool createMenuActive = false;

// ... (existing code)

 

    while (!WindowShouldClose())
    {
        // Update
        if (IsWindowResized())
        {
            // Update content or layout based on new window size
            // You can get the new width and height using:
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();
        }
        mousePosition = GetMousePosition();

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mousePosition, scroller))
            {
                Actionscroller = true;
            }
        }
        else
        {
            Actionscroller = false;
        }

    // ... (existing code)

    
    if (isClicked(buttonCreate)) {
    actionRecherche = false;
    createMenuActive = true;
    }
    

    if (createMenuActive) {
        createChoicesMenu();

        if (createMode != -1) {
            createMenuActive = false;
        }
    }

    if (createMode == 0) {
        RandomNodes();
        createMode = -1; // Reset for next creation
    } else if (createMode == 1) {
        // Insert at end
        insertAtEnd(&head, atoi(name));
        createMode = -1;
    } else if (createMode == 2) {
        // Insert at beginning
        insertAtBeginning(&head, atoi(name));
        createMode = -1;
    }

    // ... (existing code)



        if (isClicked(buttoninsert))
        {
            actionRecherche = !actionRecherche;
            ActionInsert=actionRecherche;
        }

        if(ActionInsert){ 
            if(IsKeyPressed(KEY_ENTER))
                insertNode(&head,atoi(name));
        }

        if (isClicked(buttonDelete))
        {
            actionRecherche = !actionRecherche;
            ActionDelete=actionRecherche;
        }

        if(ActionDelete){
            if (IsKeyPressed(KEY_ENTER))
                deleteNode(&head,atoi(name));
        }
            

        if (isClicked(buttonRecherche))
        {
            actionRecherche = !actionRecherche;
        }

        if (isClicked(buttonTRI))
        {
            sortListSelection(&head);
            actionRecherche=false;
        }

        if (IsKeyDown(KEY_RIGHT) && (camera.target.x >= 0))
        {
            camera.target.x += 10.0f;
            scroller.x += scrollSpeed;

            if (scroller.x + scroller.width > GetScreenWidth())
            {
                scroller.x = GetScreenWidth() - scroller.width;
            }
        }

        else if (IsKeyDown(KEY_LEFT) && (camera.target.x >= 0))
        {
            camera.target.x -= 10.0f;
            scroller.x -= scrollSpeed;
            if (scroller.x < 0)
            {
                scroller.x = 0;
                camera.target.x = 0;
            }
        }

        if (Actionscroller)
        {
            if (scroller.x < 0)
            {
                scroller.x = 0;
                camera.target.x=0;
            }
                scroller.x += GetMouseDelta().x;
                camera.target.x += GetMouseDelta().x;
        }
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

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);
        // DrawRectangle(1500 - 2200 / 2, 1000 - 1500 / 2, 2200, 1500, RAYWHITE);
        DrawRectangleRec(scroller, DARKGRAY);
        BeginMode2D(camera);

        // Draw text input rectangle
        DrawButton(buttonCreate, "Create", DARKGREEN);
        DrawButton(buttoninsert, "Insert", GOLD);
        DrawButton(buttonRecherche, "Rechercher", ORANGE);
        DrawButton(buttonDelete, "Delete", RED);
        DrawButton(buttonTRI, "Tri", GREEN);

        if(actionRecherche)
            DrawButtonInput(inputing, name, BLACK);

        if(ActionDelete){
            DrawButton(deletedebut,"Delete Debut",RED);
            DrawButton(deleteFin,"Delete Fin",RED);
            DrawButton(deleteRecherche,"Del Rechercher",RED);
        }    
        // draw list
        drawList();

        EndMode2D();
        DrawFPS(10, 10);

        EndDrawing();
    }
    // close fenètre
    CloseWindow();

    return 0;
}