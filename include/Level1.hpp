#ifndef LEVEL_1_HPP
#define LEVEL_1_HPP

#include "BasicItems.hpp"
#include "Level.hpp"

namespace {
Screen load1_1(Player& player) {
  player.position = {150, 700};
  player.velocity = {0, 0};
  return make_screen<EnvItem>(
      NonClimbable(Rectangle{0, -100, 1600, 100}, BLACK),
      NonClimbable(Rectangle{0, 900, 1600, 100}, BLACK),
      NonClimbable(Rectangle{-100, 0, 100, 900}, BLACK),
      NonClimbable(Rectangle{1600, 0, 100, 900}, BLACK),
      Block(Rectangle{0, 700, 1600, 200}, BROWN),
      Block(Rectangle{500, 500, 1100, 200}, BROWN),
      Spikes(Rectangle{800, 475, 200, 25}, WHITE),
      Spikes(Rectangle{800, 350, 200, 25}, WHITE),
      Block(Rectangle{800, 0, 200, 350}, BROWN),
      Block(Rectangle{1550, 0, 50, 300}, BROWN),
      Block(Rectangle{1350, 0, 50, 275}, BROWN),
      Goal(Rectangle{1400, 0, 150, 30}, GOLD));
}

Screen load1_2(Player& player) {
  player.position = {450, 800};
  player.velocity = {0, 0};
  return make_screen<EnvItem>(
      NonClimbable(Rectangle{0, -100, 1600, 100}, BLACK),
      NonClimbable(Rectangle{0, 900, 1600, 100}, BLACK),
      NonClimbable(Rectangle{-100, 0, 100, 900}, BLACK),
      NonClimbable(Rectangle{1600, 0, 100, 900}, BLACK),
      Block(Rectangle{0, 800, 900, 100}, BROWN),
      Block(Rectangle{100, 600, 600, 100}, BROWN),
      Block(Rectangle{200, 400, 300, 100}, BROWN),
      Spikes(Rectangle{900, 870, 400, 30}, WHITE),
      Block(Rectangle{1300, 800, 300, 100}, BROWN),
      Block(Rectangle{1550, 0, 50, 900}, BROWN),
      Block(Rectangle{1400, 0, 50, 700}, BROWN),
      Goal(Rectangle{1450, 0, 150, 100}, GOLD)

  );
}

Screen load1_3(Player& player) {
  player.position = {100, 800};
  player.velocity = {0, 0};
  return make_screen<EnvItem>(
      NonClimbable(Rectangle{0, -100, 1600, 100}, BLACK),
      NonClimbable(Rectangle{0, 900, 1600, 100}, BLACK),
      NonClimbable(Rectangle{-100, 0, 100, 900}, BLACK),
      NonClimbable(Rectangle{1600, 0, 100, 900}, BLACK),
      Block(Rectangle{0, 850, 100, 50}, BROWN),
      Block(Rectangle{300, 550, 80, 50}, BROWN),
      Block(Rectangle{0, 250, 100, 50}, BROWN),
      MoveBlock(Rectangle{900, 250, 200, 50}, BROWN, Vector2{1, 1},
                [](MoveBlock& mv) {
                  return mv.rect.x < 1000;
                }),
      Gem(Vector2{400, 100}), Goal(Rectangle{1400, 870, 150, 30}, GOLD));
}
} // namespace

inline const Level level1({load1_1, load1_2, load1_3});

#endif
