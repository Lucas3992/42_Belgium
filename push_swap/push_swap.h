/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:25:54 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/06/25 10:10:25 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include <stddef.h>

typedef struct s_node
{
	struct s_node	*prev;
	struct s_node	*next;
	int				value;
	int				index;
}					t_node;

typedef struct s_stack
{
	struct s_node	*first;
	struct s_node	*last;
	int				size;
}					t_stack;

int		find_min_value(t_stack *a);
int		find_position_min_value(t_stack *a);
void	index_stack(t_stack *a);
int		find_next_chunk_index(t_stack *a, int min, int max);
void	all_chunks_to_b(t_stack *a, t_stack *b, int min, int max);
void	fill_a_from_b(t_stack *a, t_stack *b);

int		calculate_chunk_start(int i, int chunk_size, int rest);
int		calculate_chunk_end(int i, int chunk_size, int rest, int start);
int		calculate_chunk_range(int start, int end);

void	free_stack(t_stack *stack);
void	free_split(char **split);
void	return_error(int *array, char **split);
void	easy_exit(t_stack *a, t_stack *b);

int		has_no_dup(int *array, int size);
int		validated_number(char *nb);
int		is_within_int_limits(char *nb);

t_stack	*init_stack(void);
t_node	*create_node(int value);
void	add_back(t_stack *stack, t_node *new);

t_stack	*build_stack(int *array, int size);

t_stack	*parse_args(int argc, char **argv);

void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);
void	ra(t_stack *a);
void	rb(t_stack *b);
void	rr(t_stack *a, t_stack *b);
void	rra(t_stack *a);
void	rrb(t_stack *b);
void	rrr(t_stack *a, t_stack *b);
void	sa(t_stack *a);
void	sb(t_stack *b);
void	ss(t_stack *a, t_stack *b);
void	sort_two(t_stack *a);
void	sort_three(t_stack *a);

#endif