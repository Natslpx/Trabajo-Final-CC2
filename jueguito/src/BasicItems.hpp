#include "raylib.h"
#include "raymath.h"
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <functional>

#include "Vector2.hpp"
struct Player;

struct EnvItem {
    Color color;

    EnvItem() {}
    EnvItem(Color _color): color(_color) {}
    virtual void interact(Player &player) =0;
    virtual void draw() =0;
};

struct RectEnvItem : EnvItem {
    Rectangle rect;

    RectEnvItem(Rectangle _rect, Color _color): rect(_rect), EnvItem(_color) {}
    void draw() override {
        DrawRectangleRec(rect, color);
    }
};

struct Player {
    const float gravity = 2450.0f;
    const float walkSpeed = 500.0f;
    const float jumpSpeed = 860.0f;
    const float dashSpeed = 1230.0f;
    const float climbSpeed = 250.0f;
    const int MAX_STAMINA = 110;

    Vector2 position = {0,0};
    Vector2 velocity = {0,0};

    float width;
    float height;

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
    
    bool isDead = false;
    bool hasWon = false;

    float horizontal = 0;
    float vertical = 0;

    float getHorizontal() {
        if (IsKeyDown(KEY_LEFT)) {
            horizontal-=0.05;
        } else if (IsKeyDown(KEY_RIGHT)) {
            horizontal+=0.05;
        } else if (horizontal > 0) {
            horizontal-=0.05;
        } else if (horizontal < 0) {
            horizontal+=0.05;
        }

        if (horizontal>1.0f) {
            horizontal = 1.0f;
        } else if (horizontal<-1.0f) {
            horizontal = -1.0f;
        } else if (abs(horizontal)<0.01) {
            horizontal = 0;
        }

        return horizontal;
    }
    float getVertical() {
        if (IsKeyDown(KEY_UP)) {
            vertical-=0.05;
        } else if (IsKeyDown(KEY_DOWN)) {
            vertical+=0.05;
        } else if (vertical>0) {
            vertical-=0.05;
        } else if (vertical<0) {
            vertical+=0.05;
        }

        if (vertical>1.0f) {
            vertical = 1.0f;
        } else if (vertical<-1.0f) {
            vertical = -1.0f;
        } else if (abs(vertical)<0.01) {
            vertical = 0;
        }

        return vertical;
    }

    float rawHorizontal() {
        if (IsKeyDown(KEY_LEFT)) return -1;
        if (IsKeyDown(KEY_RIGHT)) return 1;
        return 0;
    }

    float rawVertical() {
        if (IsKeyDown(KEY_UP)) return -1;
        if (IsKeyDown(KEY_DOWN)) return 1;
        return 0;
    }

    Rectangle getBody() const {
        return (Rectangle){ position.x - width/2, position.y - height, width, height };
    }

    void draw() const {
        Rectangle playerRect = getBody();
        Color dash_color = canDash ? RED : BLUE;
        DrawRectangleRec(playerRect, stamina < 20 ? DARKPURPLE : DARKBLUE);
        DrawRectangleRec((Rectangle){position.x - width/2, position.y - height, width, height/5}, dash_color);
        DrawCircleV(position, 5.0f, onGround ? GREEN : GOLD);
        DrawCircleV(position + (Vector2){-width/2, -height/2} , 5.0f, onWallLeft ? GREEN : GOLD);
        DrawCircleV(position + (Vector2){width/2, -height/2} , 5.0f, onWallRight ? GREEN : GOLD);
    }

    void update(std::vector<std::unique_ptr<EnvItem>> &envItems, float delta) {
        if (isDashing) isDashing--;
        if (isWallJumping) isWallJumping--;
        
        onGround = onWallLeft = onWallRight = false; //Colisiones
        for (std::unique_ptr<EnvItem> &ei : envItems) ei->interact(*this);

        float x = getHorizontal();
        float y = getVertical();

        if (!isGrabbing && !isDashing) { //Caminar
            if (abs(x) > 0.01f) {
                velocity.x = x * walkSpeed;
            } else {
                velocity.x *= 0.9; 
            }
        }

        if (IsKeyPressed(KEY_C) && canJump) { //Salto
            velocity.y = -jumpSpeed;
            canJump = false;
            hasJumped = true;
            onGround = false;
        } else if (IsKeyPressed(KEY_C) && !isDashing && (onWallLeft || onWallRight)) { //Wall Jump
            velocity.y = -jumpSpeed;
            velocity.x = onWallLeft ? walkSpeed : -walkSpeed;
            canJump = false;
            isWallJumping = true;
            hasJumped = true;
            stamina -= 27.5;
        }

        if (IsKeyPressed(KEY_X) && canDash && !isDashing) { //Dash
            if (rawHorizontal()!=0|| rawVertical()!=0) {
                velocity = normalized((Vector2){rawHorizontal(), rawVertical()}) * dashSpeed;
                canDash = false;
                isDashing = 14;
                onGround = false;
                hasJumped = false;
            }
        }

        if ((!onWallLeft || velocity.x >= 0) && (!onWallRight || velocity.x <= 0)) { //Movimiento horizontal
            position.x += velocity.x * delta;
        } else {
            velocity.x = 0;
        }

        isGrabbing = false;
        if (!onGround) { //Movimiento vertical aéreo
            if ((onWallLeft || onWallRight) && (IsKeyDown(KEY_V) || IsKeyDown(KEY_Z)) && !isWallJumping && stamina>0) { //Climb
                isGrabbing = true;
                if (rawVertical()!=0) {
                    velocity.y = rawVertical() * climbSpeed;
                    stamina -= 45.45 * delta;
                } else {
                    stamina -= 10 * delta;
                    velocity.y = 0;
                }
            } else if (!IsKeyDown(KEY_C) && velocity.y < 0 && hasJumped) { //Salto corto
                velocity.y += 1.75f*gravity*delta;
            } else if (!isDashing) { //Salto completo || Caída normal
                velocity.y += gravity*delta;
            } else {
                velocity.y *= 0.94; //Gravedad de dash
            }
            canJump = false;
            position.y += velocity.y*delta;
        } else { //Movimiento vertical a tierra
            if (velocity.y < 0) {
                position.y += velocity.y * delta; //MOvimiento hacia arriba
            } else {
                velocity.y = 0;
            }
            canDash = true;
            canJump = true;
            hasJumped = false;
            stamina = MAX_STAMINA;
        }
    }
};

