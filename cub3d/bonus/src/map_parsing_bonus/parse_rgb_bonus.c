/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:58:29 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 10:58:30 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_spaces(char *str)
{
	while (*str && is_space(*str))
		str++;
	return (str);
}

static int	parse_single_value(char **str)
{
	int		value;
	char	*temp;

	*str = skip_spaces(*str);
	if (!ft_isdigit(**str))
		return (-1);
	temp = *str;
	value = ft_atoi(*str);
	while (**str && ft_isdigit(**str))
		(*str)++;
	if (*str == temp)
		return (-1);
	return (value);
}

static int	expect_comma(char **str)
{
	*str = skip_spaces(*str);
	if (**str != ',')
		return (1);
	(*str)++;
	return (0);
}

int	parse_rgb(char *str, t_color *plane)
{
	int	r;
	int	g;
	int	b;

	r = parse_single_value(&str);
	if (r < 0 || expect_comma(&str))
		return (1);
	g = parse_single_value(&str);
	if (g < 0 || expect_comma(&str))
		return (1);
	b = parse_single_value(&str);
	if (b < 0)
		return (1);
	str = skip_spaces(str);
	if (*str != '\0' && *str != '\n')
		return (1);
	if (r > 255 || g > 255 || b > 255)
		return (1);
	plane->r = r;
	plane->g = g;
	plane->b = b;
	return (0);
}
