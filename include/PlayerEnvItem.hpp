#ifndef PLAYER_AND_ENV_ITEM_HPP
#define PLAYER_AND_ENV_ITEM_HPP

#include "raylib.h"
#include "raymath.h"

#include <functional>
#include <memory>
#include <vector>

struct Player;

struct EnvItem {
  Color color;

  EnvItem(Color _color) : color(_color) {}
  virtual ~EnvItem() = default;
  virtual void interact(Player& player) = 0;
  virtual void draw() = 0;
};

class Texture2DRaii {
  Texture2D texture;

public:
  Texture2DRaii() : texture{} {}
  Texture2DRaii(const char* str) : texture(LoadTexture(str)) {}

  Texture2DRaii(const Texture2DRaii&) = delete;
  Texture2DRaii& operator=(const Texture2DRaii&) = delete;

  Texture2DRaii(Texture2DRaii&& other) {
    texture = other.texture;
    other.texture.id = 0;
  }
  Texture2DRaii& operator=(Texture2DRaii&& other) {
    if (this != &other) {
      texture = other.texture;
      other.texture.id = 0;
    }
    return *this;
  }
  ~Texture2DRaii() noexcept {
    UnloadTexture(texture);
  }

  const Texture2D& get() const {
    return texture;
  }
};

struct Window {
  static constexpr int initialWidth = 1600;
  static constexpr int initialHeight = 900;
  Window() {
    InitWindow(initialWidth, initialHeight, "Jueguito");
    SetTargetFPS(60);
    BeginDrawing();
    EndDrawing();
  }
  ~Window() {
    CloseWindow();
  }
};

struct Player {
  // Initializes required graphic context
  inline static const Window ventana;

  Texture2DRaii base{"images/monkey_base.png"};
  Texture2DRaii base_dashed{"images/monkey_dashed.png"};
  Texture2DRaii grabing{"images/monkey_grabbing.png"};
  Texture2DRaii grabbing_dashed{"images/monkey_grabbing_dashed.png"};
  Texture2DRaii walking{"images/monkey_walking.png"};
  Texture2DRaii climbing{"images/monkey_climbing.png"};
  Texture2DRaii climbing_dashed{"images/monkey_climbing_dashed.png"};
  Texture2DRaii jumping{"images/monkey_jumping.png"};
  Texture2DRaii jumping_dashed{"images/monkey_jumping_dashed.png"};

  static constexpr float gravity = 2450.0f;
  static constexpr float walkSpeed = 500.0f;
  static constexpr float jumpSpeed = 860.0f;
  static constexpr float dashSpeed = 1230.0f;
  static constexpr float climbSpeed = 250.0f;
  static constexpr int max_stamina = 110;
  static constexpr float width = 40;
  static constexpr float height = 50;

  int walking_timer = 0;
  int climbing_timer = 0;

  Vector2 position = {0, 0};
  Vector2 velocity = {0, 0};

  bool canJump = false;
  bool canDash = true;
  bool onGround = false;
  bool onWallLeft = false;
  bool onWallRight = false;
  bool isGrabbing = false;
  int isDashing = 0;
  int isWallJumping = 0;
  bool hasJumped = false;
  int stamina = max_stamina;
  bool facing;

  bool isDead = false;
  bool hasWon = true;

  float horizontal = 0;
  float vertical = 0;

  const int UP;
  const int DOWN;
  const int LEFT;
  const int RIGHT;
  const int JUMP;
  const int DASH;
  const int GRAB1;
  const int GRAB2;
  const std::function<bool(int)> isInputDown;
  const std::function<bool(int)> isInputPressed;

