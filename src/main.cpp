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

float gravity           { 5000.f };
float groundFriction    { 0.8f };
float airFriction       { 0.6f };

struct Player
{
    float jumpForce     { -1250.0f };
    float maxSpeed      { 600.0f };
    float acceleration  { 50000.0f };

    Vector2 velocity    { 0 };
    Rectangle shape     { 100, 100, 60, 80 };
    std::string name    { "Player" };

    bool isGrounded = false;

    [[nodiscard]] Vector2 GetCenter() const {
        return { shape.x + shape.width / 2, shape.y + shape.height / 2 };
    }

    void Update(float dt)
    {
        // Apply gravity if the player is not on the ground
        if (!isGrounded)
            velocity.y += gravity * dt;

        // Move player horizontally
        if (IsKeyDown(KEY_RIGHT))   velocity.x += acceleration * dt;
        if (IsKeyDown(KEY_LEFT))    velocity.x -= acceleration * dt;

        // Limit horizontal velocity
        if (velocity.x > maxSpeed)  velocity.x = maxSpeed;
        if (velocity.x < -maxSpeed) velocity.x = -maxSpeed;

        // Apply friction based on whether the player is on the ground
        float friction = isGrounded ? groundFriction : airFriction;
        velocity.x *= friction;

        // Jumping
        if (IsKeyDown(KEY_UP) && isGrounded)
        {
            velocity.y = jumpForce;
            isGrounded = false;
        }

        // Update player position
        shape.x += velocity.x * dt;
        shape.y += velocity.y * dt;

        // Check collision with ground
        int screenHeight = GetScreenHeight();
        if ((shape.y + shape.height) >= screenHeight)
        {
            shape.y = screenHeight - shape.height;
            velocity.y = 0;
            isGrounded = true;
        }
        else
            isGrounded = false;
    }

    void Draw() const
    {
        DrawRectangleRec(shape, RED);

        const int FONT_SIZE = 20;
        const int TEXT_UP_OFFSET = 23;

        int nameSize = MeasureText(name.c_str(), FONT_SIZE);

        Vector2 namePosition {
                GetCenter().x - nameSize / 2,
                shape.y - TEXT_UP_OFFSET
        };

        DrawText(name.c_str(), namePosition.x, namePosition.y, FONT_SIZE, BLACK);
    }

#ifdef DEBUG_MODE
    void DebugImGui()
    {
        ImGui::Begin("Player Debug");

        ImGui::InputText("Name", &name);

        ImGui::InputFloat2("Velocity", &velocity.x);
        ImGui::InputFloat2("Position", &shape.x);

        ImGui::InputFloat2("Size", &shape.width);

        ImGui::InputFloat("Jump Force", &jumpForce);
        ImGui::InputFloat("Max Speed", &maxSpeed);
        ImGui::InputFloat("acceleration", &acceleration);

        ImGui::End();

        DrawCircleV(GetCenter(), 3, GREEN);
    }
#endif
};

void DrawWorldOptionsDebugGui()
{
    ImGui::Begin("World Options");

    ImGui::InputFloat("Gravity", &gravity);
    ImGui::InputFloat("Ground Friction", &groundFriction);
    ImGui::InputFloat("Air Friction", &airFriction);

    ImGui::End();
}

constexpr int DefaultScreenWidth = 1000;
constexpr int DefaultScreenHeight = 650;

int main()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(DefaultScreenWidth, DefaultScreenHeight, "wall-it");
    rlImGuiSetup(true);

    SetTargetFPS(144);

    Player player;

    float deltaTime = 0.0f;
    float lastFrameTime = GetTime();

    while (!WindowShouldClose())
    {
        float currentTime = GetTime();
        deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        player.Update(deltaTime);

        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        player.Draw();

#ifdef DEBUG_MODE
        rlImGuiBegin();
        DrawWorldOptionsDebugGui();
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

