# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/13 09:40:06 by lde-sutt          #+#    #+#              #
#    Updated: 2025/10/13 15:02:52 by lde-sutt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_atoi.c ft_isalpha.c ft_isprint.c ft_lstadd_front_bonus.c ft_split.c ft_strlen.c ft_substr.c \
		ft_bzero.c ft_isascii.c ft_itoa.c ft_lstclear_bonus.c ft_lstnew_bonus.c ft_strdup.c ft_strncmp.c ft_strcmp.c \
		ft_calloc.c ft_isdigit.c ft_lstiter_bonus.c ft_strjoin.c ft_strrchr.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_strchr.c ft_strstr.c ft_isalnum.c ft_memcpy.c

OBJS = $(SRC:.c=.o)
NAME = libft.a

all: $(NAME)
	
$(NAME): $(OBJS)
	@ar rcs $@ $^

%.o: %.c libft.h
	@$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean:
	@rm -f $(NAME) $(OBJS)

re: fclean all