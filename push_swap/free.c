/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:16:19 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/06/20 14:08:29 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_stack(t_stack *stack)
{
	t_node	*current_node;
	t_node	*next_node;

	if (!stack)
		return ;
	current_node = stack->first;
	while (current_node)
	{
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
	free(stack);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	return_error(int *array, char **split)
{
	if (array)
		free(array);
	if (split)
		free_split(split);
	write(2, "Error\n", 6);
	exit (1);
}

void	easy_exit(t_stack *a, t_stack *b)
{
	if (a)
		free_stack(a);
	if (b)
		free_stack(b);
	write(2, "Error\n", 6);
	exit (1);
}
