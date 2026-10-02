/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:20:00 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/04/15 15:10:10 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_size;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	total_size = ft_strlen(s1) + ft_strlen(s2) +1;
	joined = malloc(total_size);
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, s1, total_size);
	ft_strlcat(joined, s2, total_size);
	return (joined);
}
