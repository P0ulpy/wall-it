#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <rlImGui.h>

#define DEBUG_MODE

#ifdef DEBUG_MODE
#include <imgui.h>
#include <imgui_stdlib.h>
#endif

#include <string>

struct Player
{
    Vector2 velocity { 0 };
    Rectangle shape { 100, 100, 40, 60 };
    std::string name { "Player" };

    Vector2 GetCenter() const {
        return { shape.x + shape.width / 2, shape.y + shape.height / 2 };
    }

#ifdef DEBUG_MODE
    void DebugImGui()
    {
        ImGui::Begin("Player Debug");

        ImGui::InputFloat2("Velocity", &velocity.x);
        ImGui::InputFloat2("Position", &shape.x);
        ImGui::Text("Center: (%.2f, %.2f)", GetCenter().x, GetCenter().y);

        ImGui::InputText("Name", &name);

        ImGui::End();
    }
#endif
};

void DrawPlayer(const Player& player)
{
    DrawRectangleRec(player.shape, RED);

    const int FONT_SIZE = 10;
    const int TEXT_UP_OFFSET = 12;

    int nameSize = MeasureText(player.name.c_str(), FONT_SIZE);

    Vector2 namePosition {
        player.GetCenter().x - nameSize / 2,
        player.shape.y - TEXT_UP_OFFSET
    };

    DrawText(player.name.c_str(), namePosition.x, namePosition.y, FONT_SIZE, BLACK);
}

void UpdatePlayer(Player& player)
{
    player.shape.x += player.velocity.x;
    player.shape.y += player.velocity.y;
}

int main()
{
    int screenWidth = 800;
    int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "wall-it");
    rlImGuiSetup(true);

    SetTargetFPS(144);

    Player player;

    while (!WindowShouldClose())
    {
       UpdatePlayer(player);

        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

            DrawPlayer(player);

#ifdef DEBUG_MODE
            rlImGuiBegin();
                player.DebugImGui();
            rlImGuiEnd();
#endif

        EndDrawing();
    }

#ifdef DEBUG_MODE
    rlImGuiShutdown();
#endif
    CloseWindow();

    return 0;
}

