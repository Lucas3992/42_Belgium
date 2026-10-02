/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basics.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:05:24 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/07/22 09:37:06 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	i;

	if (!str)
		return (write(1, "(null)", 6));
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr(int nb)
{
	unsigned int	n;
	char			chiffre;
	int				count;

	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	count = 0;
	if (nb < 0)
	{
		count = count + write(1, "-", 1);
		n = (unsigned int)(-nb);
	}
	else
		n = (unsigned int)nb;
	if (n >= 10)
		count = count + ft_putnbr(n / 10);
	chiffre = n % 10 + '0';
	count = count + write(1, &chiffre, 1);
	return (count);
}

int	ft_unputnbr(unsigned int n)
{
	char	c;
	int		count;

	count = 0;
	if (n > 9)
		count = count + ft_unputnbr(n / 10);
	c = n % 10 + '0';
	count = count + write(1, &c, 1);
	return (count);
}

int	ft_hex_putnbr(unsigned int n, char x)
{
	char	*hex;
	char	c;
	int		count;

	count = 0;
	if (n == 0)
		return (write(1, "0", 1));
	if (x == 'x')
		hex = "0123456789abcdef";
	else if (x == 'X')
		hex = "0123456789ABCDEF";
	else
		return (0);
	if (n > 15)
		count = count + ft_hex_putnbr(n / 16, x);
	c = hex[n % 16];
	count = count + write(1, &c, 1);
	return (count);
}
