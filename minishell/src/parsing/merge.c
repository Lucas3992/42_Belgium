/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:43:57 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:43:57 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	merge_in_dq(t_exp *ex, const char *value)
{
	if (!value)
		return (1);
	return (join_strings(ex, value));
}

static int	merge_first_part(t_exp *ex, char **parts)
{
	if (!parts)
		return (0);
	if (!parts[0])
		return (1);
	if (join_strings(ex, parts[0]) == 0)
		return (0);
	return (1);
}

static int	push_rest(t_exp *ex, char **parts)
{
	int		i;
	char	*taken;

	if (!parts)
		return (0);
	i = 1;
	while (parts[i])
	{
		taken = reset_and_keep_str(ex);
		if (!taken)
			return (0);
		if (!push_str(ex, taken))
			return (free(taken), 0);
		if (!join_strings(ex, parts[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	merge_outside_quotes(t_exp *ex, const char *value)
{
	char	**parts;
	int		check;

	if (!value)
		return (1);
	if (value[0] == '\0')
		return (1);
	parts = ft_split2(value, ' ', '\t');
	if (!parts)
		return (0);
	check = merge_first_part(ex, parts);
	if (check)
		check = push_rest(ex, parts);
	free_array(parts);
	return (check);
}

int	ultimate_merger(t_exp *ex, const char *value, int dq)
{
	if (dq != 0)
		return (merge_in_dq(ex, value));
	return (merge_outside_quotes(ex, value));
}
