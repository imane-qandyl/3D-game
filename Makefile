# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 07:50:40 by imqandyl          #+#    #+#              #
#    Updated: 2025/05/03 12:35:57 by imqandyl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub3d
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -Iincludes
CFLAGS	+= -fsanitize=address -g3
LIBRARY := -L./minilibx -lmlx -lm -march=native -framework OpenGL AppKit -framework

MINILIBX := minilibx/
get_next_line := get_next_line
LIBFT = libft

SRC     = srcs/main.c \
          srcs/draw_map.c\
          execution/movement.c\
		  execution/raycasting.c\
          parsing/parse_map.c \
		  parsing/parse.c \
          parsing/parse_textures.c \
          parsing/parse_colors.c \
		  get_next_line/get_next_line.c\
		  get_next_line/get_next_line_utils.c


OS:= ${shell uname}
ifeq (${OS},Darwin)
	MINILIBX := minilibx/
	MLXFLG = -framework OpenGL -framework Appkit
	CFLAGS += -D OSX
else
	MINILIBX = mlx-linux
	MLXFLG = -lXext -lX11
	CFLAGS += -D LINUX
 endif


OBJS    = $(SRC:.c=.o)

all: $(NAME)
$(LIBFT):
	@$(MAKE) -C ./libft

$(NAME): $(OBJS)
	make -C $(MINILIBX)
	@make -C $(LIBFT)

	$(CC) $(OBJS) $(CFLAGS) -L$(MINILIBX) $(LIBFT)/libft.a -lmlx -lm -march=native $(MLXFLG) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LIBFT)
	make clean -C $(MINILIBX)
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
