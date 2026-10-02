/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:25:46 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/20 10:08:30 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dot(char **args)
{
	if (!args || !args[1] || args[1][0] == '\0')
	{
		ft_puterr("minishell: .: filename argument required\n");
		ft_puterr(".: usage: . filename [arguments]\n");
		return (2);
	}
	return (2);
}
