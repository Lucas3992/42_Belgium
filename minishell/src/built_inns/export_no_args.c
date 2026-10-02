/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:40:57 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:40:58 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_var	**build_export(t_shell *ms, int *size)
{
	t_var	**array;
	t_var	*temp;
	int		i;

	*size = ft_lstsize(ms->env);
	array = malloc((*size + 1) * sizeof(*array));
	if (!array)
		return (NULL);
	i = 0;
	temp = ms->env;
	while (temp)
	{
		array[i] = temp;
		i++;
		temp = temp->next;
	}
	array[i] = NULL;
	return (array);
}

static void	node_swap(t_var **a, t_var **b)
{
	t_var	*swap;

	swap = *a;
	*a = *b;
	*b = swap;
}

static void	print_escaped(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\\')
			printf("\\");
		printf("%c", str[i]);
		i++;
	}
}

static void	print_exp_no_arg(t_var **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (ft_strcmp(arr[i]->key, "_") == 0)
		{
			i++;
			continue ;
		}
		printf("declare -x %s", arr[i]->key);
		if (!arr[i]->has_eq)
			printf("\n");
		else if (arr[i]->value == NULL || arr[i]->value[0] == '\0')
			printf("=\"\"\n");
		else
		{
			printf("=\"");
			print_escaped(arr[i]->value);
			printf("\"\n");
		}
		i++;
	}
}

int	export_no_args(t_shell *ms)
{
	int		i;
	int		check;
	t_var	**arr;
	int		size;

	arr = build_export(ms, &size);
	check = 1;
	while (check)
	{
		i = 0;
		check = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(arr[i]->key, arr[i + 1]->key) > 0)
			{
				node_swap(&arr[i], &arr[i + 1]);
				check = 1;
			}
			i++;
		}
	}
	print_exp_no_arg(arr, size);
	free(arr);
	return (0);
}
