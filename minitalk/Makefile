# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/25 13:37:54 by lde-sutt          #+#    #+#              #
#    Updated: 2025/06/30 13:51:32 by lde-sutt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I$(FT_DIR)

FT_DIR = ft_printf
FT_LIB = $(FT_DIR)/libftprintf.a

SERVER = server
CLIENT = client
NAME = $(SERVER) $(CLIENT)

SRC_COMMON = utils.c
SRC_SERVER = server.c
SRC_CLIENT = client.c

OBJ_SERVER = $(SRC_SERVER:.c=.o) $(SRC_COMMON:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o) $(SRC_COMMON:.c=.o)

HEADER = minitalk.h

all : $(FT_LIB) $(NAME)

$(FT_LIB):
	$(MAKE) -C $(FT_DIR)

$(SERVER): $(OBJ_SERVER) $(FT_LIB)
	$(CC) $(CFLAGS) $^ -o $@

$(CLIENT): $(OBJ_CLIENT) $(FT_LIB)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)
	$(MAKE) -C $(FT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(FT_DIR) fclean

re: fclean all

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re