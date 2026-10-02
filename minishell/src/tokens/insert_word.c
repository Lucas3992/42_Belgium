/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:47:28 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 14:48:02 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*insert_word(t_token *current, char *value)
{
	t_token	*new;

	new = create_word_token(value);
	if (!new)
		return (NULL);
	free(new->raw);
	new->raw = NULL;
	new->next = current->next;
	current->next = new;
	return (new);
}
