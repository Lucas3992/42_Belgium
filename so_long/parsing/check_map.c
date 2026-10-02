/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:02:53 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/07/16 13:53:07 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_map_dimensions(int fd, int *width, int *height, t_game *game)
{
	char	*line;

	*height = 0;
	line = get_next_line(fd);
	if (!line)
		explicit_error_and_exit("Empty map", game);
	while (line)
	{
		replace_nl(line);
		if (*height == 0)
			*width = ft_strlen(line);
		if (ft_strlen(line) != *width)
		{
			free(line);
			explicit_error_and_exit("The map must be a rectangle", game);
		}
		(*height)++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (*height < 3 || *width < 3)
		explicit_error_and_exit("Map must be at least 3x3", game);
}

//on lappellera apres get_map_dimension qui elle check, leak a check
static char	**read_and_fill_map(int fd, int height, t_game *game)
{
	char	**map;
	char	*line;
	int		i;

	map = malloc((height +1) * sizeof(char *));
	if (!map)
		explicit_error_and_exit("Malloc failed", game);
	i = 0;
	while (i < height)
	{
		line = get_next_line(fd);
		replace_nl(line);
		map[i] = ft_strdup(line);
		free(line);
		if (!map[i])
			explicit_error_and_exit("Malloc failed", game);
		i++;
	}
	map[i] = NULL;
	get_next_line(-19);
	close(fd);
	return (map);
}

static int	check_walls(char **map, int width, int height)
{
	int	x;
	int	y;

	if (!map)
		return (0);
	x = 0;
	while (x < width)
	{
		if (map[0][x] != '1' || map[height -1][x] != '1')
			return (0);
		x++;
	}
	y = 0;
	while (y < height)
	{
		if (map[y][0] != '1' || map[y][width -1] != '1')
			return (0);
		y++;
	}
	return (1);
}

void	parse_map(char *mapname, t_game *game)
{
	int	fd;

	fd = open(mapname, O_RDONLY);
	if (fd < 0)
		explicit_error_and_exit("Wrong map file", game);
	check_map_dimensions(fd, &game->map.x, &game->map.y, game);
	close(fd);
	fd = open(mapname, O_RDONLY);
	if (fd < 0)
		explicit_error_and_exit("Wrong map file", game);
	game->map.grid = read_and_fill_map(fd, game->map.y, game);
	close(fd);
	if (!check_walls(game->map.grid, game->map.x, game->map.y))
		explicit_error_and_exit("Map must be surrounded by walls", game);
	is_valid_pec(game->map.grid, game);
	game_is_playable(game->map, game);
}
