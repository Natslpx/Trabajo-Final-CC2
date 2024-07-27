cmake_minimum_required(VERSION 3.5.0)
set (CMAKE_CXX_STANDARD 23)

project(jueguito VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(RAYLIB_PATH ".." CACHE PATH "Path to the Raylib library")

include_directories(
    ${RAYLIB_PATH}/src
)

if(WIN32)
    add_definitions(-DPLATFORM_DESKTOP)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-missing-braces -Wunused-result")
    set(LIBS ${LIBS} raylib opengl32 gdi32 winmm)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${RAYLIB_PATH}/src/raylib.rc.data -Wl,--subsystem,windows")
elseif(UNIX)
    add_definitions(-DPLATFORM_DESKTOP)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-missing-braces -Wunused-result -D_DEFAULT_SOURCE")
    set(LIBS ${LIBS} raylib GL m pthread dl rt X11 c atomic)
endif()

add_executable(main src/main.cpp)

target_link_libraries(main ${LIBS})

link_directories(
    ${RAYLIB_PATH}/src
)
