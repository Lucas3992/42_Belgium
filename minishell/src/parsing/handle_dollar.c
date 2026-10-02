/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:43:50 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:43:51 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_start(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}

static void	scan_var(const char *str, int i, int *len, int *qmark)
{
	int	j;
	int	start;

	*len = 0;
	*qmark = 0;
	if (!str || str[i] != '$' || str[i + 1] == '\0')
		return ;
	if (str[i +1] == '?')
	{
		*qmark = 1;
		return ;
	}
	if (str[i + 1] >= '0' && str[i + 1] <= '9')
	{
		*len = 1;
		return ;
	}
	start = i +1;
	if (!is_valid_start(str[start]))
		return ;
	j = start + 1;
	while (str[j] && (ft_isalnum((unsigned char)str[j]) || str[j] == '_'))
		j++;
	*len = j - start;
}

static int	handle_dollar_prefix(t_exp *ex)
{
	char	next;

	if (!ex || !ex->in)
		return (0);
	next = ex->in[ex->i +1];
	if (next == '\'' && ex->sq == 0 && ex->dq == 0)
		return (handle_dollar_sq(ex));
	if (next == '\"' && ex->dq == 0 && ex->sq == 0)
		return (handle_dollar_dq(ex));
	if (next == '0')
		return (handle_dollar_zero(ex));
	return (-1);
}

int	handle_dollar(t_exp *ex)
{
	int		len;
	int		qmark;
	char	*value;
	int		res;

	len = 0;
	qmark = 0;
	value = NULL;
	res = handle_dollar_prefix(ex);
	if (res != -1)
		return (res);
	scan_var(ex->in, ex->i, &len, &qmark);
	if (qmark == 0 && len == 0)
		return (handle_literal_dollar(ex));
	value = transform_dollar_value(ex, len, qmark);
	if (!value)
		return (0);
	if (!ultimate_merger(ex, value, ex->dq))
		return (free(value), 0);
	if (qmark != 0)
		ex->i = ex->i +2;
	else
		ex->i = ex->i + len +1;
	return (free(value), 1);
}
