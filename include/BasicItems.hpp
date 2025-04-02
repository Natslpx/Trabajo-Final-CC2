#include "raylib.h"
#include "raymath.h"

#include <functional>
#include <memory>
#include <utility>
#include <vector>

#ifndef BASIC_ITEMS_H
#define BASIC_ITEMS_H

struct Player;

struct EnvItem {
  Color color;

  EnvItem(Color _color) : color(_color) {}
  virtual void interact(Player& player) = 0;
  virtual void draw() = 0;
};

struct Player {
  Texture2D sprite_base;
  Texture2D sprite_base_dashed;
  Texture2D sprite_grabing;
  Texture2D sprite_grabbing_dashed;
  Texture2D sprite_walking;
  Texture2D sprite_climbing;
  Texture2D sprite_climbing_dashed;
  Texture2D sprite_jumping;
  Texture2D sprite_jumping_dashed;

  mutable int walking_timer = 0;
  mutable int climbing_timer = 0;

  const float gravity = 2450.0f;
  const float walkSpeed = 500.0f;
  const float jumpSpeed = 860.0f;
  const float dashSpeed = 1230.0f;
  const float climbSpeed = 250.0f;
  const int MAX_STAMINA = 110;

  Vector2 position = {0, 0};
  Vector2 velocity = {0, 0};

  const float width = 40;
  const float height = 50;

