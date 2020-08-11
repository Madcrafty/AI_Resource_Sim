// Graphing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "raylib.h"
#include "Graph2D.h"
#include "Graph2DEditor.h"

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    Graph2D myGraph;

    int numRows = 10;
    int numCols = 17;
    float xOffset = 0;
    float yOffset = 0;
    float spacing = 50;

    for (size_t y = 0; y < numRows; y++)
    {
        for (size_t x = 0; x < numCols; x++)
        {
            myGraph.AddNode({
                x * spacing + xOffset,
                y * spacing + yOffset
                });
        }
    }

    for (auto node : myGraph.GetNodes()) 
    {
        std::vector<Graph2D::Node*> nearbyNodes;
        myGraph.GetNearbyNodes(node, 60, nearbyNodes);

        for (auto connectedNode : nearbyNodes)
        {
            float dist = Vector2Distance(node->data, connectedNode->data);
            myGraph.AddEdge(node, connectedNode, dist);
            myGraph.AddEdge(connectedNode, node, dist);
        }
    }



    Graph2DEditor graphEditor;
    graphEditor.SetGraph(&myGraph);

    

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    float deltaTime = 0;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        deltaTime = GetFrameTime();
        graphEditor.Update(deltaTime);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        graphEditor.Draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    //delete &myGraph;
    //delete &graphEditor;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
