cmake_minimum_required(VERSION 3.11.0)
project(jueguito VERSION 1.1)

set (CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) 
if (NOT raylib_FOUND) 
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) 
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) 
  endif()
endif()

add_executable(${PROJECT_NAME} src/main.cpp)
set (source "${CMAKE_SOURCE_DIR}/images")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/images")
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination} 
    DEPENDS ${destination}
    COMMENT "symbolic link resources folder from ${source} => ${destination}"
)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} raylib)
