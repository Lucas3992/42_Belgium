/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:02:25 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/04/17 15:22:19 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dest, const char	*src, size_t	size)
{
	size_t	lendest;
	size_t	lensrc;
	size_t	i;

	lendest = 0;
	lensrc = 0;
	while (dest[lendest] && lendest < size)
		lendest++;
	while (src[lensrc])
		lensrc++;
	if (lendest == size)
		return (size + lensrc);
	i = 0;
	while (src[i] && lendest + i < size -1)
	{
		dest[lendest + i] = src[i];
		i++;
	}
	dest[lendest + i] = '\0';
	return (lendest + lensrc);
}
