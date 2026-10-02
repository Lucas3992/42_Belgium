/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:43:47 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:43:48 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_dollar_sq(t_exp *ex)
{
	int		start;
	int		j;
	char	*chunk;

	start = ex->i +2;
	j = start;
	while (ex->in[j] && ex->in[j] != '\'')
		j++;
	if (!ex->in[j])
		return (0);
	chunk = ft_substr(ex->in, start, j - start);
	if (!chunk)
		return (0);
	if (!join_strings(ex, chunk))
		return (free(chunk), 0);
	free(chunk);
	ex->i = j +1;
	return (1);
}

int	handle_dollar_dq(t_exp *ex)
{
	int		start;
	int		j;
	char	*chunk;

	start = ex->i +2;
	j = start;
	while (ex->in[j] && ex->in[j] != '\"')
		j++;
	if (!ex->in[j])
		return (handle_literal_dollar(ex));
	chunk = ft_substr(ex->in, start, j - start);
	if (!chunk)
		return (0);
	if (!join_strings(ex, chunk))
		return (free(chunk), 0);
	free(chunk);
	ex->i = j +1;
	return (1);
}

int	handle_dollar_zero(t_exp *ex)
{
	char	*value;
	int		check;

	value = ft_strdup("minishell");
	if (!value)
		return (0);
	check = ultimate_merger(ex, value, ex->dq);
	free(value);
	if (!check)
		return (0);
	ex->i = ex->i + 2;
	return (1);
}

int	handle_literal_dollar(t_exp *ex)
{
	int	check;

	check = add_char(ex, '$');
	if (check == 0)
		return (0);
	ex->i = ex->i +1;
	return (1);
}
