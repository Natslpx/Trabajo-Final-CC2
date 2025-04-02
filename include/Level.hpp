#include "BasicItems.hpp"
#include <memory>
#include <utility>
#include <vector>

#ifndef LEVEL_H
#define LEVEL_H

using Screen = std::vector<std::unique_ptr<EnvItem>>;
using ScreenLoader = Screen (*)(Player&);

class Level {
  std::vector<ScreenLoader> screens;
  int current_screen = -1;

public:
  Level() {}
  Level(std::vector<ScreenLoader> _screens) : screens(_screens) {}

  Screen loadScreen(Player& player) const {
    if (current_screen < screens.size())
      return screens[current_screen](player);
    else
      return Screen();
  }

  void next_screen() {
    ++current_screen;
  }

  bool empty() const {
    return screens.empty();
  }
};

template <typename Base, typename... Derived>
requires(std::is_convertible_v<Derived*, Base*> && ...)
inline auto make_screen(Derived&&... ptrs) {
  std::vector<std::unique_ptr<Base>> vec;
  (vec.push_back(std::make_unique<Derived>(std::move(ptrs))), ...);
  return vec;
}

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
                [](MoveBlock& mv) {
                  return mv.rect.y < 1600;
                }),
      MoveBlock((Rectangle){600, 800, 300, 100}, GRAY, (Vector2){1, 0},
                [](MoveBlock& mv) {
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

#endif
