#ifndef LEVEL_3_HPP
#define LEVEL_3_HPP

#include "BasicItems.hpp"
#include "Level.hpp"

namespace {
Screen load3_1(Player& player) {
  player.position = {480, 200};
  player.velocity = {0, 0};
  return make_screen<EnvItem>(
      Block((Rectangle){0, 400, 1000, 200}, DARKGREEN),
      Block((Rectangle){100, -600, 300, 1000}, GRAY),
      Block((Rectangle){600, -600, 300, 1000}, GRAY), Jumper(500, 390),
      Spikes((Rectangle){0, 350, 100, 50}, WHITE),
      Goal((Rectangle){900, 350, 100, 50}, GOLD), Gem(500, -100),
      Spikes((Rectangle){-1000, 600, 3000, 200}, BLACK));
}

Screen load3_2(Player& player) {
  player.position = {300, 400};
  return make_screen<EnvItem>(
      Block((Rectangle){0, 400, 525, 200}, DARKGREEN),
      Block((Rectangle){1600, 400, 525, 200}, DARKGREEN),
      MoveBlock((Rectangle){100, 800, 300, 100}, GRAY, (Vector2){0, 1},
                [](const MoveBlock& mv) {
                  return mv.rect.y < 1600;
                }),
      MoveBlock((Rectangle){600, 800, 300, 100}, GRAY, (Vector2){1, 0},
                [](const MoveBlock& mv) {
                  return mv.rect.x < 1700;
                }),
      Block((Rectangle){475, -1000, 50, 1400}, GRAY),
      Spikes((Rectangle){0, 350, 100, 50}, WHITE),
      Goal((Rectangle){1775, 350, 100, 50}, GOLD),
      Spikes((Rectangle){-1000, 1500, 3000, 200}, BLACK));
}

Screen load3_3(Player& player) {
  player.position = {480, 400};
  return make_screen<EnvItem>(
      Block((Rectangle){0, 400, 1000, 200}, DARKGREEN), Gem(250, 850),
      Gem(750, 850), Gem(1100, 750),
      Block((Rectangle){475, -1000, 50, 1400}, GRAY),
      Spikes((Rectangle){0, 350, 100, 50}, WHITE),
      Goal((Rectangle){900, 350, 100, 50}, GOLD),
      Spikes((Rectangle){-1000, 1500, 3000, 200}, BLACK));
}
} // namespace

inline const Level level3({load3_1, load3_2, load3_3});

#endif // !LEVEL_3_HPP
