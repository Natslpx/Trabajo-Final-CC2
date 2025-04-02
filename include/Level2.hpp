#include "Level.hpp"

#ifndef LEVEL_3_HPP
#define LEVEL_3_HPP

namespace {
Screen load2_1(Player& player) {
  player.position = {150, 800};
  player.velocity = {0, 0};

  return make_screen<EnvItem>(
      NonClimbable(Rectangle{0, -100, 1700, 100}, BLACK),
      NonClimbable(Rectangle{0, 900, 1700, 100}, BLACK),
      NonClimbable(Rectangle{-100, 0, 100, 900}, BLACK),
      NonClimbable(Rectangle{1700, 0, 100, 900}, BLACK),
      Block(Rectangle{0, 100, 50, 800}, BROWN),
      Block(Rectangle{250, 100, 50, 800}, BROWN), Gem(150, 400),
      Block(Rectangle{400, 600, 100, 50}, BROWN),
      MoveBlock(Rectangle{400, 150, 100, 50}, BLUE, Vector2{1, 0},
                [](MoveBlock& mv) {
                  return mv.rect.x < 600;
                }),
      MoveBlock(Rectangle{650, 700, 100, 50}, BLUE, Vector2{1, 0},
                [](MoveBlock& mv) {
                  return mv.rect.x < 900;
                }),
      Block(Rectangle{900, 550, 200, 50}, BROWN),
      Block(Rectangle{900, 100, 200, 50}, BROWN),
      Block(Rectangle{1150, 300, 50, 350}, BROWN),
      Spikes(Rectangle{900, 650, 300, 50}, WHITE),
      Spikes(Rectangle{300, 850, 700, 50}, WHITE),
      Spikes(Rectangle{1200, 850, 500, 50}, WHITE),
      NonClimbable(Rectangle{1000, 700, 200, 200}, BLACK),
      MoveBlock(Rectangle{1350, 550, 100, 50}, BLUE, Vector2{1, 1},
                [](MoveBlock& mv) {
                  return mv.rect.y < 700 && mv.rect.x < 1500;
                }),
      Block(Rectangle{1350, 300, 200, 50}, BROWN),
      Spikes(Rectangle{1350, 350, 200, 50}, WHITE),
      NonClimbable(Rectangle{1500, 0, 50, 600}, BLACK),
      Block(Rectangle{1600, 400, 100, 50}, BROWN),
      Goal(Rectangle{1650, 350, 50, 50}, GOLD));
}

Screen load2_2(Player& player) {
  player.position = {100, 800};
  player.velocity = {0, 0};

  return make_screen<EnvItem>(
      NonClimbable(Rectangle{0, -100, 1700, 100}, BLACK),
      NonClimbable(Rectangle{0, 900, 1700, 100}, BLACK),
      NonClimbable(Rectangle{-100, 0, 100, 900}, BLACK),
      NonClimbable(Rectangle{1700, 0, 100, 900}, BLACK),
      Block(Rectangle{100, 700, 200, 300}, BROWN),
      Block(Rectangle{0, 0, 400, 600}, BROWN),
      MoveBlock(Rectangle{470, 700, 50, 50}, BLUE, Vector2{0, -1},
                [](MoveBlock& mv) {
                  return mv.rect.y > 400;
                }),
      Spikes(Rectangle{300, 850, 290, 50}, WHITE),
      Block(Rectangle{590, 270, 90, 630}, BROWN),
      Block(Rectangle{680, 850, 120, 50}, BROWN),
      Spikes(Rectangle{680, 800, 120, 50}, WHITE),
      Spikes(Rectangle{800, 850, 250, 50}, WHITE),
      Block(Rectangle{1050, 850, 150, 50}, BROWN),
      Spikes(Rectangle{1050, 800, 150, 50}, WHITE),
      Block(Rectangle{1200, 800, 250, 50}, BROWN),
      Spikes(Rectangle{1200, 750, 250, 50}, WHITE),
      NonClimbable(Rectangle{1450, 600, 250, 300}, BLACK),
      Block(Rectangle{1350, 400, 350, 200}, BROWN),
      Block(Rectangle{1430, 300, 270, 100}, BROWN),
      Block(Rectangle{950, 250, 50, 200}, BROWN),
      Block(Rectangle{1000, 250, 150, 50}, BROWN),
      Block(Rectangle{1100, 200, 200, 50}, BROWN),
      Spikes(Rectangle{950, 200, 200, 50}, WHITE),
      Spikes(Rectangle{1100, 150, 200, 50}, WHITE), Gem(800, 300),
      MoveBlock(Rectangle{1020, 670, 100, 50}, BLUE, Vector2{1, -1},
                [](MoveBlock& mv) {
                  return mv.rect.y > 400 && mv.rect.x < 1200;
                }),
      Goal(Rectangle{1650, 250, 50, 50}, GOLD));
}

Screen load2_3(Player& player) {
  player.position = {400, 350};
  player.velocity = {0, 0};

  return make_screen<EnvItem>(
      NonClimbable(Rectangle{0, -100, 1700, 100}, BLACK),
      NonClimbable(Rectangle{0, 900, 1700, 100}, BLACK),
      NonClimbable(Rectangle{-100, 0, 100, 900}, BLACK),
      NonClimbable(Rectangle{1700, 0, 100, 900}, BLACK),
      Block(Rectangle{0, 0, 50, 650}, BROWN),
      Block(Rectangle{300, 250, 150, 550}, BROWN),
      Block(Rectangle{450, 250, 450, 100}, BROWN),
      Block(Rectangle{700, 350, 200, 200}, BROWN),
      Block(Rectangle{900, 250, 50, 650}, BROWN),
      Block(Rectangle{450, 450, 150, 50}, BROWN),
      Block(Rectangle{550, 500, 50, 150}, BROWN),
      Block(Rectangle{550, 600, 200, 50}, BROWN),
      Block(Rectangle{700, 650, 50, 150}, BROWN),
      NonClimbable(Rectangle{300, 850, 600, 50}, BLACK),
      MoveBlock(Rectangle{300, 800, 150, 50}, BLUE, Vector2{-1, 0},
                [](MoveBlock& mv) {
                  return mv.rect.x > 50;
                }),
      Gem(150, 500), Spikes(Rectangle{950, 850, 300, 50}, WHITE),
      NonClimbable(Rectangle{1250, 0, 150, 680}, BLACK),
      Block(Rectangle{1650, 700, 50, 50}, BROWN),
      Block(Rectangle{1400, 450, 50, 50}, BROWN),
      Block(Rectangle{1650, 320, 50, 50}, BROWN),
      Block(Rectangle{1400, 160, 100, 50}, BROWN),
      Goal(Rectangle{1400, 110, 50, 50}, GOLD));
}
} // namespace

inline const Level level2({load2_1, load2_2, load2_3});

#endif