  bool canJump = false;
  bool canDash = true;
  bool onGround = false;
  bool onWallLeft = false;
  bool onWallRight = false;
  bool isGrabbing = false;
  int isDashing = 0;
  int isWallJumping = 0;
  bool hasJumped = false;
  int stamina = MAX_STAMINA;
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
    Texture2D sprite = sprite_base;
    Rectangle spriteRect;
    int timer = 0;
    if (isGrabbing) {
      if (rawVertical() != 0) {
        climbing_timer += rawVertical() == 1 ? 1 : -1;
        climbing_timer %= 40;
        timer = climbing_timer;

        sprite = canDash ? sprite_climbing : sprite_climbing_dashed;
        spriteRect =
            facing ? Rectangle{(timer / 10) * width, 0, width, height}
                   : Rectangle{((timer / 10) + 1) * width, 0, -width, height};
      } else {
        climbing_timer = 0;

        if (onWallRight) {
          spriteRect = Rectangle{width, 0, -width, height};
        } else {
          spriteRect = Rectangle{0, 0, width, height};
        }

        if (canDash) {
          sprite = sprite_grabing;
        } else {
          sprite = sprite_grabbing_dashed;
        }
      }

    } else if (onGround) {
      if (rawHorizontal() != 0) {
        walking_timer += 1;
        walking_timer %= 40;
        timer = walking_timer;

        sprite = sprite_walking;
      } else {
        walking_timer = 0;

        if (canDash) {
          sprite = sprite_base;
        } else {
          sprite = sprite_base_dashed;
        }
      }

      spriteRect =
          facing ? Rectangle{(timer / 10) * width, 0, width, height}
                 : Rectangle{((timer / 10) + 1) * width, 0, -width, height};
    } else {
      sprite = canDash ? sprite_jumping : sprite_jumping_dashed;
      spriteRect = facing ? Rectangle{0, 0, width, height}
                          : Rectangle{width, 0, -width, height};
    }
    bool isTired = stamina < 30;
    DrawTextureRec(sprite, spriteRect, position - Vector2{width / 2, height},
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
          velocity.y = rawVertical() * climbSpeed;
          stamina -= 45.45 * delta;
        } else {
          stamina -= 10 * delta;
          velocity.y = 0;
        }
      } else if (!isInputDown(JUMP) && velocity.y < 0 &&
                 hasJumped) { // Salto corto
        velocity.y += 1.75f * gravity * delta;
      } else if (!isDashing) { // Salto completo || Caída normal
        velocity.y += gravity * delta;
      } else {
        velocity.y *= 0.94; // Gravedad de dash
      }
      canJump = false;
      position.y += velocity.y * delta;
    } else { // Movimiento vertical a tierra
      if (velocity.y < 0) {
        position.y += velocity.y * delta; // MOvimiento hacia arriba
      } else {
        velocity.y = 0;
      }
      canDash = true;
      canJump = true;
      hasJumped = false;
      stamina = MAX_STAMINA;
    }
  }

  Player() :
      sprite_base(LoadTexture("../images/monkey_base.png")),
      sprite_base_dashed(LoadTexture("../images/monkey_dashed.png")),
      sprite_grabing(LoadTexture("../images/monkey_grabbing.png")),
      sprite_grabbing_dashed(
          LoadTexture("../images/monkey_grabbing_dashed.png")),
      sprite_walking(LoadTexture("../images/monkey_walking.png")),
      sprite_climbing(LoadTexture("../images/monkey_climbing.png")),
      sprite_climbing_dashed(
          LoadTexture("../images/monkey_climbing_dashed.png")),
      sprite_jumping(LoadTexture("../images/monkey_jumping.png")),
      sprite_jumping_dashed(LoadTexture("../images/monkey_jumping_dashed.png")),
      isInputDown([](int KEY) {
        return IsKeyDown(KEY);
      }),
      isInputPressed([](int KEY) {
        return IsKeyPressed(KEY);
      }),
      UP((int)KEY_UP),
      DOWN((int)KEY_DOWN),
      LEFT((int)KEY_LEFT),
      RIGHT((int)KEY_RIGHT),
      JUMP((int)KEY_C),
      DASH((int)KEY_X),
      GRAB1((int)KEY_Z),
      GRAB2((int)KEY_V) {} // Jugador principal (teclado)

  Player(int gamepadNumber) :
      sprite_base(LoadTexture("../images/monkey_base.png")),
      sprite_base_dashed(LoadTexture("../images/monkey_dashed.png")),
      sprite_grabing(LoadTexture("../images/monkey_grabbing.png")),
      sprite_grabbing_dashed(
          LoadTexture("../images/monkey_grabbing_dashed.png")),
      sprite_walking(LoadTexture("../images/monkey_walking.png")),
      sprite_climbing(LoadTexture("../images/monkey_climbing.png")),
      sprite_climbing_dashed(
          LoadTexture("../images/monkey_climbing_dashed.png")),
      sprite_jumping(LoadTexture("../images/monkey_jumping.png")),
      sprite_jumping_dashed(LoadTexture("../images/monkey_jumping_dashed.png")),
      isInputDown([gamepadNumber](int BUTTON) {
        return IsGamepadButtonDown(gamepadNumber, BUTTON);
      }),
      isInputPressed([gamepadNumber](int BUTTON) {
        return IsGamepadButtonPressed(gamepadNumber, BUTTON);
      }),
      UP((int)GAMEPAD_BUTTON_LEFT_FACE_UP),
      DOWN((int)GAMEPAD_BUTTON_LEFT_FACE_DOWN),
      LEFT((int)GAMEPAD_BUTTON_LEFT_FACE_LEFT),
      RIGHT((int)GAMEPAD_BUTTON_LEFT_FACE_RIGHT),
      JUMP((int)GAMEPAD_BUTTON_RIGHT_FACE_DOWN),
      DASH((int)GAMEPAD_BUTTON_RIGHT_FACE_LEFT),
      GRAB1((int)GAMEPAD_BUTTON_LEFT_TRIGGER_1),
      GRAB2((int)GAMEPAD_BUTTON_RIGHT_TRIGGER_1) {} // Jugador de mando

  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;
  Player& operator=(Player&& other) = delete;

  Player(Player&& other) noexcept :
      sprite_base(other.sprite_base),
      sprite_base_dashed(other.sprite_base_dashed),
      sprite_grabing(other.sprite_grabing),
      sprite_grabbing_dashed(other.sprite_grabbing_dashed),
      sprite_walking(other.sprite_walking),
      sprite_climbing(other.sprite_climbing),
      sprite_climbing_dashed(other.sprite_climbing_dashed),
      sprite_jumping(other.sprite_jumping),
      sprite_jumping_dashed(other.sprite_jumping_dashed),
      UP(other.UP),
      DOWN(other.DOWN),
      LEFT(other.LEFT),
      RIGHT(other.RIGHT),
      JUMP(other.JUMP),
      DASH(other.DASH),
      GRAB1(other.GRAB1),
      GRAB2(other.GRAB2),
      isInputDown(std::move(other.isInputDown)),
      isInputPressed(std::move(other.isInputPressed)) {

    other.sprite_base.id = 0;
    other.sprite_base_dashed.id = 0;
    other.sprite_grabing.id = 0;
    other.sprite_grabbing_dashed.id = 0;
    other.sprite_walking.id = 0;
    other.sprite_climbing.id = 0;
    other.sprite_climbing_dashed.id = 0;
    other.sprite_jumping.id = 0;
    other.sprite_jumping_dashed.id = 0;
  }

  ~Player() {
    UnloadTexture(sprite_base);
    UnloadTexture(sprite_base_dashed);
    UnloadTexture(sprite_grabing);
    UnloadTexture(sprite_grabbing_dashed);
    UnloadTexture(sprite_walking);
    UnloadTexture(sprite_climbing);
    UnloadTexture(sprite_climbing_dashed);
    UnloadTexture(sprite_jumping);
    UnloadTexture(sprite_jumping_dashed);
  }
};

struct RectEnvItem : EnvItem {
  Rectangle rect;

  RectEnvItem(Rectangle _rect, Color _color) : rect(_rect), EnvItem(_color) {}
  void draw() override {
    DrawRectangleRec(rect, color);
  }
};

struct NonInteractable : RectEnvItem {
  void interact(Player& player) override {}
  using RectEnvItem::RectEnvItem;
};

