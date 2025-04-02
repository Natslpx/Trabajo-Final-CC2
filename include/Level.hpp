#ifndef LEVEL_H
#define LEVEL_H

#include "PlayerEnvItem.hpp"
#include <memory>
#include <vector>

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

template <typename T, typename... Args>
inline auto make_vector(Args&&... args) {
  std::vector<T> vec;
  (vec.emplace_back(std::forward<Args>(args)), ...);
  return vec;
}

template <typename Base, typename... Derived>
requires(std::is_convertible_v<Derived*, Base*> && ...)
inline auto make_screen(Derived&&... ptrs) {
  return make_vector<std::unique_ptr<Base>>(std::make_unique<Derived>(ptrs)...);
}

#endif
