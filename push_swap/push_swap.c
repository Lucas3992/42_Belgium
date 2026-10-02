/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:48:57 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/06/25 10:38:42 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
/* 
void	print_stack(t_stack *stack, char *name)
{
	t_node	*current;

	ft_printf("%s: ", name);
	current = stack->first;
	while (current)
	{
		ft_printf("%d ", current->value);
		current = current->next;
	}
	ft_printf("\n");
} */

static int	is_sorted(t_stack *stack)
{
	t_node	*tmp;

	if (!stack || stack->first->next == NULL)
		return (1);
	tmp = stack->first;
	while (tmp->next)
	{
		if (tmp->value >= tmp->next->value)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

static void	easy_sort(t_stack *a, t_stack *b)
{
	int	position;
	int	rotations;

	while (a->size > 3)
	{
		position = find_position_min_value(a);
		if (position <= a->size / 2)
		{
			while (position-- > 0)
				ra(a);
		}
		else
		{
			rotations = a->size - position;
			while (rotations-- > 0)
				rra(a);
		}
		pb(a, b);
	}
	sort_three(a);
	while (b->size > 0)
		pa(a, b);
}

static void	sort(t_stack *a, t_stack *b)
{
	if (is_sorted(a))
		return ;
	if (a->size == 2)
		sort_two(a);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size < 10)
		easy_sort(a, b);
	else
	{
		index_stack(a);
		all_chunks_to_b(a, b, 0, 0);
		fill_a_from_b(a, b);
	}
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc < 2)
		return (0);
	a = parse_args(argc, argv);
	b = init_stack();
	if (!a || !b)
		easy_exit(a, b);
	sort(a, b);
	free_stack(a);
	free_stack(b);
	return (0);
}
