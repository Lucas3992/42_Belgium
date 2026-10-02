/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:26:00 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/04/18 09:15:33 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *sentence, const char *word, size_t len)
{
	size_t	i;
	size_t	j;

	if (*word == '\0')
		return ((char *)sentence);
	i = 0;
	while (i < len && sentence[i])
	{
		j = 0;
		if (sentence[i] == word[j])
		{
			while (i + j < len && word[j] && sentence[i + j] == word[j])
				j++;
			if (word[j] == '\0')
				return ((char *)&sentence[i]);
		}
		i++;
	}
	return (NULL);
}
