/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:48:16 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/16 13:28:21 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_any_quote(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

char	*remove_all_quotes(const char *s)
{
	char	*out;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	out = malloc(ft_strlen(s) +1);
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '"')
		{
			out[j] = s[i];
			j++;
		}
		i++;
	}
	out[j] = '\0';
	return (out);
}
