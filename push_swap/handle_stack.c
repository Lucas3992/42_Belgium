/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:18:34 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/06/20 16:00:57 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*init_stack(void)
{
	t_stack	*new_stack;

	new_stack = malloc(sizeof(t_stack));
	if (!new_stack)
		return (NULL);
	new_stack->first = NULL;
	new_stack->last = NULL;
	new_stack->size = 0;
	return (new_stack);
}

t_node	*create_node(int value)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->value = value;
	new_node->index = -1;
	return (new_node);
}

void	add_back(t_stack *stack, t_node *new)
{
	if (!stack)
		return ;
	if (stack->first == NULL)
	{
		stack->first = new;
		stack->last = new;
	}
	else
	{
		stack->last->next = new;
		new->prev = stack->last;
		stack->last = new;
	}
	stack->size++;
}

t_stack	*build_stack(int *array, int size)
{
	t_stack	*stack;
	t_node	*new;
	int		i;

	stack = init_stack();
	if (!stack)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new = create_node(array[i]);
		if (!new)
		{
			free_stack(stack);
			return (NULL);
		}
		add_back(stack, new);
		i++;
	}
	return (stack);
}
