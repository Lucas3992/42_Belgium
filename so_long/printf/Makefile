# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/06 12:58:51 by lde-sutt          #+#    #+#              #
#    Updated: 2025/05/06 13:33:12 by lde-sutt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRC = ft_basics.c ft_printf.c ft_ptrhex.c
OBJ = $(SRC:.c=.o)
HEADER = ft_printf.h

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME)

re: fclean all

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re