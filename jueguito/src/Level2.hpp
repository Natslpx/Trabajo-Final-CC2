#include "Level.hpp"

Screen load2_1(Player& player) {
    player.position = {150, 800};  // Posición inicial del jugador
    player.velocity = {0, 0};

    Screen envItems = make_vector<EnvItem>(
        // Límites del mapa
        std::make_unique<NonClimbable>(Rectangle{0, -100, 1700, 100}, BLACK),
        std::make_unique<NonClimbable>(Rectangle{0, 900, 1700, 100}, BLACK),
        std::make_unique<NonClimbable>(Rectangle{-100, 0, 100, 900}, BLACK),
        std::make_unique<NonClimbable>(Rectangle{1700, 0, 100, 900}, BLACK),

        // Bloques de inicio para escalar
        std::make_unique<Block>(Rectangle{0, 100, 50, 800}, BROWN),
        std::make_unique<Block>(Rectangle{250, 100, 50, 800}, BROWN),

        // Gem para recargar dash
        std::make_unique<Gem>(150, 400),

        // Primera plataforma de descanso
        std::make_unique<Block>(Rectangle{400, 600, 100, 50}, BROWN),

        // Primera plataforma que se mueve
        std::make_unique<MoveBlock>(Rectangle{400, 150, 100, 50}, BLUE, Vector2{1, 0}, [](MoveBlock& mv){return mv.rect.x < 600;}),

        // Plataforma móvil horizontal
        std::make_unique<MoveBlock>(Rectangle{650, 700, 100, 50}, BLUE, Vector2{1, 0}, [](MoveBlock& mv){return mv.rect.x < 900;}),

        // Segunda plataforma fija
        std::make_unique<Block>(Rectangle{900, 550, 200, 50}, BROWN),

        // Tercera plataforma fija
        std::make_unique<Block>(Rectangle{900, 100, 200, 50}, BROWN),

        // Bloque alto vertical para escalar
        std::make_unique<Block>(Rectangle{1150, 300, 50, 350}, BROWN),

        // Plataforma con pinchos debajo del bloque alto
        std::make_unique<Spikes>(Rectangle{900, 650, 300, 50}, WHITE),

        // Pinchos en el suelo
        std::make_unique<Spikes>(Rectangle{300, 850, 700, 50}, WHITE),
        std::make_unique<Spikes>(Rectangle{1200, 850, 500, 50}, WHITE),

        // Pared no escalable en la parte superior
        std::make_unique<NonClimbable>(Rectangle{1000, 700, 200, 200}, BLACK),

        // Plataforma móvil diagonal (hacia abajo y a la derecha)
        std::make_unique<MoveBlock>(Rectangle{1350, 550, 100, 50}, BLUE, Vector2{1, 1}, [](MoveBlock& mv){return mv.rect.y < 700 && mv.rect.x < 1500;}),

        // Plataforma alta con pinchos debajo
        std::make_unique<Block>(Rectangle{1350, 300, 200, 50}, BROWN),
        std::make_unique<Spikes>(Rectangle{1350, 350, 200, 50}, WHITE),

        // Pared vertical no escalable
        std::make_unique<NonClimbable>(Rectangle{1500, 0, 50, 600}, BLACK),

        // Plataforma final
        std::make_unique<Block>(Rectangle{1600, 400, 100, 50}, BROWN),

        // Goal en una plataforma accesible
        std::make_unique<Goal>(Rectangle{1650, 350, 50, 50}, GOLD)
    );

    return envItems;
}

