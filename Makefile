# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 07:50:40 by imqandyl          #+#    #+#              #
#    Updated: 2025/04/18 17:42:13 by lalwafi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub3d
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -Iincludes
CFLAGS	+= -fsanitize=address -g3
# LIBRARY := -L./minilibx -lmlx -lm -march=native -framework OpenGL AppKit #-framework

MINILIBX := minilibx/

SRC     = srcs/main.c \
          parsing/parse_map.c \
          srcs/draw_map.c srcs/movement.c \


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

$(NAME): $(OBJS)
	make -C $(MINILIBX)
	$(CC) $(OBJS) $(CFLAGS) -L$(MINILIBX) -lmlx -lm -march=native $(MLXFLG) -o $(NAME)
#$(CC) $(CFLAGS) $(OBJS) $(LIBRARY) -o $(NAME) $(MLXFLG)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(MINILIBX)
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all




# NAME = cub3d

# SRCS = srcs/main.c \
#           parsing/parse_map.c \
#           srcs/draw_map.c srcs/movement.c \

# CC = cc

# CFLAGS = -Wall -Werror -Wextra -g3

# OS:= ${shell uname}
# ifeq (${OS},Darwin)
# 	MLXDIR = mlx
# 	MLXFLG = -framework OpenGL -framework Appkit
# 	CFLAGS += -D OSX
# else
# 	MLXDIR = mlx-linux
# 	MLXFLG = -lXext -lX11
# 	CFLAGS += -D LINUX
#  endif

# SRCDIR = srcs

# OBJDIR = objs

# OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# all: $(NAME)

# $(OBJDIR)/%.o: $(SRCDIR)/%.c
# 	$(CC) $(CFLAGS) -I$(MLXDIR) -c $< -o $@

# $(OBJDIR):
# 	mkdir -p $(OBJDIR)

# $(NAME): $(OBJS)
# 	make -C libft
# 	make -C $(MLXDIR)
# 	$(CC) $(OBJS) $(CFLAGS) -L$(MLXDIR) -lmlx -lm -march=native $(MLXFLG) -o $(NAME)

# norm: 
# 	@python3 -m norminette

# clean:
# 	rm -rf $(OBJS) $(OBJDIR) 
# 	make clean -C $(MLXDIR)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all