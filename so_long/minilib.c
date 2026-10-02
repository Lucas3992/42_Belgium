/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:42:16 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/07/16 11:24:15 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	replace_nl(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		i++;
	if (i > 0 && str[i -1] == '\n')
		str[i -1] = '\0';
}

static int	ft_strlcpy(char	*dest, const char *src, int size)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (size == 0)
	{
		while (src[len])
			len++;
		return (len);
	}
	while (i < size - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (src[len])
		len++;
	return (len);
}

char	*ft_strdup(char *s)
{
	int		size;
	char	*dup_s;

	if (!s)
		return (NULL);
	size = ft_strlen(s) +1;
	dup_s = malloc(size);
	if (dup_s == NULL)
		return (NULL);
	ft_strlcpy(dup_s, s, size);
	return (dup_s);
}

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (n--)
	{
		*ptr = 0;
		ptr++;
	}
	return (s);
}
