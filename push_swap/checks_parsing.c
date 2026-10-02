/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:46:06 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/06/20 14:27:38 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	validated_number(char *nb)
{
	int	i;

	if (!nb || nb[0] == '\0')
		return (0);
	i = 0;
	if (nb[i] == '+' || nb[i] == '-')
		i++;
	while (nb[i])
	{
		if (!ft_isdigit(nb[i]))
			return (0);
		else
			i++;
	}
	return (1);
}

int	is_within_int_limits(char *nb)
{
	long long	nb_converted;

	if (!nb || nb[0] == '\0')
		return (0);
	nb_converted = ft_atol(nb);
	if (nb_converted < -2147483648 || nb_converted > 2147483647)
		return (0);
	return (1);
}

int	has_no_dup(int *array, int size)
{
	int	i;
	int	j;

	if (!array)
		return (0);
	i = 0;
	while (i < size)
	{
		j = i +1;
		while (j < size)
		{
			if (array[i] == array [j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
