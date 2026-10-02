/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:58:41 by dcasiell          #+#    #+#             */
/*   Updated: 2025/12/01 13:49:14 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <string.h>
# include <math.h>
# include <stddef.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <stdbool.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_map		t_map;
typedef struct s_map_config	t_map_config;
typedef struct s_game		t_game;

typedef struct s_rc
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_rc;

typedef struct s_character
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rot_speed;
	int			hp;
	int			money;
	char		pov;
}	t_character;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_flood_node
{
	int					x;
	int					y;
	struct s_flood_node	*next;
}	t_flood_node;

struct s_map
{
	char			**grid;
	int				width;
	int				height;
	t_map_config	*data;
};

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		width;
	int		height;
	t_color	floor;
	t_color	ceiling;
}	t_textures;

typedef struct s_txt_addr
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_pp;
	int		line_len;
	int		endian;
}	t_txt_addr;

typedef struct s_txt_ptr
{
	t_txt_addr	north;
	t_txt_addr	south;
	t_txt_addr	west;
	t_txt_addr	east;
}	t_txt_ptr;

typedef struct s_txt_calc
{
	double	step;
	double	tex_pos;
	int		tex_x;
}	t_txt_calc;

struct s_map_config
{
	t_textures	textures;
	t_map		map;
	t_character	player;
	char		*map_path;
	t_game		*game;
};

typedef struct s_window
{
	int		width;
	int		height;
	void	*mlx;
	void	*win;
}	t_window;

typedef struct s_keys
{
	int	up;
	int	left;
	int	down;
	int	right;
	int	esc;
	int	l_click;
	int	a_left;
	int	a_right;
	int	space;
	int	sprint;
	int	toggle_sprint;
}	t_keys;

typedef struct s_frame
{
	void	*img;
	char	*address;
	int		bits_pp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	int		sky_argb;
	int		floor_argb;
}	t_frame;

typedef struct s_minimap
{
	int		size;
	int		tile_size;
	int		player_size;
	int		x_map;
	int		y_map;
	int		wall_color;
	int		floor_color;
	int		player_color;
}	t_minimap;

struct s_game
{
	t_frame			*buffer;
	t_keys			keys;
	t_window		win;
	t_map			map;
	t_txt_ptr		textures;
	t_character		player;
	t_minimap		minimap;
	pid_t			music_id;
};

//		MAIN
int		init_game(t_game *cub, char *map_path);
int		game_loop(t_game *cub);

//		MAP
int		map_init(char *map_name, t_game *cub, t_map_config *data);
void	add_to_queue(t_flood_node **queue, int y, int x);
void	remove_from_queue(t_flood_node **queue);
void	explore_neighbors(t_point p, char **map, t_flood_node **q, t_map *og);
int		fill_dx_dy(int dx[4], int dy[4]);
int		is_map_closed(t_map *map);
char	**copy_map_grid(t_map *og_map);
int		check_cub(char *map_name);
int		read_map(char *map_path, t_map_config *map_data);
int		get_textures(int fd, t_map_config *data);
void	fill_cardinal(char *cardinal[6]);
int		get_map(int fd, t_map *map, t_map_config *data);
int		parse_element(t_map_config *data, char *line, int index);
int		check_single_player(t_map *map);
int		check_valid_characters(t_map *map);
int		validate_map(t_map *map);
int		is_valid_xpm(char *path);
int		parse_rgb(char *str, t_color *plane);
int		check_txt_order(int fd);
int		is_map_char(char c);
void	remove_newline(char *str);
int		check_edges_are_walls(t_map *og);
int		is_walkable(char c);
int		check_all_walkable_visited(char **map_copy, t_map *og);
char	*trim_leading_spaces(char *line);
char	get_map_cell(t_game *cub, int x, int y);
char	*read_valid_line(int fd, int *map_started);
int		normalize_map_lines(t_map *map, int y);

//		UTILITIES
double	now_in_seconds(void);
int		is_space(char c);
int		ft_isspace(char *str);
int		is_null_or_space(char **map, t_map *og, int y, int x);
void	assign_directions(char pov, t_character *player);

//		FREE
void	free_array(char **array);
void	free_win(t_window *win);
void	free_game(t_game *cub);
void	clean_explicit_exit(t_game *cub, int ret, char *msg);
void	free_textures(t_textures *textures);
void	free_texture_images(t_window *win, t_txt_ptr *textures);
void	free_map_data(t_map_config *data);
int		free_map_data_and_fail(t_game *cub, t_map_config *map_data);

//		WINDOW
int		init_window(t_window *win);
int		render_scene(t_game *cub);
t_frame	*init_buffer(t_game *game, t_map_config *data);
void	render_background(t_frame *buf, unsigned int s_clr, unsigned int f_clr);
void	ultimate_rc(t_game *cub);
void	init_rc(t_rc *rc, t_game *cub, int x);
void	compute_wall_height(t_rc *rc, t_game *cub);
int		error_msg(char *msg);

//		PLAYER
int		init_player(t_game *cub);

//		TEXTURES
int		check_txt_order(int fd);
int		load_textures(t_window *win, t_txt_ptr *load, t_textures *path);
int		rgb_to_argb(t_color color);
int		text_addr(t_game *cub);
int		compute_tex_x(t_txt_addr *tex, t_rc *rc, double wall_x);
void	init_txt_calc(t_txt_calc *tc, t_rc *rc, t_game *cub, t_txt_addr *ta);
void	put_pixel(t_frame *buf, int x, int y, unsigned int color);
void	draw_wall_column(t_game *cub, t_rc *rc, int x);

//		MOVEMENTS
void	mov_plyr(t_game *cub, double dx, double dy);
void	rotate_player(t_game *cub, double angle);

//		HOOKS
int		handle_key_press(int key, t_game *cub);
int		handle_key_release(int key, t_game *cub);
int		mouse_quit(t_game *cub);
void	apply_inputs(t_game *cub, double delta);

#endif