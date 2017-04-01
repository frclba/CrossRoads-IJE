cmake_minimum_required (VERSION 2.6)
project (tutorial)

file(GLOB_RECURSE SRC
    "src/*.cpp"
    "libs/*.c"
    )

file(GLOB_RECURSE HEADERS
    "include/*.h"
    #"libs/*.h"
    )


add_executable(my_exec ${SRC} ${HEADERS})

target_compile_options(my_exec PUBLIC -std=c++1y -lSDL2 -lSDL2_image -lSDL2_ttf)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(my_exec ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} )

