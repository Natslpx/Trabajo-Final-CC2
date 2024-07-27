cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(jueguito)

# Versión de C++
set(CMAKE_CXX_STANDARD 17)

# Añadir el directorio de encabezados
include_directories(include)

# Archivos fuente
set(SOURCES
    jueguito/src/main.cpp
    jueguito/src/BasicItems.hpp
    jueguito/src/Level.hpp
    jueguito/src/Level1.hpp
    jueguito/src/Level2.hpp
    jueguito/src/Vector2.hpp
)

# Añadir el ejecutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Enlazar raylib (asegúrate de tener raylib instalado y disponible)
find_package(raylib REQUIRED)

# Incluir los directorios de encabezados de Raylib
include_directories(${RAYLIB_INCLUDE_DIRS})

# Enlazar las bibliotecas de Raylib
target_link_libraries(${PROJECT_NAME} raylib)
