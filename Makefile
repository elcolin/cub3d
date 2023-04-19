# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 14:57:18 by ecolin            #+#    #+#              #
#    Updated: 2023/03/09 16:04:23 by ecolin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -g3 -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 #-fsanitize=address

NAME = cub3d

SRC = main.c hitpoint.c print.c parse.c utils2.c free.c texture.c utils.c map.c

GNL = get_next_line.c get_next_line_utils.c

GPATH= $(addprefix gnl/, $(GNL))

SPATH= $(addprefix src/, $(SRC))

OBJ = $(SPATH:.c=.o)

GOBJ = $(GPATH:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -I./src -I./gnl -I./mlx_linux -c $< -o ${<:.c=.o}

all: MLX $(NAME)
 
MLX:
	cd mlx_linux && $(MAKE)

$(NAME): $(GOBJ) $(OBJ) src/cub3d.h gnl/get_next_line.h
	$(CC) $(CFLAGS) $(GOBJ) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	/bin/rm -rf $(OBJ)
	/bin/rm -rf $(GOBJ)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all