#include "Level.hpp"

void UpdateCameraCenter(Camera2D &camera, Player &player, Screen &envItems, float delta, int width, int height) {
    camera.offset = (Vector2){ width/2.0f, height/2.0f };
    camera.target = player.position;
}

struct Warp : RectEnvItem {
    const Level& read;
    Level& write;
    Warp(Rectangle _rect, Color _color, const Level& _read,  Level& _write) :  RectEnvItem(_rect, _color), read(_read), write(_write) {}

    void interact(Player& player) override{
        if (CheckCollisionRecs(player.getBody(), rect) && IsKeyPressed(KEY_UP)) {
            write = read;
            player.hasWon = true;
        }
    }
};

Screen loadMenu(Player& player, Level& level) {
    player.position = {0,0};
    Screen envItems = make_vector<EnvItem>(
        std::make_unique<Block>(Rectangle{-1000,0,2000,100}, GRAY),
        std::make_unique<Text>("Menu Principal", -300),
        std::make_unique<Warp>(Rectangle{-600,-100,80,100}, BLACK, testLevel, level),
        std::make_unique<Warp>(Rectangle{-200,-100,80,100}, BLACK, testLevel, level),
        std::make_unique<Warp>(Rectangle{200,-100,80,100}, BLACK, testLevel, level),
        std::make_unique<Warp>(Rectangle{600,-100,80,100}, BLACK, testLevel, level)
    );
    return envItems;
}

int main() {
    const int initialWidth = 1600;
    const int initialHeight = 900;
    int screenWidth = initialWidth;
    int screenHeight = initialHeight;

    InitWindow(screenWidth, screenHeight, "Jueguito");

    Player player;
    player.width = 40;
    player.height = 50;
    player.hasWon = true;

    Camera2D camera = {0};
    camera.target = player.position;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    Level level;
    Screen screen;

    int cameraOption = 0;

    SetTargetFPS(60);
    float time = 0;

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        time += deltaTime;

        if (IsKeyPressed(KEY_F)) {
 			int display = GetCurrentMonitor();            
                if (IsWindowFullscreen()) {
                    screenWidth = initialWidth;
                    screenHeight = initialHeight;
                } else {
                    screenWidth = GetMonitorWidth(display); 
                    screenHeight = GetMonitorHeight(display);
                }
                SetWindowSize(screenWidth, screenHeight);
 			ToggleFullscreen();
 		}

        if (IsKeyPressed(KEY_R)) screen = level.loadScreen(player);
    
        player.update(screen, deltaTime);

        UpdateCameraCenter(camera, player, screen, deltaTime, screenWidth, screenHeight);
        BeginDrawing();
            ClearBackground(SKYBLUE);
            BeginMode2D(camera);
                if (player.hasWon) {
                    level.next_screen();
                    screen = level.loadScreen(player);
                    if (screen.empty()) {
                        level = Level();
                        screen = loadMenu(player, level);
                    }
                    player.hasWon = false;
                } else if (player.isDead) {
                    screen = level.loadScreen(player);
                    player.isDead = false;
                } else {
                    for (const std::unique_ptr<EnvItem> &ei: screen) ei->draw();
                    player.draw();   
                }
            EndMode2D();            
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
