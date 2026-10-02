/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:45:48 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/04/16 13:55:43 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char c, const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	total_size;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (is_in(s1[start], set))
		start++;
	while (end > 0 && is_in(s1[end -1], set))
		end--;
	total_size = end - start;
	trimmed = ft_substr(s1, start, total_size);
	if (!trimmed)
		return (NULL);
	return (trimmed);
}
