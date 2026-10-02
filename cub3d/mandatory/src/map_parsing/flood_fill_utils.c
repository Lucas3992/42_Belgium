/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:56:30 by dcasiell          #+#    #+#             */
/*   Updated: 2025/12/01 13:57:11 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	fill_dx_dy(int dx[4], int dy[4])
{
	if (!dx || !dy)
		return (1);
	dx[0] = 0;
	dx[1] = 0;
	dx[2] = 1;
	dx[3] = -1;
	dy[0] = 1;
	dy[1] = -1;
	dy[2] = 0;
	dy[3] = 0;
	return (0);
}

void	explore_neighbors(t_point p, char **map, t_flood_node **q, t_map *og)
{
	int	dx[4];
	int	dy[4];
	int	i;
	int	nx;
	int	ny;

	if (!map || !q || !og)
		return ;
	fill_dx_dy(dx, dy);
	i = 0;
	while (i < 4)
	{
		nx = p.x + dx[i];
		ny = p.y + dy[i];
		if (ny >= 0 && ny < og->height && nx >= 0
			&& nx < (int)ft_strlen(map[ny])
			&& map[ny] && map[ny][nx] && is_walkable(map[ny][nx]))
		{
			map[ny][nx] = 'V';
			add_to_queue(q, ny, nx);
		}
		i++;
	}
}

void	add_to_queue(t_flood_node **queue, int y, int x)
{
	t_flood_node	*new;
	t_flood_node	*tmp;

	new = malloc(sizeof(t_flood_node));
	if (!new)
		return ;
	new->x = x;
	new->y = y;
	new->next = NULL;
	if (!*queue)
		*queue = new;
	else
	{
		tmp = *queue;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	remove_from_queue(t_flood_node **queue)
{
	t_flood_node	*tmp;

	if (!queue || !*queue)
		return ;
	tmp = *queue;
	*queue = (*queue)->next;
	free(tmp);
}
