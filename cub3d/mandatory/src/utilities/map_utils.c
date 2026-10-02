/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:55:55 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 11:26:02 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == '\t'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '\n');
}

void	remove_newline(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\r')
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
}

char	*trim_leading_spaces(char *line)
{
	char	*trimmed;
	int		i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (i > 0)
	{
		trimmed = ft_strdup(line + i);
		free(line);
		return (trimmed);
	}
	return (line);
}
