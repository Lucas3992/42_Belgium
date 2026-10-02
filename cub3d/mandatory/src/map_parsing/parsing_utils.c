/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:56:16 by dcasiell          #+#    #+#             */
/*   Updated: 2025/11/27 11:27:46 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**realloc_grid(char **old_grid, int old_size, int new_capacity)
{
	char	**new_grid;
	int		i;

	new_grid = malloc(new_capacity * sizeof(char *));
	if (!new_grid)
		return (NULL);
	i = 0;
	while (i < old_size)
	{
		new_grid[i] = old_grid[i];
		i++;
	}
	while (i < new_capacity)
	{
		new_grid[i] = NULL;
		i++;
	}
	free(old_grid);
	return (new_grid);
}

static char	**allocate_and_read(int fd, int *height, char **grid, int capacity)
{
	char	**new_grid;
	int		i;
	int		map_started;

	i = 0;
	map_started = 0;
	while (1)
	{
		if (i >= capacity - 1)
		{
			capacity *= 2;
			new_grid = realloc_grid(grid, i, capacity);
			if (!new_grid)
				return (free_array(grid), NULL);
			grid = new_grid;
		}
		grid[i] = read_valid_line(fd, &map_started);
		if (!grid[i])
			break ;
		i++;
	}
	grid[i] = NULL;
	*height = i;
	return (grid);
}

static int	get_max_width(char **grid, int height)
{
	int	max;
	int	len;
	int	i;

	max = 0;
	i = 0;
	while (i < height)
	{
		len = ft_strlen(grid[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

int	get_map(int fd, t_map *map, t_map_config *data)
{
	char	**grid;
	int		capacity;
	int		i;

	i = 0;
	capacity = 20;
	grid = malloc(capacity * sizeof(char *));
	if (!grid)
		return (1);
	while (i < capacity)
	{
		grid[i] = NULL;
		i++;
	}
	grid = allocate_and_read(fd, &map->height, grid, capacity);
	if (!grid || map->height == 0)
	{
		if (grid)
			free_array(grid);
		return (1);
	}
	map->grid = grid;
	map->width = get_max_width(map->grid, map->height);
	map->data = data;
	return (0);
}
