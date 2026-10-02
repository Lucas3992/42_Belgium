/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:44:40 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/06/24 10:45:01 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_strings(char **split)
{
	int	i;

	if (!split)
		return (0);
	i = 0;
	while (split[i])
		i++;
	return (i);
}

static int	count_all_numbers_in_args(int argc, char **argv)
{
	int		i;
	int		total_splits;
	char	**split;

	i = 1;
	total_splits = 0;
	while (i < argc)
	{
		split = ft_split(argv[i], ' ');
		if (!split || count_strings(split) == 0)
		{
			free_split(split);
			return (-1);
		}
		total_splits = total_splits + count_strings(split);
		if (total_splits <= 0)
			return_error(NULL, split);
		free_split(split);
		i++;
	}
	return (total_splits);
}

static int	safe_str_to_int(char *str, int *dest)
{
	if (!str)
		return (0);
	if (!validated_number(str) || !is_within_int_limits(str))
		return (0);
	else
	{
		*dest = ft_atol(str);
		return (1);
	}
	return (0);
}

static int	fill_array_with_splitted_args(int *array, int argc, char **argv)
{
	int		i;
	int		j;
	int		k;
	char	**split;

	i = 1;
	k = 0;
	while (i < argc)
	{
		split = ft_split(argv[i], ' ');
		if (!split)
			return (0);
		j = 0;
		while (split[j])
		{
			if (!safe_str_to_int(split[j], &array[k]))
				return (free_split(split), 0);
			j++;
			k++;
		}
		free_split(split);
		i++;
	}
	return (1);
}

t_stack	*parse_args(int argc, char **argv)
{
	int		size;
	int		*array;
	t_stack	*a;

	size = count_all_numbers_in_args(argc, argv);
	if (size <= 0)
		return_error(NULL, NULL);
	array = malloc(size * sizeof(int));
	if (!array)
		return (NULL);
	if (!fill_array_with_splitted_args(array, argc, argv))
		return_error(array, NULL);
	if (!has_no_dup(array, size))
		return_error(array, NULL);
	a = build_stack(array, size);
	free(array);
	return (a);
}