struct NonInteractable : RectEnvItem {
    void interact(Player &player) override {}
    using RectEnvItem::RectEnvItem;
};

struct Block : RectEnvItem {
    void interact(Player &player) override {
        Vector2 &p = player.position;
        
        if (!player.onWallLeft) {if (player.onWallLeft = CheckCollisionCircleRec(p + (Vector2){-(player.width/2 - 5), -player.height/2}, 5, rect)) {
            p.x = rect.x + rect.width + 20;
            if (player.velocity.y <0 && !player.isWallJumping) player.velocity.y = 0;
            player.horizontal = 0;
            player.isWallJumping = false;
        }}
        if (!player.onWallRight) {if (player.onWallRight = CheckCollisionCircleRec(p + (Vector2){player.width/2 - 5, -player.height/2}, 5, rect)) {
            p.x = rect.x - 20;
            if (player.velocity.y <0 && !player.isWallJumping) player.velocity.y = 0;
            player.horizontal = 0;
            player.isWallJumping = false;
        }}
        if (!player.onGround) {if (player.onGround = CheckCollisionCircleRec(p + (Vector2){-5, 0}, 5, rect)) {
            player.position.y = rect.y;
        }}

        if (CheckCollisionCircleRec(p + (Vector2){-5, -player.height}, 5, rect)) {
            player.position.y = rect.y + rect.height + player.height;
        }
    }
    using RectEnvItem::RectEnvItem;
};

struct MoveBlock : Block {
    bool fall;
    int timer; 
    std::function<bool(MoveBlock&)> condition;

    const float displacement = 5;
    const Vector2 direction;
    void interact(Player &player) override {
        short old_state = player.onGround + player.onWallLeft * 2 + player.onWallRight * 4;
        Block::interact(player);
        short new_state = player.onGround + player.onWallLeft * 2 + player.onWallRight * 4;
        if (old_state != new_state) {
            if (!fall) {
                fall = true;
                timer = 10;
                color = RED;
            } else if (condition(*this)) {
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

    MoveBlock(Rectangle _rect, Color _color, Vector2 _direction, bool (*_condition)(MoveBlock&)) : fall(false), Block(_rect, _color), direction(normalized(_direction)), condition(_condition) {}

};

struct Jumper : RectEnvItem {
    void interact(Player &player) override {
        if (CheckCollisionRecs(player.getBody(), rect)) {
            player.position.y -= 10;
            player.velocity.y -= player.dashSpeed ;
            player.velocity.x = 0;
            //player.position.x = rect.x + rect.width/2; //Center player on jumper
            player.canDash = true;
            player.canJump = false;
            player.stamina = player.MAX_STAMINA;
        }
    }

    Jumper(float x, float y): RectEnvItem((Rectangle){x - 30, y - 5, 60, 15}, BROWN) {}
};

struct Gem : EnvItem {
    bool active;
    int timer;
    Vector2 center;
    void interact(Player &player) override {
        if (CheckCollisionCircleRec((Vector2){center.x, center.y}, 30, player.getBody()) && !timer && !player.canDash) {
            player.canDash = true;
            player.stamina = player.MAX_STAMINA;
            timer = 150;
            color = GRAY;
            BeginDrawing();
            draw();
            WaitTime(0.5f);
            EndDrawing();
            GetFrameTime();
        }
    }

    Gem(float x, float y): timer(0) {
        center = {x, y};
        color = GREEN;
    }

    void draw() override {
        DrawCircle(center.x, center.y, 30, color);
        if (timer!=0) {
            if (!--timer) {
                color = GREEN;
            }
        }
    }
};

struct Spikes : RectEnvItem {
    void interact(Player &player) override { player.isDead = player.isDead || CheckCollisionRecs(player.getBody(), rect);}
    using RectEnvItem::RectEnvItem;
};

struct Goal : RectEnvItem {
    void interact(Player &player) override { player.hasWon = CheckCollisionRecs(player.getBody(), rect);}
    using RectEnvItem::RectEnvItem;
};

struct Text : EnvItem {
    const std::string text;
    const int x;
    const int y;
    const int fontSize;
    const Color color;
    Text(std::string _text, int _x=0, int _y=0, int _fontSize = 100, Color _color = BLACK) : text(_text), x(_x), y(_y), fontSize(_fontSize), color(_color) {}

    void interact(Player&) override {}
    void draw() override {
        DrawText(text.data(), x, y, fontSize, color);
    }
};
