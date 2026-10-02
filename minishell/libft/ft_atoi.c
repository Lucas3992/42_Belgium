/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:47:19 by dcasiell          #+#    #+#             */
/*   Updated: 2025/10/13 09:36:40 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == 32)
		i++;
	if ((nptr[i] == '+' || nptr[i] == '-')
		&& (nptr[i +1] >= '0' && nptr[i +1] <= '9'))
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	else if (nptr[i] == '+' || nptr[i] == '-')
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}
