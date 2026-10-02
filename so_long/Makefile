# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/07 09:11:38 by lde-sutt          #+#    #+#              #
#    Updated: 2025/07/16 14:39:45 by lde-sutt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
INCLUDES = -I. -I$(MLX_DIR)

PRINTF_DIR = ./printf
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a
PRINTF_INC = -I$(PRINTF_DIR)


SRC =	graphic/init.c \
		minilib.c \
		parsing/check_path.c \
		parsing/check_pec.c \
		parsing/check_args.c \
		parsing/check_map.c \
		parsing/errors_or_free.c \
		so_long.c \
		gnl/get_next_line_utils.c \
		gnl/get_next_line.c \
		controls/move.c \
		controls/support.c

OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
OBJ_DIR = obj
DIRS = $(sort $(dir $(OBJ)))

all : $(NAME)

$(NAME): $(MLX) $(OBJ) $(PRINTF_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) $(PRINTF_INC) -o $@ $(OBJ) $(MLX_FLAGS) $(PRINTF_LIB)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MLX):
	make -C $(MLX_DIR)

$(PRINTF_LIB):
	make -C $(PRINTF_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(MLX_DIR) clean
	make -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(PRINTF_DIR) fclean

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: all clean fclean re