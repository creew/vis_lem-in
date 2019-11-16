cmake_minimum_required(VERSION 3.14)
project(vis_lem_in C)

set(CMAKE_C_STANDARD 11)

include_directories(.
                    ./include
                    ./libft)

add_executable(vis_lem_in
        vis_lemin.c
        print_error.c
        init_sdl.c
        load_image.c
        vis_lemin.h)

