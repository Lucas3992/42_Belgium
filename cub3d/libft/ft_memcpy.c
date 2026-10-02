/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:06:45 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/04/18 09:21:02 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*temp_src;
	unsigned char		*temp_dest;

	if (!dest && !src)
		return (NULL);
	temp_dest = (unsigned char *)dest;
	temp_src = (const unsigned char *)src;
	while (n--)
	{
		*temp_dest = *temp_src;
		temp_dest++;
		temp_src++;
	}
	return (dest);
}
