# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 10:18:56 by lde-sutt          #+#    #+#              #
#    Updated: 2025/06/20 15:34:38 by lde-sutt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Ilibft
SRC =  chunk_range.c moves_from_index.c chunks.c index_stack.c checks_parsing.c free.c handle_stack.c parsing.c push_swap.c push.c rotate_down.c rotate_up.c swap.c two_or_three.c
OBJ = $(SRC:.c=.o)
HEADER = push_swap.h 

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re