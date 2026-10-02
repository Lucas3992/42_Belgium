/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:13:42 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/07/03 11:00:20 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	int		nb;

	if (!str)
		return (0);
	i = 0;
	sign = 1;
	nb = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (sign * nb);
}

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

void	error(void)
{
	write(2, "ERROR\n", 6);
	exit(1);
}