Screen load2_2(Player& player) {
    player.position = {100, 800};  // Posición inicial del jugador
    player.velocity = {0, 0};

    Screen envItems = make_vector<EnvItem>(
        // Límites del mapa
        std::make_unique<NonClimbable>(Rectangle{0, -100, 1700, 100}, BLACK),
        std::make_unique<NonClimbable>(Rectangle{0, 900, 1700, 100}, BLACK),
        std::make_unique<NonClimbable>(Rectangle{-100, 0, 100, 900}, BLACK),
        std::make_unique<NonClimbable>(Rectangle{1700, 0, 100, 900}, BLACK),

        // Bloque 1
        std::make_unique<Block>(Rectangle{100, 700, 200, 300}, BROWN),

        // Bloque 2
        std::make_unique<Block>(Rectangle{0, 0, 400, 600}, BROWN),

        // Bloque 3
        std::make_unique<MoveBlock>(Rectangle{470, 700, 50, 50}, BLUE, Vector2{0, -1}, [](MoveBlock& mv){return mv.rect.y > 400;}),

        // Pinchos 1
        std::make_unique<Spikes>(Rectangle{300, 850, 290, 50}, WHITE),

        // Bloque 4
        std::make_unique<Block>(Rectangle{590, 270, 90, 630}, BROWN),

        // Bloque 5
        std::make_unique<Block>(Rectangle{680, 850, 120, 50}, BROWN),
        std::make_unique<Spikes>(Rectangle{680, 800, 120, 50}, WHITE),

        // Pinchos 2
        std::make_unique<Spikes>(Rectangle{800, 850, 250, 50}, WHITE),

        // Bloque 6
        std::make_unique<Block>(Rectangle{1050, 850, 150, 50}, BROWN),
        std::make_unique<Spikes>(Rectangle{1050, 800, 150, 50}, WHITE),

        // Bloque 7
        std::make_unique<Block>(Rectangle{1200, 800, 250, 50}, BROWN),
        std::make_unique<Spikes>(Rectangle{1200, 750, 250, 50}, WHITE),

        // Bloque 8
        std::make_unique<NonClimbable>(Rectangle{1450, 600, 250, 300}, BLACK),

        // Bloque 9
        std::make_unique<Block>(Rectangle{1350, 400, 350, 200}, BROWN),

        // Bloque 10
        std::make_unique<Block>(Rectangle{1430, 300, 270, 100}, BROWN),

        // Bloque 11
        std::make_unique<Block>(Rectangle{950, 250, 50, 200}, BROWN),
        std::make_unique<Block>(Rectangle{1000, 250, 150, 50}, BROWN),
        std::make_unique<Block>(Rectangle{1100, 200, 200, 50}, BROWN),
        std::make_unique<Spikes>(Rectangle{950, 200, 200, 50}, WHITE),
        std::make_unique<Spikes>(Rectangle{1100, 150, 200, 50}, WHITE),

        // Gem para recargar dash
        std::make_unique<Gem>(800, 300),

        // Bloque móvil
        std::make_unique<MoveBlock>(Rectangle{1020, 670, 100, 50}, BLUE, Vector2{1, -1}, [](MoveBlock& mv){return mv.rect.y > 400 && mv.rect.x < 1200;}),

        //Goal
        std::make_unique<Goal>(Rectangle{1650, 250, 50, 50}, GOLD)
    );

    return envItems;
    
}

Screen load2_3(Player& player) {
    player.position = {400, 350};  // Posición inicial del jugador
    player.velocity = {0, 0};

    Screen envItems = make_vector<EnvItem>(
        // Límites del mapa
        std::make_unique<NonClimbable>(Rectangle{0, -100, 1700, 100}, BLACK),
        std::make_unique<NonClimbable>(Rectangle{0, 900, 1700, 100}, BLACK),
        std::make_unique<NonClimbable>(Rectangle{-100, 0, 100, 900}, BLACK),
        std::make_unique<NonClimbable>(Rectangle{1700, 0, 100, 900}, BLACK),

        // Bloques
        std::make_unique<Block>(Rectangle{0, 0, 50, 650}, BROWN),
        std::make_unique<Block>(Rectangle{300, 250, 150, 550}, BROWN),
        std::make_unique<Block>(Rectangle{450, 250, 450, 100}, BROWN),
        std::make_unique<Block>(Rectangle{700, 350, 200, 200}, BROWN),
        std::make_unique<Block>(Rectangle{900, 250, 50, 650}, BROWN),

        // Bloque 6
        std::make_unique<Block>(Rectangle{450, 450, 150, 50}, BROWN),
        std::make_unique<Block>(Rectangle{550, 500, 50, 150}, BROWN),
        std::make_unique<Block>(Rectangle{550, 600, 200, 50}, BROWN),
        std::make_unique<Block>(Rectangle{700, 650, 50, 150}, BROWN),

        // No escalable
        std::make_unique<NonClimbable>(Rectangle{300, 850, 600, 50}, BLACK),

        // Bloque móvil 
        std::make_unique<MoveBlock>(Rectangle{300, 800, 150, 50}, BLUE, Vector2{-1, 0}, [](MoveBlock& mv){return mv.rect.x > 50;}),

        // Gem para recargar dash
        std::make_unique<Gem>(150, 500),
        
        // SPIKES
        std::make_unique<Spikes>(Rectangle{950, 850, 300, 50}, WHITE),
        
        // No escalable
        std::make_unique<NonClimbable>(Rectangle{1250, 0, 150, 680}, BLACK),

        // Bloques
        std::make_unique<Block>(Rectangle{1650, 700, 50, 50}, BROWN),
        std::make_unique<Block>(Rectangle{1400, 450, 50, 50}, BROWN),
        std::make_unique<Block>(Rectangle{1650, 320, 50, 50}, BROWN),
        std::make_unique<Block>(Rectangle{1400, 160, 100, 50}, BROWN),

        // Goal en una plataforma accesible
        std::make_unique<Goal>(Rectangle{1400, 110, 50, 50}, GOLD)
    );

    return envItems;
}

const Level level2(std::vector<ScreenLoader>{load2_1, load2_2, load2_3});