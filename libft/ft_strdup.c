/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:42:16 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/04/17 14:58:53 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t		size;
	char		*dup_s;

	size = ft_strlen(s) +1;
	dup_s = malloc(size);
	if (dup_s == NULL)
		return (NULL);
	ft_strlcpy(dup_s, s, size);
	return (dup_s);
}
