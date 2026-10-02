/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:43:11 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/21 12:47:04 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell(t_shell *ms, char **env)
{
	bzero(ms, sizeof(t_shell));
	ms->last_exit_code = 0;
	ms->should_exit = false;
	ms->exit_status = 0;
	rl_catch_signals = 0;
	create_env(env, ms);
}

static int	lex_and_maybe_expand(t_shell *ms, char *rlbuffer,
								t_token **tokens, int *empty_input)
{
	int	ok;

	*tokens = NULL;
	*empty_input = 0;
	*tokens = tokenize_line(rlbuffer);
	if (!*tokens)
	{
		msg_error("syntax error: unclosed quotes", NULL, NULL, 1);
		ms->last_exit_code = 2;
		return (0);
	}
	if ((*tokens)->type == T_EOF)
		*empty_input = 1;
	ok = ultimate_expand_tokens(tokens, ms);
	if (!ok)
		return (-1);
	return (1);
}

static int	handle_expand_result(int st, char **rlbuffer, t_token **tokens)
{
	if (st == -1)
	{
		if (*rlbuffer)
			free(*rlbuffer);
		if (*tokens && *tokens)
			free_tokens(*tokens);
		*tokens = NULL;
		*rlbuffer = NULL;
		return (0);
	}
	if (st == 0)
	{
		if (tokens && *tokens)
			free_tokens(*tokens);
		if (rlbuffer && *rlbuffer)
			free(*rlbuffer);
		if (tokens)
			*tokens = NULL;
		if (rlbuffer)
			*rlbuffer = NULL;
		return (2);
	}
	return (1);
}

static int	shell_loop(t_shell *minishell)
{
	char	*rlbuffer;
	t_token	*tokens;
	int		empty_input;
	int		st;

	st = get_line_and_history(minishell, &rlbuffer);
	if (!st)
		return (0);
	st = lex_and_maybe_expand(minishell, rlbuffer, &tokens, &empty_input);
	st = handle_expand_result(st, &rlbuffer, &tokens);
	if (st == 0)
		return (0);
	if (st == 2)
		return (1);
	free(rlbuffer);
	rlbuffer = NULL;
	st = build_ast_then_free_tokens(minishell, &tokens, empty_input);
	if (!st)
		return (1);
	st = prepare_all_heredocs(minishell);
	if (!st)
		return (free_ast(minishell->tree), 1);
	run_exec_and_cleanup(minishell);
	close_all_heredocs_from_ast(minishell->tree);
	return (1);
}

int	main(int ac, char **argv, char **envp)
{
	t_shell	minishell;

	if (ac == 1)
	{
		init_shell(&minishell, envp);
		while (1)
		{
			write(1, "\0", 0);
			if (shell_loop(&minishell) == 0)
				break ;
		}
		rl_clear_history();
		close_all_heredocs_from_ast(minishell.tree);
		free_ms(&minishell, NULL);
		return (minishell.last_exit_code);
	}
	else
	{
		ft_puterr("minishell: ");
		ft_puterr(argv[1]);
		ft_puterr(": No such file or directory\n");
		return (127);
	}
}
