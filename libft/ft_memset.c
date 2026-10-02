/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:19:06 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/04/16 13:12:15 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void	*s, int c, size_t	n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (n--)
	{
		*ptr = (unsigned char) c;
		ptr++;
	}
	return (s);
}
