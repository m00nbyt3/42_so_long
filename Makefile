# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycarro <ycarro@student.42madrid.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 10:56:40 by ycarro            #+#    #+#              #
#    Updated: 2021/10/26 11:43:17 by ycarro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := so_long
GNL_NAME := gnl.a
MLX_NAME := mlx.h

CC = gcc

IDIR = include/
INCLUDE = -I $(IDIR)
HEADERFILES :=	include/so_long.h
GNL_HEADERFILES := gnl/get_next_line.h

SRCFILES :=	collisions.c \
			exit.c \
			map.c \
			player.c \
			draw.c \
			main.c \
			parse.c \
			preload.c \
			get_next_line.c \
			get_next_line_utils.c

OBJFILES := $(SRCFILES:%.c=obj/%.o)

LDFLAGS =  -lmlx -framework OpenGL -framework AppKit
CFLAGS = -Wall -Wextra -Werror $(INCLUDE)

all: $(NAME)

$(NAME): $(OBJFILES)
		$(CC) $(CFLAGS) $(LDFLAGS) $(OBJFILES) -o $@

obj/%.o: src/%.c $(HEADERFILES)
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -o $@ -c $<

obj/%.o: gnl/%.c $(GNL_HEADERFILES)
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -o $@ -c $<

clean:
		rm -f $(OBJFILES)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY = all clean fclean re
