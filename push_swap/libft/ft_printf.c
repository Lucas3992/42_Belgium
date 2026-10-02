/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:12:20 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/05/20 11:16:27 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	transform(va_list argz, char type)
{
	void	*ptr;

	if (type == 'c')
		return (ft_putchar((char)va_arg(argz, int)));
	else if (type == 's')
		return (ft_putstr((char *)va_arg(argz, char *)));
	else if (type == 'p')
	{
		ptr = va_arg(argz, void *);
		if (!ptr)
			return (write(1, "(nil)", 5));
		return (write (1, "0x", 2)
			+ ft_ptrhex((unsigned long)ptr));
	}
	else if (type == 'd' || type == 'i')
		return (ft_putnbr(va_arg(argz, int)));
	else if (type == 'u')
		return (ft_unputnbr(va_arg(argz, unsigned int)));
	else if (type == 'x')
		return (ft_hex_putnbr(va_arg(argz, unsigned int), type));
	else if (type == 'X')
		return (ft_hex_putnbr(va_arg(argz, unsigned int), type));
	else if (type == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *form, ...)
{
	va_list	args;
	int		i;
	int		count;

	if (!form)
		return (-1);
	va_start(args, form);
	i = 0;
	count = 0;
	while (form[i])
	{
		if (form[i] == '%' && form[i +1])
		{
			count = count + transform(args, form[i +1]);
			i++;
		}
		else
		{
			write(1, &form[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
/* 
#include <limits.h>

int main ()
{
	ft_printf("%c %c ", '%', 'c');
	printf("%c %c\n", '%', 'c');

	ft_printf("%s", "coucou les bib0u$ ", "tsb il ne va pas imprimer ca");
	printf("%s\n", "coucou les bib0u$ ");
	ft_printf("%s", "");
	printf("%s", "");
	
	ft_printf("%d ", 19);
	printf("%d\n", 19);

	ft_printf("%i ", INT_MIN);
	printf("%i\n", INT_MIN);

	ft_printf("%u ",696969);
	printf("%u\n", 696969);
	ft_printf("%u ", -0);
	printf("%u\n", -0);


	ft_printf("%x ", 139257);
	printf("%x\n", 139257);

	ft_printf("%X ", 6969);
	printf("%X\n", 6969);

	ft_printf("%%%%%%%%%% ");
	printf("%%%%%%%%%%\n");

	ft_printf(" %p %p ", (void *)0, (void *)0);
	printf(" %p %p \n", (void *)0, (void *)0);
	ft_printf("%p ", (void *)-1234);
	printf("%p\n", (void *)-1234);
	
	ft_printf("coucou %s bibous ", "l3s");
	printf("coucou %s bibous\n", "l3s");
	return (0);
}
 */