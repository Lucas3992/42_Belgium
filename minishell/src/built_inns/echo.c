/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:40:35 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:40:36 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_n(const char *str)
{
	int	j;

	if (!str || str[0] != '-')
		return (false);
	j = 1;
	if (str[j] == '\0')
		return (false);
	while (str[j] == 'n')
		j++;
	return (str[j] == '\0');
}

int	echo(char **args)
{
	int		i;
	bool	n;

	i = 1;
	n = true;
	while (args[i] && is_n(args[i]))
	{
		n = false;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n)
		printf("\n");
	return (0);
}
