#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eklompus <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/16 10:33:18 by eklompus          #+#    #+#              #
#    Updated: 2019/11/16 10:33:22 by eklompus         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = vis_lemin

CC = gcc

CC_FLAGS = -Wall -Wextra -g3 -O3

ALL_C =	vis_lemin.c \
		print_error.c \
		init_sdl.c \
		load_image.c \
		load_font.c \
		read_file.c \
		rooms_parse.c \
		links_parse.c \
		line_parse.c \
		check_all.c \
		process_events.c \
		draw_elems.c \
		init_timers.c \
		calc_sizes.c \
		destroy.c \
		draw_all.c \
		get_dims.c

SRCDIR = ./srcs
OBJDIR = ./objs

ALL_OBJ = $(ALL_C:%.c=%.o)

OBJS = $(addprefix $(OBJDIR)/, $(ALL_OBJ))

INC_DIR =	./libft/includes \
			./includes \
			./include
#			/usr/include \


INC_FLAG = $(addprefix -I,$(INC_DIR))

LIB_DIR =	./libft \
			./lib
#			/usr/lib/x86_64-linux-gnu \

LIB_DIR_FLAG = $(addprefix -L,$(LIB_DIR))

LIBS = 		ft \
			SDL2 \
			SDL2_image \
			SDL2_ttf \
			m

LIBS_FLAG = $(addprefix -l,$(LIBS))

HEADERS = ./includes/vis_lemin.h

all: lib $(NAME)

lib:
	make -C ./libft

$(NAME): $(OBJS)
	$(CC) $(CC_FLAGS) $^ $(LIB_DIR_FLAG) $(LIBS_FLAG) -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	$(CC) $(CC_FLAGS) $(INC_FLAG) -c $< -o $@

clean:
	make clean -C ./libft
	rm -f $(OBJS)

fclean: clean
	rm -f ./libft/libft.a
	rm -f $(NAME)

re: fclean all

.PHONY: lib clean fclean all re
