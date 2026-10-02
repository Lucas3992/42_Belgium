/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:56:25 by dcasiell          #+#    #+#             */
/*   Updated: 2025/12/18 11:23:01 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	flood_fill_from_player(char **map, t_point start, t_map *og)
{
	t_flood_node	*queue;
	t_point			p;

	queue = NULL;
	if (!map || !map[start.y])
		return ;
	add_to_queue(&queue, start.y, start.x);
	map[start.y][start.x] = 'V';
	while (queue)
	{
		p.x = queue->x;
		p.y = queue->y;
		if (!map[p.y] || map[p.y][p.x] == '1')
		{
			remove_from_queue(&queue);
			continue ;
		}
		explore_neighbors(p, map, &queue, og);
		remove_from_queue(&queue);
	}
}

static int	is_leak(char **map, t_map *og, int y, int x)
{
	int	dx[4];
	int	dy[4];
	int	i;

	fill_dx_dy(dx, dy);
	i = 0;
	while (i < 4)
	{
		if ((x + dx[i]) < 0 || (y + dy[i]) < 0 || (y + dy[i]) >= og->height
			|| !map[(y + dy[i])])
			return (1);
		if ((x + dx[i]) >= (int)ft_strlen(map[(y + dy[i])]))
			return (1);
		if (is_null_or_space(map, og, y + dy[i], x + dx[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	check_no_leaks(char **map, t_map *og)
{
	int	y;
	int	x;

	y = 0;
	while (y < og->height)
	{
		if (!map)
			return (0);
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'V')
			{
				if (is_leak(map, og, y, x))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	is_map_closed(t_map *map)
{
	char	**map_copy;
	t_point	start;
	int		result;

	if (!check_edges_are_walls(map))
		return (0);
	start.x = map->data->player.x;
	start.y = map->data->player.y;
	map_copy = copy_map_grid(map);
	if (!map_copy)
		return (0);
	flood_fill_from_player(map_copy, start, map);
	result = check_no_leaks(map_copy, map);
	free_array(map_copy);
	return (result);
}

char	**copy_map_grid(t_map *og_map)
{
	char	**copy;
	int		y;

	copy = malloc((og_map->height + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	y = 0;
	while (y < og_map->height)
	{
		copy[y] = ft_strdup(og_map->grid[y]);
		if (!copy[y])
		{
			free_array(copy);
			return (NULL);
		}
		y++;
	}
	copy[og_map->height] = NULL;
	return (copy);
}
