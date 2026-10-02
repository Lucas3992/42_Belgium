/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:45:17 by dcasiell          #+#    #+#             */
/*   Updated: 2025/10/13 09:39:12 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char *str, char *to_find, int i)
{
	int	j;

	j = 0;
	while (to_find[j] != '\0')
	{
		if (str[i + j] != to_find[j])
			return (0);
		j++;
	}
	return (1);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;

	i = 0;
	if (*to_find == '\0')
		return (str);
	while (str[i] != '\0')
	{
		if (str[i] == to_find[0])
		{
			if (check(str, to_find, i) == 1)
			{
				return (&str[i]);
			}
		}
		i++;
	}
	return (NULL);
}
