/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:41:42 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/23 11:05:52 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msg_error(char *msg, char *arg, char *msg_end, int return_code)
{
	ft_putstr_fd("minishell: ", 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	if (msg_end)
		ft_putendl_fd(msg_end, 2);
	if (!msg_end)
		write(2, "\n", 1);
	return (return_code);
}

const char	*which_token_error(t_token *token)
{
	if (!token || token->type == T_EOF)
		return ("bash: syntax error near unexpected token 'newline'");
	else if (token->type == T_PIPE)
		return ("bash: syntax error near unexpected token '|'");
	else if (token->type == T_LT)
		return ("bash: syntax error near unexpected token '<'");
	else if (token->type == T_GT)
		return ("bash: syntax error near unexpected token '>'");
	else if (token->type == T_DLT)
		return ("bash: syntax error near unexpected token '<<'");
	else if (token->type == T_DGT)
		return ("bash: syntax error near unexpected token '>>'");
	return ("bash: syntax error near unexpected token");
}

void	msg_error_exit(char *msg, int exit_c, t_shell *ms)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	if (exit_c != 0)
	{
		ms->last_exit_code = exit_c;
		free_ms(ms, NULL);
		exit(exit_c);
	}
}

void	ft_puterr(const char *s)
{
	if (s)
		write(2, s, ft_strlen(s));
}
