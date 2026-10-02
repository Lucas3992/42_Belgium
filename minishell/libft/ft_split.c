/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:19:54 by dcasiell          #+#    #+#             */
/*   Updated: 2025/10/13 09:38:15 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkwords(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	**freeall(char **array, int x)
{
	while (x >= 0)
	{
		free (array[x]);
		x--;
	}
	free (array);
	return (NULL);
}

static char	**fill_array(char **array, char const *s, char c)
{
	int		x;
	int		i;
	int		start;

	x = 0;
	i = 0;
	while (x < checkwords(s, c))
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (start != i)
		{
			array[x] = ft_substr(s, start, i - start);
			if (!array[x])
				return (freeall(array, x));
			x++;
		}
	}
	array[x] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = (char **) malloc ((checkwords(s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array = fill_array(array, s, c);
	return (array);
}
