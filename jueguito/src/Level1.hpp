#include "Level.hpp"

Screen load1_1(Player& player) {
    player.position = {150, 700};
    player.velocity = {0, 0};
    Screen envItems = make_vector<EnvItem>(
        std::make_unique<NonClimbable>(Rectangle{0, -100, 1600, 100}, BLACK),
        std::make_unique<NonClimbable>(Rectangle{0, 900, 1600, 100}, BLACK),
        std::make_unique<NonClimbable>(Rectangle{-100, 0, 100, 900}, BLACK),
        std::make_unique<NonClimbable>(Rectangle{1600, 0, 100, 900}, BLACK),

        std::make_unique<Block>(Rectangle{0, 700, 1600, 200}, BROWN),
        std::make_unique<Block>(Rectangle{500, 500, 1100, 200}, BROWN),
        std::make_unique<Spikes>(Rectangle{800, 475, 200, 25}, WHITE),
        std::make_unique<Spikes>(Rectangle{800, 350, 200, 25}, WHITE),
        std::make_unique<Block>(Rectangle{800, 0, 200, 350}, BROWN),
        std::make_unique<Block>(Rectangle{1550, 0, 50, 300}, BROWN),
        std::make_unique<Block>(Rectangle{1350, 0, 50, 275}, BROWN),
        std::make_unique<Goal>(Rectangle{1400, 0, 150, 30}, GOLD)
    );
    return envItems;
}

Screen load1_2(Player& player) {
    player.position = {450, 800};
    player.velocity = {0, 0};
    Screen envItems = make_vector<EnvItem>(
        std::make_unique<NonClimbable>(Rectangle{0, -100, 1600, 100}, BLACK),
        std::make_unique<NonClimbable>(Rectangle{0, 900, 1600, 100}, BLACK),
        std::make_unique<NonClimbable>(Rectangle{-100, 0, 100, 900}, BLACK),
        std::make_unique<NonClimbable>(Rectangle{1600, 0, 100, 900}, BLACK),

        std::make_unique<Block>(Rectangle{0, 800, 900, 100}, BROWN),
        std::make_unique<Block>(Rectangle{100, 600, 600, 100}, BROWN),
        std::make_unique<Block>(Rectangle{200, 400, 300, 100}, BROWN),

        std::make_unique<Spikes>(Rectangle{900, 870, 400, 30}, WHITE),
        std::make_unique<Block>(Rectangle{1300, 800, 300, 100}, BROWN),
        std::make_unique<Block>(Rectangle{1550, 0, 50, 900}, BROWN),
        std::make_unique<Block>(Rectangle{1400, 0, 50, 700}, BROWN),
        std::make_unique<Goal>(Rectangle{1450, 0, 150, 100}, GOLD)
    );
    return envItems;
}

Screen load1_3(Player& player) {
    player.position = {100, 800};
    player.velocity = {0, 0};
    Screen envItems = make_vector<EnvItem>(
        std::make_unique<NonClimbable>(Rectangle{0, -100, 1600, 100}, BLACK),
        std::make_unique<NonClimbable>(Rectangle{0, 900, 1600, 100}, BLACK),
        std::make_unique<NonClimbable>(Rectangle{-100, 0, 100, 900}, BLACK),
        std::make_unique<NonClimbable>(Rectangle{1600, 0, 100, 900}, BLACK),

        std::make_unique<Block>(Rectangle{0, 850, 100, 50}, BROWN),
        std::make_unique<Block>(Rectangle{300, 550, 80, 50}, BROWN),
        std::make_unique<Block>(Rectangle{0, 250, 100, 50}, BROWN),
        std::make_unique<MoveBlock>(Rectangle{900, 250, 200, 50}, BROWN, Vector2{1, 1}, [](MoveBlock& mv){return mv.rect.x<1000;}),
        std::make_unique<Gem>(Vector2{400, 100}),
        std::make_unique<Goal>(Rectangle{1400, 870, 150, 30}, GOLD)
    );
    return envItems;
}

const Level level1(std::vector<ScreenLoader>{load1_1, load1_2, load1_3});
