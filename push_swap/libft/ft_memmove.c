/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:21:41 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/04/16 13:12:01 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*temp_dest;
	const unsigned char	*temp_src;

	if (dest == src || n == 0)
		return (dest);
	temp_dest = (unsigned char *)dest;
	temp_src = (const unsigned char *)src;
	if (dest < src)
	{
		while (n--)
		{
			*temp_dest = *temp_src;
			temp_dest++;
			temp_src++;
		}
	}
	else
	{
		temp_dest = temp_dest + n;
		temp_src = temp_src + n;
		while (n--)
			*--temp_dest = *--temp_src;
	}
	return (dest);
}
