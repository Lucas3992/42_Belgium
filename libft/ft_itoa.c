/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:12:15 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/04/16 13:49:47 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*number;
	int		len;
	long	nb;

	nb = n;
	len = count_digits(nb);
	number = malloc(len +1);
	if (!number)
		return (NULL);
	number[len] = '\0';
	if (nb == 0)
		number[0] = '0';
	if (nb < 0)
	{
		number[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		len--;
		number[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (number);
}
