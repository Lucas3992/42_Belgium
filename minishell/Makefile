# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/13 09:48:40 by lde-sutt          #+#    #+#              #
#    Updated: 2025/10/21 12:42:46 by dcasiell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g
SRC_DIR		:= src
OBJ_DIR 	:= obj
LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a
INCLUDE		:= -Iinclude -I$(LIBFT_DIR)
RL_FLAGS	:= -lreadline -lncurses
SRC			:= \
			main/main.c main/build_env.c main/prompt.c main/return_to_env.c main/exec_and_clean.c \
			built_inns/echo.c built_inns/env.c built_inns/export.c built_inns/unset.c \
			built_inns/cd.c built_inns/exit.c built_inns/pwd.c built_inns/export_no_args.c \
			built_inns/exec_builtin.c built_inns/dot.c \
			errors_and_free/error.c errors_and_free/free.c errors_and_free/ef_pipes.c errors_and_free/free_bi.c \
			errors_and_free/free_join.c \
			execution/exec.c execution/exec_utils.c execution/cmd_exec.c execution/pipe_exec.c \
			execution/path_solve.c execution/cmd_utils.c execution/exec_aid.c \
			errors_and_free/free_ex.c errors_and_free/free_ms.c errors_and_free/error_126_or_127.c \
			heredoc/hdoc_utils.c heredoc/heredoc_prepare.c heredoc/more_hdoc_utils.c heredoc/redirect_hdoc_handler.c \
			parsing/array.c parsing/cut_utils.c parsing/init.c \
			parsing/build_ast.c parsing/redir.c parsing/checks.c parsing/cut.c parsing/expansions.c \
			parsing/parsing.c parsing/quotes.c parsing/handle_dollar_utils.c \
			parsing/merge.c parsing/handle_dollar.c parsing/expand_one_token.c parsing/redir_aid.c \
			parsing/handle_expandable_word.c \
			redirections/redirect.c redirections/redir_choices.c \
			signals/signal.c signals/signal_utils.c \
			childs/child.c \
			cmd/get_cmd_path.c \
			tokens/create_tokens.c tokens/remove_token.c tokens/insert_word.c \
			utilities/env_utils.c utilities/export_utils.c utilities/quotes_utils.c \
			utilities/main_utils.c utilities/lst_utils.c utilities/cd_utils.c utilities/join_str.c \
			utilities/shlvl.c utilities/ft_split2sep.c utilities/dup_empty.c utilities/add_char.c utilities/push_str.c \
			utilities/reset_keep.c utilities/skips.c utilities/transform_dollar_value.c \
			utilities/consume_pipe.c \

OBJS		:= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
MAKEFLAGS 	+= --no-print-directory

all : $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "Making minishell..."
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBFT) $(RL_FLAGS) -o $@
	@echo "Minishell ready !"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "Cleaned"

fclean:
	@rm -rf $(NAME) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "fCleaned"

c: all clean

re: fclean all

.PHONY: clean fclean re all
