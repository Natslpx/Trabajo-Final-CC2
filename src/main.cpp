#include "Level1.hpp"
#include "Level2.hpp"
#include "Level3.hpp"
#include <thread>

void UpdateCameraCenter(Camera2D& camera, Player& player, int width,
                        int height) {
  camera.offset = {width / 2.0f, height / 2.0f};
  camera.target = player.position;
}

struct Warp : RectEnvItem {
  const Level& read;
  Level& write;
  Warp(Rectangle _rect, const Level& _read, Level& _write) :
      RectEnvItem(_rect, BLACK),
      read(_read),
      write(_write) {}

  void interact(Player& player) override {
    if (CheckCollisionRecs(player.getBody(), rect) && player.controller.up()) {
      write = read;
      player.hasWon = true;
    }
  }

  void draw() override {
    RectEnvItem::draw();
    DrawTriangle(Vector2{rect.x + rect.width / 4, rect.y + rect.height / 2},
                 Vector2{rect.x + 3 * rect.width / 4, rect.y + rect.height / 2},
                 Vector2{rect.x + rect.width / 2, rect.y + rect.height / 4},
                 WHITE);
  }
};

Screen loadMenu(Player& player, Level& level) {
  player.position = {800, 450};
  return make_screen<EnvItem>(
      Block(Rectangle{0, 450, 1600, 100}, GRAY),
      Text("Menu Principal", 600, 450),
      Warp(Rectangle{320, 350, 80, 100}, level1, level),
      Warp(Rectangle{640, 350, 80, 100}, level2, level),
      Warp(Rectangle{960, 350, 80, 100}, level3, level),
      Warp(Rectangle{1280, 350, 80, 100}, level3, level));
}

struct Window {
  static constexpr int initialWidth = 1600;
  static constexpr int initialHeight = 900;

  Window(const char* name) {
    InitWindow(initialWidth, initialHeight, name);
    SetTargetFPS(60);
    BeginDrawing();
    EndDrawing();
  }
  ~Window() {
    CloseWindow();
  }
};

class Game {
  int screenWidth = Window::initialWidth;
  int screenHeight = Window::initialHeight;
  // Initializes required graphic context, careful placement needed
  const Window ventana{"Jueguito"};

  std::vector<Player> players = make_vector<Player>(Player());
  Camera2D camera = {{screenWidth / 2.0f, screenHeight / 2.0f},
                     players[0].position,
                     0.0f,
                     1.0f};
  Level level;
  Screen screen = loadMenu(players[0], level);

  void draw() const {
    BeginDrawing();
    ClearBackground(SKYBLUE);
    BeginMode2D(camera);
    for (const std::unique_ptr<EnvItem>& ei : screen)
      ei->draw();
    for (const Player& player : players)
      if (!player.hasWon)
        player.draw();
    EndMode2D();
    EndDrawing();
  }

  void update() {
    float deltaTime = GetFrameTime();
    if (IsKeyPressed(KEY_F)) {
      int display = GetCurrentMonitor();
      if (IsWindowFullscreen()) {
        screenWidth = Window::initialWidth;
        screenHeight = Window::initialHeight;
      } else {
        screenWidth = GetMonitorWidth(display);
        screenHeight = GetMonitorHeight(display);
      }
      SetWindowSize(screenWidth, screenHeight);
      ToggleFullscreen();
    }

    if (IsKeyPressed(KEY_R) && !level.empty()) {
      screen = level.loadScreen(players[0]);
      for (auto& other_player : players)
        other_player.position = players[0].position;
    }

    bool everybody_won = true;
    bool anyone_dead = false;
    std::vector<std::thread> threads;
    for (Player& player : players) {
      if (!player.hasWon) {
        threads.emplace_back([&] {
          player.update(screen, deltaTime);
        });
        everybody_won = false;
      }
      if (player.isDead) {
        anyone_dead = true;
      }
    }
    for (std::thread& thread : threads)
      thread.join();

    if (everybody_won) {
      level.next_screen();
      screen = level.loadScreen(players[0]);
      if (screen.empty()) {
        level = Level();
        screen = loadMenu(players[0], level);
      }
      for (Player& player : players) {
        player.hasWon = false;
        player.position = players[0].position;
      }
    } else if (anyone_dead) {
      screen = level.loadScreen(players[0]);
      for (Player& player : players) {
        player.isDead = false;
        player.position = players[0].position;
      }
    }
    UpdateCameraCenter(camera, players[0], 1600, 900);
  }

public:
  Game() {
    for (int gamepad = 0; gamepad < 3; ++gamepad) {
      if (IsGamepadAvailable(gamepad)) {
        players.emplace_back(gamepad);
      }
    }
  }
  ~Game() = default;

  void run() {
    while (!WindowShouldClose()) {
      update();
      draw();
    }
  }
};

int main() {
  Game().run();
}
