# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 07:50:40 by imqandyl          #+#    #+#              #
#    Updated: 2025/04/24 19:42:38 by imqandyl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub3d
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -Iincludes 
LIBRARY := -L./minilibx -lmlx -framework OpenGL -framework AppKit

MINILIBX := minilibx/
get_next_line := get_next_line
LIBFT = libft

SRC     = srcs/main.c \
          parsing/parse_map.c \
          parsing/parse.c \
          parsing/parse_textures.c \
          parsing/parse_colors.c \
          srcs/draw_map.c\
          srcs/movement.c\
		  get_next_line/get_next_line.c\
		  get_next_line/get_next_line_utils.c

OBJS    = $(SRC:.c=.o)

all: $(NAME)
$(LIBFT):
	@$(MAKE) -C ./libft
$(NAME): $(OBJS)
	make -C $(MINILIBX)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT)/libft.a $(LIBRARY) -o $(NAME)


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
