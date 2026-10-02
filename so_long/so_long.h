/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:12:00 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/07/16 14:29:16 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include "gnl/get_next_line.h"
# include "printf/ft_printf.h"

# ifndef TILE_SIZE
#  define TILE_SIZE 64
# endif

typedef struct s_move
{
	int	old_x;
	int	old_y;
	int	new_x;
	int	new_y;
}		t_move;

typedef struct s_map
{
	char	**grid;
	int		x;
	int		y;	
}			t_map;

typedef struct s_images
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*exit;
	void	*collectible;
}			t_images;

typedef struct s_game
{
	t_map		map;
	t_images	img;
	int			player_x;
	int			player_y;
	int			move_count;
	int			total_collectibles;
	int			remaining_collectibles;
	int			current_key;
	void		*mlx_init;
	void		*window;
}			t_game;

void	explicit_error_and_exit(const char *msg, t_game *game);
void	free_grid_and_exit(t_game *game, const char *msg);
void	free_grid(char **map);
void	free_game(t_game *game);

int		arguments_are_valid(int argc, char *argv, t_game *game);
void	replace_nl(char *str);
void	game_is_playable(t_map map, t_game *game);
void	is_valid_pec(char **map, t_game *game);
void	parse_map(char *mapname, t_game *game);

void	init_and_create_mlx_window(t_game *game);
void	charging_sprites(t_game *game);
void	display_map(t_game *game);

void	move_up(t_game *game);
void	move_down(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	swap_tiles(t_game *game, t_move m, char old_tile);
void	is_game_successfully_over(t_game *game, int x, int y);
/* 
void	slide_up(char **map, int *x, int *y);
void	slide_down(char **map, int *x, int *y);
void	slide_right(char **map, int *x, int *y);
void	slide_left(char **map, int *x, int *y);
void	check_slide(char **map, int *x, int *y);
int		player_dies(void);
void	print_map(t_map map);
*/

int		ft_strlen(const char *s);

void	*ft_bzero(void *s, size_t n);

char	*ft_strdup(char *s);

#endif