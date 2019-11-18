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

SRCS =	vis_lemin.c \
		print_error.c \
		init_sdl.c \
		load_image.c \
		load_font.c \
		read_file.c

OBJS = $(SRCS:.c=.o)

INC_DIR =	./include \
			./libft/includes

INC_FLAG = $(addprefix -I,$(INC_DIR))

LIB_DIR =	./lib \
			./libft/

LIB_DIR_FLAG = $(addprefix -L,$(LIB_DIR))

LIBS = 		ft \
			SDL2 \
			SDL2_image \
			SDL2_ttf

LIBS_FLAG = $(addprefix -l,$(LIBS))

HEADERS = ./vis_lemin.h

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(CC_FLAGS) $^ $(LIB_DIR_FLAG) $(LIBS_FLAG) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CC_FLAGS) $(INC_FLAG) -c $< -o $@

clean:
	make clean -C ./libft
	rm -f $(OBJS)

fclean: clean
	rm -f ./libft/libft.a
	rm -f $(NAME)

re: fclean all