struct Block : RectEnvItem {
  void interact(Player& player) override {
    Vector2& p = player.position;

    if (!player.onWallLeft) {
      if (player.onWallLeft = CheckCollisionCircleRec(
              p + Vector2{-(player.width / 2 - 5), -player.height / 2}, 5,
              rect)) {
        p.x = rect.x + rect.width + 20;
        if (player.velocity.y < 0 && !player.isWallJumping)
          player.velocity.y = 0;
        player.horizontal = 0;
        player.isWallJumping = false;
      }
    }
    if (!player.onWallRight) {
      if (player.onWallRight = CheckCollisionCircleRec(
              p + Vector2{player.width / 2 - 5, -player.height / 2}, 5, rect)) {
        p.x = rect.x - 20;
        if (player.velocity.y < 0 && !player.isWallJumping)
          player.velocity.y = 0;
        player.horizontal = 0;
        player.isWallJumping = false;
      }
    }
    if (!player.onGround) {
      if (player.onGround =
              CheckCollisionCircleRec(p + Vector2{-5, 0}, 5, rect)) {
        player.position.y = rect.y;
      }
    }

    if (CheckCollisionCircleRec(p + Vector2{-5, -player.height}, 5, rect)) {
      player.position.y = rect.y + rect.height + player.height;
    }
  }
  using RectEnvItem::RectEnvItem;
};

struct NonClimbable : Block {
  void interact(Player& player) override {
    bool wasWallLeft = player.onWallLeft;
    bool wasWallRight = player.onWallRight;
    this->Block::interact(player);
    player.onWallLeft = wasWallLeft;
    player.onWallRight = wasWallRight;
  }

  using Block::Block;
};

struct MoveBlock : Block {
  bool fall;
  int timer;
  std::function<bool(MoveBlock&)> condition;

  const float displacement = 5;
  const Vector2 direction;
  void interact(Player& player) override {
    short old_state =
        player.onGround + player.onWallLeft * 2 + player.onWallRight * 4;
    this->Block::interact(player);
    short new_state =
        player.onGround + player.onWallLeft * 2 + player.onWallRight * 4;
    if (old_state != new_state) {
      if (!fall) {
        fall = true;
        timer = 10;
        color = RED;
      } else if (condition(*this) && !timer) {
        player.position += direction * displacement;
      }
    }
  }

  void draw() override {
    if (fall && condition(*this)) {
      if (timer) {
        timer--;
      } else {
        rect.x += direction.x * displacement;
        rect.y += direction.y * displacement;
      }
    }
    Block::draw();
  }

  MoveBlock(Rectangle _rect, Color _color, Vector2 _direction,
            bool (*_condition)(MoveBlock&)) :
      fall(false),
      Block(_rect, _color),
      direction(Vector2Normalize(_direction)),
      condition(_condition) {}
};

struct Jumper : RectEnvItem {
  void interact(Player& player) override {
    if (CheckCollisionRecs(player.getBody(), rect)) {
      player.position.y -= 10;
      player.velocity.y -= player.dashSpeed;
      player.velocity.x = 0;
      // player.position.x = rect.x + rect.width/2; //Center player on jumper
      player.canDash = true;
      player.canJump = false;
      player.stamina = player.MAX_STAMINA;
    }
  }

  Jumper(float x, float y) :
      RectEnvItem(Rectangle{x - 30, y - 5, 60, 15}, BROWN) {}
};

struct Gem : EnvItem {
  bool active;
  int timer;
  Vector2 center;
  void interact(Player& player) override {
    if (CheckCollisionCircleRec(Vector2{center.x, center.y}, 30,
                                player.getBody()) &&
        !timer && !player.canDash) {
      player.canDash = true;
      player.stamina = player.MAX_STAMINA;
      timer = 150;
      color = GRAY;
    }
  }

  Gem(float x, float y) : timer(0), center(Vector2{x, y}), EnvItem(GREEN) {}
  Gem(Vector2 _center) : timer(0), center(_center), EnvItem(GREEN) {}

  void draw() override {
    DrawCircleV(center, 30, color);
    if (timer != 0) {
      if (!--timer) {
        color = GREEN;
      }
    }
  }
};

struct Spikes : RectEnvItem {
  void interact(Player& player) override {
    player.isDead = player.isDead || CheckCollisionRecs(player.getBody(), rect);
  }
  using RectEnvItem::RectEnvItem;
};

struct Goal : RectEnvItem {
  void interact(Player& player) override {
    player.hasWon = CheckCollisionRecs(player.getBody(), rect);
  }
  using RectEnvItem::RectEnvItem;
};

struct Text : EnvItem {
  const std::string text;
  const int x;
  const int y;
  const int fontSize;
  Text(std::string _text, int _x = 0, int _y = 0, int _fontSize = 100,
       Color _color = BLACK) :
      text(_text),
      x(_x),
      y(_y),
      fontSize(_fontSize),
      EnvItem(_color) {}

  void interact(Player&) override {}
  void draw() override {
    DrawText(text.c_str(), x, y, fontSize, color);
  }
};

#endif
