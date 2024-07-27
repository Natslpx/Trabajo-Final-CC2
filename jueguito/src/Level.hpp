#include <vector>
#include <memory>
#include <utility>
#include "BasicItems.hpp"

#ifndef LEVEL_H
#define LEVEL_H

typedef std::vector<std::unique_ptr<EnvItem>> Screen;
typedef std::function<Screen(Player&)> ScreenLoader;

class Level {
    std::vector<ScreenLoader> screens;
    int current_screen = -1;

    public:
    Level() {}
    Level(std::vector<ScreenLoader> _screens): screens(_screens) {}

    Screen loadScreen(Player& player) {
        if (current_screen<screens.size()) return screens[current_screen](player);
        else return Screen();
    }

    void next_screen() {
        ++current_screen;
    }

    bool empty() {
        return screens.empty();
    }
};

template<typename T, typename ... Ptrs>
auto make_vector( Ptrs&& ... ptrs ) {
    std::vector<std::unique_ptr<T>> vec;
    ( vec.emplace_back( std::forward<Ptrs>(ptrs) ), ... );
    return vec;
}

Screen loadTestScreen1(Player& player) {
    player.position = {480, 200};
    player.velocity = {0, 0};
    Screen envItems = make_vector<EnvItem>(
        std::make_unique<Block>((Rectangle){ 0, 400, 1000, 200 }, DARKGREEN),
        std::make_unique<Block>((Rectangle){ 100, -600, 300, 1000 }, GRAY),
        std::make_unique<Block>((Rectangle){ 600, -600, 300, 1000 }, GRAY),
        std::make_unique<Jumper>(500, 390),
        std::make_unique<Spikes>((Rectangle){0, 350 ,100, 50}, WHITE),
        std::make_unique<Goal>((Rectangle){900, 350, 100, 50}, GOLD),
        std::make_unique<Gem>(500, -100),
        std::make_unique<Spikes>((Rectangle){-1000, 600 ,3000, 200}, BLACK)
    );
    return envItems;
}

Screen loadTestScreen2(Player& player) {
    player.position = {300, 400};
    Screen envItems = make_vector<EnvItem>(
        std::make_unique<Block>((Rectangle){ 0, 400, 525, 200 }, DARKGREEN),
        std::make_unique<Block>((Rectangle){ 1600, 400, 525, 200 }, DARKGREEN),
        std::make_unique<MoveBlock>((Rectangle){ 100, 800, 300, 100 }, GRAY, (Vector2){0, 1}, [](MoveBlock& mv){return mv.rect.y<1600;}),
        std::make_unique<MoveBlock>((Rectangle){ 600, 800, 300, 100 }, GRAY, (Vector2){1, 0}, [](MoveBlock& mv){return mv.rect.x<1700;}),
        std::make_unique<Block>((Rectangle){ 475, -1000, 50, 1400}, GRAY),
        std::make_unique<Spikes>((Rectangle){0, 350 ,100, 50}, WHITE),
        std::make_unique<Goal>((Rectangle){1775, 350, 100, 50}, GOLD),
        std::make_unique<Spikes>((Rectangle){-1000, 1500 ,3000, 200}, BLACK)
    );
    return envItems;
}

Screen loadTestScreen3(Player& player) {
    player.position = {480, 400};
    Screen envItems = make_vector<EnvItem>(
        std::make_unique<Block>((Rectangle){ 0, 400, 1000, 200 }, DARKGREEN),
        std::make_unique<Gem>(250, 850),
        std::make_unique<Gem>(750, 850),
        std::make_unique<Gem>(1100, 750),
        std::make_unique<Block>((Rectangle){ 475, -1000, 50, 1400}, GRAY),
        std::make_unique<Spikes>((Rectangle){0, 350 ,100, 50}, WHITE),
        std::make_unique<Goal>((Rectangle){900, 350, 100, 50}, GOLD),
        std::make_unique<Spikes>((Rectangle){-1000, 1500 ,3000, 200}, BLACK)
    );
    return envItems;
}

const Level testLevel(std::vector<ScreenLoader>{loadTestScreen1, loadTestScreen2, loadTestScreen3});

#endif