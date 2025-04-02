#ifndef BASIC_ITEMS_H
#define BASIC_ITEMS_H

#include "PlayerEnvItem.hpp"

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
              rect);
          player.onWallLeft) {
        p.x = rect.x + rect.width + 20;
        if (player.velocity.y < 0 && !player.isWallJumping)
          player.velocity.y = 0;
        player.horizontal = 0;
        player.isWallJumping = false;
      }
    }
    if (!player.onWallRight) {
      if (player.onWallRight = CheckCollisionCircleRec(
              p + Vector2{player.width / 2 - 5, -player.height / 2}, 5, rect);
          player.onWallRight) {
        p.x = rect.x - 20;
        if (player.velocity.y < 0 && !player.isWallJumping)
          player.velocity.y = 0;
        player.horizontal = 0;
        player.isWallJumping = false;
      }
    }
    if (!player.onGround) {
      if (player.onGround =
              CheckCollisionCircleRec(p + Vector2{-5, 0}, 5, rect);
          player.onGround) {
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
      player.stamina = player.max_stamina;
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
      player.stamina = player.max_stamina;
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