  float getHorizontal() {
    if (isInputDown(LEFT)) {
      horizontal -= 0.05;
    } else if (isInputDown(RIGHT)) {
      horizontal += 0.05;
    } else if (horizontal > 0) {
      horizontal -= 0.05;
    } else if (horizontal < 0) {
      horizontal += 0.05;
    }

    if (horizontal > 1.0f) {
      horizontal = 1.0f;
    } else if (horizontal < -1.0f) {
      horizontal = -1.0f;
    } else if (abs(horizontal) < 0.01) {
      horizontal = 0;
    }

    return horizontal;
  }
  float getVertical() {
    if (isInputDown(UP)) {
      vertical -= 0.05;
    } else if (isInputDown(DOWN)) {
      vertical += 0.05;
    } else if (vertical > 0) {
      vertical -= 0.05;
    } else if (vertical < 0) {
      vertical += 0.05;
    }

    if (vertical > 1.0f) {
      vertical = 1.0f;
    } else if (vertical < -1.0f) {
      vertical = -1.0f;
    } else if (abs(vertical) < 0.01) {
      vertical = 0;
    }

    return vertical;
  }

  int rawHorizontal() const {
    if (isInputDown(LEFT))
      return -1;
    if (isInputDown(RIGHT))
      return 1;
    return 0;
  }

  int rawVertical() const {
    if (isInputDown(UP))
      return -1;
    if (isInputDown(DOWN))
      return 1;
    return 0;
  }

  Rectangle getBody() const {
    return Rectangle{position.x - width / 2, position.y - height, width,
                     height};
  }

  void draw() const {
    const Texture2DRaii* sprite = &base;
    Rectangle spriteRect;
    int timer = 0;
    if (isGrabbing) {
      if (rawVertical() != 0) {
        timer = climbing_timer;
        sprite = canDash ? &climbing : &climbing_dashed;
        spriteRect =
            facing
                ? Rectangle{int(timer / 10) * width, 0, width, height}
                : Rectangle{(int(timer / 10) + 1) * width, 0, -width, height};
      } else {
        if (onWallRight) {
          spriteRect = Rectangle{width, 0, -width, height};
        } else {
          spriteRect = Rectangle{0, 0, width, height};
        }

        if (canDash) {
          sprite = &grabing;
        } else {
          sprite = &grabbing_dashed;
        }
      }

    } else if (onGround) {
      if (rawHorizontal() != 0) {
        timer = walking_timer;
        sprite = &walking;
      } else {
        if (canDash) {
          sprite = &base;
        } else {
          sprite = &base_dashed;
        }
      }

      spriteRect =
          facing ? Rectangle{int(timer / 10) * width, 0, width, height}
                 : Rectangle{int(timer / 10 + 1) * width, 0, -width, height};
    } else {
      sprite = canDash ? &jumping : &jumping_dashed;
      spriteRect = facing ? Rectangle{0, 0, width, height}
                          : Rectangle{width, 0, -width, height};
    }
    bool isTired = stamina < 30;
    DrawTextureRec(sprite->get(), spriteRect,
                   position - Vector2{width / 2, height},
                   isTired ? RED : WHITE);
  }

