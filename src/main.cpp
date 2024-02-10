/*******************************************************************************************
*
*   LayoutName v1.0.0 - Tool Description
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include <imgui.h>
#include <rlImGui.h>

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------
static void Button001();

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "layout_name");
    rlImGuiSetup(true);

    // layout_name: controls initialization
    //----------------------------------------------------------------------------------
    const char *WindowBox000Text = "SAMPLE TEXT";
    const char *Button001Text = "SAMPLE TEXT";
    const char *Slider004Text = "";
    const char *Spinner003Text = "";
    
    Vector2 anchor01 = { 40, 40 };
    Vector2 anchor02 = { 48, 72 };
    
    bool WindowBox000Active = true;
    bool TextBox002EditMode = false;
    char TextBox002Text[128] = "SAMPLE TEXT";
    bool Spinner003EditMode = false;
    int Spinner003Value = 0;
    float Slider004Value = 0.0f;

    Rectangle layoutRecs[5] = {
        { anchor02.x + 8, anchor02.y + 16, 160, 176 },
        { anchor02.x + 24, anchor02.y + 48, 120, 24 },
        { anchor02.x + 24, anchor02.y + 80, 120, 24 },
        { anchor02.x + 24, anchor02.y + 112, 120, 24 },
        { anchor02.x + 24, anchor02.y + 152, 120, 16 },
    };
    //----------------------------------------------------------------------------------

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            if (WindowBox000Active)
            {
                WindowBox000Active = !GuiWindowBox(layoutRecs[0], WindowBox000Text);
                if (GuiButton(layoutRecs[1], Button001Text)) Button001(); 
                if (GuiTextBox(layoutRecs[2], TextBox002Text, 128, TextBox002EditMode)) TextBox002EditMode = !TextBox002EditMode;
                if (GuiSpinner(layoutRecs[3], Spinner003Text, &Spinner003Value, 0, 100, Spinner003EditMode)) Spinner003EditMode = !Spinner003EditMode;
                GuiSlider(layoutRecs[4], Slider004Text, NULL, &Slider004Value, 0, 100);
            }
            //----------------------------------------------------------------------------------

            // imgui: render
            //----------------------------------------------------------------------------------
            // start ImGui Conent
            rlImGuiBegin();

            // show ImGui Content
            bool open = true;
            ImGui::ShowDemoWindow(&open);

            // end ImGui Content
            rlImGuiEnd();
            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    rlImGuiShutdown();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------
static void Button001()
{
    // TODO: Implement control logic
}

