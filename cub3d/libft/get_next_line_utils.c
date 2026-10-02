/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 06:50:10 by sleyro            #+#    #+#             */
/*   Updated: 2025/11/21 12:59:23 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr2(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup_gnl(const char *s)
{
	char	*dup;
	int		len;
	int		i;

	len = ft_strlen_gnl(s);
	dup = (char *) malloc ((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

size_t	ft_strlen_gnl(const char *c)
{
	int	x;

	if (!c)
		return (0);
	x = 0;
	while (c[x] != '\0')
		x++;
	return (x);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;
	size_t			str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen_gnl(s);
	if (start >= str_len)
		len = 0;
	else if (start + len > str_len)
		len = str_len - start;
	substr = (char *) malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_join_gnl(char *s1, char *s2, int bytes_read)
{
	int		i;
	int		j;
	char	*joined;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	joined = (char *)malloc((ft_strlen_gnl(s1) + bytes_read +1) * sizeof(char));
	if (!joined)
		return (cleanfree_gnl(&s1));
	while (s1[i] != '\0')
	{
		joined[i] = s1[i];
		i++;
	}
	while (j < bytes_read)
	{
		joined[i] = s2[j];
		j++;
		i++;
	}
	joined[i] = '\0';
	return (joined);
}