  void update(std::vector<std::unique_ptr<EnvItem>>& envItems, float delta) {
    float x = getHorizontal();
    float y = getVertical();

    if (isDashing)
      isDashing--;
    if (isWallJumping)
      isWallJumping--;

    onGround = onWallLeft = onWallRight = false; // Colisiones
    for (std::unique_ptr<EnvItem>& ei : envItems)
      ei->interact(*this);

    if (rawHorizontal() == 1.0f)
      facing = true;
    else if (rawHorizontal() == -1.0f)
      facing = false;

    if (!isGrabbing && !isDashing) { // Caminar
      if (abs(x) > 0.01f) {
        velocity.x = x * walkSpeed;
      } else {
        velocity.x *= 0.9;
      }
    }

    if (isInputPressed(JUMP) && canJump) { // Salto
      velocity.y = -jumpSpeed;
      canJump = false;
      hasJumped = true;
      onGround = false;
    } else if (isInputPressed(JUMP) && !isDashing &&
               (onWallLeft || onWallRight)) { // Wall Jump
      velocity.y = -jumpSpeed;
      velocity.x = onWallLeft ? walkSpeed : -walkSpeed;
      canJump = false;
      isWallJumping = true;
      hasJumped = true;
      stamina -= 27.5;
    }

    if (isInputPressed(DASH) && canDash && !isDashing) { // Dash
      if (rawHorizontal() != 0 || rawVertical() != 0) {
        velocity = Vector2Normalize(
                       Vector2{(float)rawHorizontal(), (float)rawVertical()}) *
                   dashSpeed;
        canDash = false;
        isDashing = 14;
        onGround = false;
        hasJumped = false;
      }
    }

    if ((!onWallLeft || velocity.x >= 0) &&
        (!onWallRight || velocity.x <= 0)) { // Movimiento horizontal
      position.x += velocity.x * delta;
    } else {
      velocity.x = 0;
    }

    isGrabbing = false;
    if (!onGround) { // Movimiento vertical aéreo
      if ((onWallLeft || onWallRight) &&
          (isInputDown(GRAB1) || isInputDown(GRAB2)) && !isWallJumping &&
          stamina > 0) { // Climb
        isGrabbing = true;
        if (rawVertical() != 0) {
          climbing_timer += rawVertical() == 1 ? 1 : -1;
          climbing_timer %= 40;
          velocity.y = rawVertical() * climbSpeed;
          stamina -= 45.45 * delta;
        } else {
          climbing_timer = 0;
          stamina -= 10 * delta;
          velocity.y = 0;
        }
      } else if (!isInputDown(JUMP) && velocity.y < 0 && hasJumped) {
        velocity.y += 1.75f * gravity * delta; // Salto corto
      } else if (!isDashing) {                 // Salto completo || Caída normal
        velocity.y += gravity * delta;
      } else {
        velocity.y *= 0.94; // Gravedad de dash
      }
      canJump = false;
      position.y += velocity.y * delta;
    } else { // Movimiento vertical a tierra
      if (rawHorizontal() != 0) {
        walking_timer += 1;
        walking_timer %= 40;
      } else
        walking_timer = 0;
      if (velocity.y < 0) {
        position.y += velocity.y * delta; // Movimiento hacia arriba
      } else {
        velocity.y = 0;
      }
      canDash = true;
      canJump = true;
      hasJumped = false;
      stamina = max_stamina;
    }
  }

  Player() :
      isInputDown([](int KEY) {
        return IsKeyDown(KEY);
      }),
      isInputPressed([](int KEY) {
        return IsKeyPressed(KEY);
      }),
      UP(KEY_UP),
      DOWN(KEY_DOWN),
      LEFT(KEY_LEFT),
      RIGHT(KEY_RIGHT),
      JUMP(KEY_C),
      DASH(KEY_X),
      GRAB1(KEY_Z),
      GRAB2(KEY_V) {} // Jugador principal (teclado)

  Player(int gamepadNumber) :
      isInputDown([gamepadNumber](int BUTTON) {
        return IsGamepadButtonDown(gamepadNumber, BUTTON);
      }),
      isInputPressed([gamepadNumber](int BUTTON) {
        return IsGamepadButtonPressed(gamepadNumber, BUTTON);
      }),
      UP(GAMEPAD_BUTTON_LEFT_FACE_UP),
      DOWN(GAMEPAD_BUTTON_LEFT_FACE_DOWN),
      LEFT(GAMEPAD_BUTTON_LEFT_FACE_LEFT),
      RIGHT(GAMEPAD_BUTTON_LEFT_FACE_RIGHT),
      JUMP(GAMEPAD_BUTTON_RIGHT_FACE_DOWN),
      DASH(GAMEPAD_BUTTON_RIGHT_FACE_LEFT),
      GRAB1(GAMEPAD_BUTTON_LEFT_TRIGGER_1),
      GRAB2(GAMEPAD_BUTTON_RIGHT_TRIGGER_1) {} // Jugador de mando

  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;
  Player& operator=(Player&& other) = delete;
  Player(Player&& other) noexcept = default;
};

#endif // !PLAYER_AND_ENV_ITEM_HPP
