cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(jueguito)

# Versión de C++
set(CMAKE_CXX_STANDARD 17)

# Incluir los directorios de encabezados
include_directories(include)

# Archivos fuente
set(SOURCES
    jueguito/src/main.cpp
    jueguito/src/BasicItems.hpp
    jueguito/src/Level.hpp
    jueguito/src/Vector2.hpp
)

# Añadir el ejecutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Enlazar raylib
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
