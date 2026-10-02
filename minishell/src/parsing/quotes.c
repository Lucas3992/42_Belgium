/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:44:05 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:44:11 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_zero(int *a, int *b, int *c, int *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
}

int	handle_sq(char c, int *sq, int dq)
{
	if (!dq && c == '\'')
	{
		*sq = !*sq;
		return (1);
	}
	return (0);
}

int	handle_dq(char c, int *dq, int sq)
{
	if (!sq && c == '\"')
	{
		*dq = !*dq;
		return (1);
	}
	return (0);
}

static int	get_size_in_quotes(const char *str)
{
	int	i;
	int	sq;
	int	dq;
	int	size;

	if (!str)
		return (0);
	init_zero(&i, &sq, &dq, &size);
	while (str[i])
	{
		if (!handle_sq(str[i], &sq, dq) && !handle_dq(str[i], &dq, sq))
			size++;
		i++;
	}
	return (size);
}

char	*remove_quotes_from_string(const char *str)
{
	int		i;
	int		j;
	int		sq;
	int		dq;
	char	*new;

	if (!str)
		return (NULL);
	new = malloc(get_size_in_quotes(str) +1);
	if (!new)
		return (NULL);
	init_zero(&i, &sq, &dq, &j);
	while (str[i])
	{
		if (!handle_sq(str[i], &sq, dq) && !handle_dq(str[i], &dq, sq))
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}
