/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:47:31 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 14:40:02 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_token(t_token **first, t_token *prev, t_token *current)
{
	if (first == NULL)
		return ;
	if (*first == NULL)
		return ;
	if (current == NULL)
		return ;
	if (prev == NULL)
		*first = current->next;
	else
		prev->next = current->next;
	if (current->value != NULL)
		free(current->value);
	if (current->raw != NULL)
		free(current->raw);
	free(current);
}
