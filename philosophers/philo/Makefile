# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/23 13:36:12 by lde-sutt          #+#    #+#              #
#    Updated: 2025/08/12 13:04:29 by lde-sutt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread #-fsanitize=address -fno-omit-frame-pointer 
INCLUDES = -Iincludes

SRC =	src/handle_errors.c \
		src/init.c \
		src/main.c \
		src/monitor.c \
		src/parsing.c \
		src/routine.c \
		src/utils.c \
		src/eating.c \
		src/easy_mutex.c

OBJ_DIR = .obj
OBJ = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJ)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean: 
	rm -f $(OBJ)

fclean:
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re