cmake_minimum_required(VERSION 3.14)
project(vis_lem_in C)

set(CMAKE_C_STANDARD 11)

include_directories(
        .
        ./include
        ./includes
        ./libft/includes
        ./ft_printf/includes
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
        srcs/calc_sizes.c
        srcs/draw_all.c
        srcs/get_dims.c
        srcs/draw_arc.c
        srcs/moves.c srcs/draw_roomants.c srcs/draw_fat_line.c)



find_library(SDL2s SDL2 ./lib)
find_library(SDL2i SDL2_image ./lib)
find_library(SDL2t SDL2_ttf ./lib)
target_link_libraries(vis_lem_in PUBLIC ${SDL2s} ${SDL2i} ${SDL2t} ${FT} ${FTPR} )

add_dependencies(vis_lem_in libftprintf_target libft_target)

find_library(FTPR ftprintf ./ft_printf)
find_library(FT ft ./libft)

add_custom_target(
        libft_target
        COMMAND make
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/libft
)

add_custom_target(
        libftprintf_target
        COMMAND make
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/ft_printf
)


