# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 07:50:40 by imqandyl          #+#    #+#              #
#    Updated: 2025/04/04 11:13:47 by imqandyl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub3d
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -Iincludes
LIBRARY := -L./minilibx -lmlx -framework OpenGL -framework AppKit

MINILIBX := minilibx/

SRC     = srcs/main.c \
          parsing/parse_map.c \
          srcs/draw_map.c \

OBJS    = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBRARY) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(MINILIBX)
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all
