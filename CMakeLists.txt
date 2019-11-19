cmake_minimum_required(VERSION 3.14)
project(vis_lem_in C)

set(CMAKE_C_STANDARD 11)

include_directories(
        .
        ./include
        ./libft/includes
)


add_executable(
        vis_lem_in
        vis_lemin.c
        print_error.c
        init_sdl.c
        load_image.c
        load_font.c
        vis_lemin.h
        read_file.c
        links_parse.c
        line_parse.c
        rooms_parse.c
        )

add_dependencies(vis_lem_in libft_target)

find_library(SDL2s SDL2 ./lib)
find_library(SDL2i SDL2_image ./lib)
find_library(SDL2t SDL2_ttf ./lib)
find_library(FT ft ./libft)
target_link_libraries(vis_lem_in PUBLIC ${SDL2s} ${SDL2i} ${SDL2t} ${FT})

add_custom_target(
        libft_target
        COMMAND make
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/libft
)


