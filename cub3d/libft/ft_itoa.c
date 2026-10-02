/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:53:33 by dcasiell          #+#    #+#             */
/*   Updated: 2025/10/13 09:37:37 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*likeptnumbr(int n, char *str, int size)
{
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	str[size] = '\0';
	size--;
	while (n >= 10)
	{
		str[size] = n % 10 + '0';
		size--;
		n = n / 10;
	}
	str[size] = n % 10 + '0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*converted;
	int		size;
	int		tempn;

	tempn = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	size = 0;
	while (tempn != 0)
	{
		tempn = tempn / 10;
		size++;
	}
	if (n < 0)
		size++;
	converted = (char *) malloc ((size +1) * sizeof(char));
	if (!converted)
		return (NULL);
	converted = likeptnumbr(n, converted, size);
	return (converted);
}
