/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrhex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:01:35 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/05/06 13:54:03 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptrhex(unsigned long n)
{
	char	*hex;
	char	c;
	int		count;

	count = 0;
	if (n == 0)
		return (write(1, "0", 1));
	hex = "0123456789abcdef";
	if (n > 15)
		count = count + ft_ptrhex(n / 16);
	c = hex[n % 16];
	count = count + write(1, &c, 1);
	return (count);
}
