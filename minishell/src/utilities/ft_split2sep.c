/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2sep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:48:00 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:48:00 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_sep2(char c, const char *seps)
{
	if (c == seps[0])
		return (1);
	if (c == seps[1])
		return (1);
	return (0);
}

static int	count_words2(const char *s, const char *seps)
{
	int	i;
	int	count;

	if (s == NULL)
		return (0);
	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_sep2(s[i], seps))
			i++;
		if (!s[i])
			break ;
		count++;
		while (s[i] && !is_sep2(s[i], seps))
			i++;
	}
	return (count);
}

static char	**free_all2(char **array, int last)
{
	int	x;

	if (array == NULL)
		return (NULL);
	x = last;
	while (x >= 0)
	{
		if (array[x] != NULL)
			free(array[x]);
		x--;
	}
	free(array);
	return (NULL);
}

static char	**fill_array2(char **a, const char *s, int words, const char *seps)
{
	int	x;
	int	i;
	int	start;

	x = 0;
	i = 0;
	while (x < words)
	{
		while (s[i] && is_sep2(s[i], seps))
			i++;
		start = i;
		while (s[i] && !is_sep2(s[i], seps))
			i++;
		a[x] = ft_substr(s, start, i - start);
		if (a[x] == NULL)
			return (free_all2(a, x -1));
		x++;
	}
	a[x] = NULL;
	return (a);
}

char	**ft_split2(const char *s, char sep1, char sep2)
{
	char	**array;
	int		words;
	char	seps[2];

	if (s == NULL)
		return (NULL);
	seps[0] = sep1;
	seps[1] = sep2;
	words = count_words2(s, seps);
	array = NULL;
	array = (char **)malloc(sizeof(char *) * (words +1));
	if (array == NULL)
		return (NULL);
	array = fill_array2(array, s, words, seps);
	return (array);
}
