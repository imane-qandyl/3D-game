# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 07:50:40 by imqandyl          #+#    #+#              #
#    Updated: 2025/05/31 07:58:40 by imqandyl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3d
BONUS_NAME  = cub3d_bonus

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -Iincludes
CFLAGS     += -fsanitize=address -g3

LIBFT       = libft
MINILIBX    = minilibx

OS := $(shell uname)
ifeq ($(OS),Darwin)
    MLXFLG = -framework OpenGL -framework AppKit
    CFLAGS += -D OSX
else
    MINILIBX = mlx-linux
    MLXFLG = -lXext -lX11
    CFLAGS += -D LINUX
endif
GNL = get_next_line

GNL_SRC = \
$(GNL)/get_next_line.c \
$(GNL)/get_next_line_utils.c
# Mandatory Sources
SRC = \
mandatory_part/srcs/main.c \
mandatory_part/srcs/init.c \
mandatory_part/srcs/make_texture_maps.c \
mandatory_part/srcs/draw_2d.c \
mandatory_part/srcs/movement_1.c \
mandatory_part/srcs/movement_2.c \
mandatory_part/srcs/rendering_2d.c \
mandatory_part/srcs/rendering_3d.c \
mandatory_part/srcs/rendering_3d_2.c \
mandatory_part/srcs/raycast_v_h.c \
mandatory_part/parsing/parse_map.c \
mandatory_part/parsing/parse_map_utils.c \
mandatory_part/parsing/parse_map_utils1.c \
mandatory_part/parsing/parse.c \
mandatory_part/parsing/parse_utils.c \
mandatory_part/parsing/parse_utils1.c \
mandatory_part/parsing/parse_textures.c \
mandatory_part/parsing/parse_colors.c \
mandatory_part/parsing/parse_colors_utils.c \
mandatory_part/parsing/parse_player.c \
$(GNL_SRC)

# Bonus Sources
SRC_BONUS = \
bonus_part/srcs/main.c \
bonus_part/srcs/init.c \
bonus_part/srcs/minimap.c \
bonus_part/srcs/make_texture_maps.c \
bonus_part/srcs/draw_2d.c \
bonus_part/srcs/movement_1.c \
bonus_part/srcs/movement_2.c \
bonus_part/srcs/rendering_2d.c \
bonus_part/srcs/rendering_3d.c \
bonus_part/srcs/rendering_3d_2.c \
bonus_part/srcs/raycast_v_h.c \
bonus_part/parsing/parse_map.c \
bonus_part/parsing/parse_map_utils.c \
bonus_part/parsing/parse_map_utils1.c \
bonus_part/parsing/parse.c \
bonus_part/parsing/parse_utils.c \
bonus_part/parsing/parse_utils1.c \
bonus_part/parsing/parse_textures.c \
bonus_part/parsing/parse_colors.c \
bonus_part/parsing/parse_colors_utils.c \
bonus_part/parsing/parse_player.c \
$(GNL_SRC)

# Objects
OBJS        = $(SRC:.c=.o)
OBJS_BONUS  = $(SRC_BONUS:.c=.o)

# Build Rules
all: $(NAME) 

$(LIBFT):
	@$(MAKE) -C ./libft

$(MINILIBX):
	@make -C $(MINILIBX)

$(NAME): $(OBJS)
	make -C $(MINILIBX)
	@make -C $(LIBFT)

	$(CC) $(OBJS) $(CFLAGS) -L$(MINILIBX) $(LIBFT)/libft.a -lmlx -lm -march=native $(MLXFLG) -o $(NAME)

$(BONUS_NAME): $(OBJS_BONUS)
	make -C $(MINILIBX)
	@make -C $(LIBFT)

	$(CC) $(OBJS_BONUS) $(CFLAGS) -L$(MINILIBX) $(LIBFT)/libft.a -lmlx -lm -march=native $(MLXFLG) -o $(BONUS_NAME)

$(GNL)/%.o: $(GNL)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUS_NAME)

clean:
	@make clean -C $(LIBFT)
	@make clean -C $(MINILIBX)
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re bonus
