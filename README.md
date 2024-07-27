# Proyecto de Juego en C++

## Descripción

Este proyecto es un juego en 2D desarrollado en C++ utilizando la librería Raylib. El juego presenta múltiples niveles con diferentes desafíos y elementos interactivos para el jugador. Se han aplicado conceptos avanzados de programación como patrones de diseño, punteros inteligentes y multithreading para crear un entorno de juego eficiente y organizado. Este proyecto ha sido realizado como parte del trabajo final para el curso de Ciencia de la Computación 2.

## Funcionalidades

- **Jugador Interactivo**: El jugador puede moverse, saltar, realizar dash y escalar paredes.
- **Elementos del Entorno**:
  - **Bloques**: Plataformas estáticas y móviles.
  - **Pinchos**: Obstáculos que reinician el nivel si el jugador los toca.
  - **Gemas**: Recargan la capacidad de dash del jugador.
  - **Metas**: Objetivos que el jugador debe alcanzar para completar el nivel.
- **Niveles y Pantallas**: Múltiples niveles con pantallas que presentan diferentes desafíos.
- **Cámara Seguimiento**: La cámara sigue al jugador para mantenerlo en el centro de la pantalla.
- **Transiciones entre Pantallas**: El jugador puede moverse entre diferentes pantallas y niveles.

## Uso de Patrones de Diseño

El proyecto implementa varios patrones de diseño para organizar y manejar la lógica del juego:

- **Observer**: Utilizado en las funciones `interact` y `draw` de los elementos del entorno.
- **Decorator**: Añade funcionalidades adicionales a los objetos del juego sin modificar sus estructuras originales.
- **Memento**: Maneja los estados del jugador, permitiendo restaurar su estado al inicio del nivel en caso de muerte.

## Punteros Inteligentes

Se utilizan punteros inteligentes (`std::unique_ptr`) para manejar la memoria de los objetos `EnvItem`. Esto asegura que la memoria se gestione automáticamente, evitando fugas de memoria y facilitando el manejo de la duración de vida de los objetos.

## Multithreading

Se utiliza multithreading para actualizar el estado de cada jugador de forma concurrente, mejorando el rendimiento y la experiencia del juego.

## Estructura del Proyecto

El proyecto está organizado en varios archivos, cada uno con una responsabilidad específica:

- **BasicItems.hpp**: Define los elementos básicos del juego, como el jugador y los diferentes tipos de objetos del entorno.
- **Level.hpp**: Define la estructura de un nivel, incluyendo la gestión de pantallas y la transición entre ellas.
- **Level1.hpp y Level2.hpp**: Contienen la definición específica de las pantallas y los niveles del juego.
- **main.cpp**: Contiene la lógica principal del juego, la inicialización de la ventana, el manejo de eventos y el bucle principal del juego.
- **Vector2.hpp**: Define sobrecargas y funciones auxiliares para el manejo de vectores en 2D.

## Ejecución del Proyecto

### Prerrequisitos

- [Raylib](https://www.raylib.com/)
- Compilador C++ compatible con C++17
- [CMake](https://cmake.org/)

### Compilación y Ejecución

1. Clona el repositorio:

   ```sh
   git clone [https://github.com/Natslpx/Trabajo-Final-CC2]
   cd tu_repositorio
   ```

2. Crea una carpeta para los archivos de compilación:

   ```sh
   mkdir build
   cd build
   ```

3. Genera los archivos de construcción con CMake:

   ```sh
   cmake ..
   ```

4. Compila el proyecto:

   ```sh
   cmake --build .
   ```

5. Ejecuta el juego:

   ```sh
   ./jueguito
   ```
## Licencia

Este proyecto está licenciado bajo la Licencia GPL-3.0. Consulta el archivo [LICENSE](LICENSE) para obtener más detalles.

## Autores

- [Natalie Marleny Lazo Paxi](https://github.com/Natslpx)
- [Alberto Gabriel Torres Ara](https://github.com/All23tor)
- [Anderson Samuel Carpio Chura](https://github.com/AndersonCarpio)
- [Alexandro Ysaac Delgado Justo](https://github.com/adelgadoj)

