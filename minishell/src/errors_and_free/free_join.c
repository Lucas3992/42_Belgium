/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:42:01 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:42:02 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2, int free_s1, int free_s2)
{
	char	*out;

	out = ft_strjoin(s1, s2);
	if (free_s1 && s1)
		free(s1);
	if (free_s2 && s2)
		free(s2);
	return (out);
}
