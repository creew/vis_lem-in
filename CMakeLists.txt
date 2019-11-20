cmake_minimum_required(VERSION 3.14)
project(vis_lem_in C)

set(CMAKE_C_STANDARD 11)

include_directories(
        .
        ./include
        ./includes
        ./libft/includes
)


add_executable(
        vis_lem_in
        srcs/vis_lemin.c
        srcs/print_error.c
        srcs/init_sdl.c
        srcs/load_image.c
        srcs/load_font.c
        srcs/read_file.c
        srcs/links_parse.c
        srcs/line_parse.c
        srcs/rooms_parse.c
        srcs/check_all.c
        srcs/process_events.c
        srcs/draw_elems.c
        srcs/init_timers.c
        srcs/destroy.c
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


