/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:46:50 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/04/18 09:10:27 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(const char *s, char c)
{
	int	i;
	int	check;
	int	count;

	check = 0;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && check == 0)
		{
			check = 1;
			count++;
		}
		else if (s[i] == c)
			check = 0;
		i++;
	}
	return (count);
}

static void	free_s(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	*word_dup(const char *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(end - start +1);
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static char	**fill(char **arr, const char *s, char c)
{
	int	i;
	int	j;
	int	ind;

	i = 0;
	j = 0;
	ind = -1;
	while (s[i])
	{
		if (s[i] != c && ind == -1)
			ind = i;
		if ((s[i + 1] == '\0' && ind != -1 && s[i] != c)
			|| (s[i] == c && ind != -1))
		{
			arr[j] = word_dup(s, ind, i + ((s[i +1] == '\0' && s[i] != c)));
			if (!arr[j])
				return (free_s(arr), NULL);
			j++;
			ind = -1;
		}
		i++;
	}
	arr[j] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	if (!s)
		return (NULL);
	arr = malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	return (fill(arr, s, c));
}
