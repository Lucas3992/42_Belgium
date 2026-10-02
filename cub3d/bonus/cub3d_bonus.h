/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:57:39 by dcasiell          #+#    #+#             */
/*   Updated: 2025/12/01 13:58:04 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H
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
# include <time.h>

typedef struct s_map		t_map;
typedef struct s_map_config	t_map_config;

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

typedef struct s_enemy_proj
{
	double		transform_x;
	double		transform_y;
	int			screen_x;
	int			start_x;
	int			end_x;
	int			start_y;
	int			end_y;
	int			w;
	int			h;
	t_txt_addr	*tex;
}	t_enemy_proj;

typedef struct s_hit_ctx
{
	int		cx;
	int		cy;
	double	best_dist;
	int		best_index;
}	t_hit_ctx;

typedef struct s_hit_pixel
{
	int				sprite_w;
	int				sprite_h;
	double			ratio_x;
	double			ratio_y;
	int				tex_x;
	int				tex_y;
	char			*src;
	unsigned int	color;
}	t_hit_pixel;

typedef struct s_rc
{
	double	camera_x;	// position horizontale du rayon dans l'écran (-1 à +1)
	double	ray_dir_x;	// direction du rayon en X
	double	ray_dir_y;	// direction du rayon en Y
	double	side_dist_x;// distance jusqu'à la prochaine frontière verticale 
	double	side_dist_y;// distance jusqu'à la prochaine frontière horizontale
	double	delta_dist_x;// distance pour traverser 1 case en X le long du rayon
	double	delta_dist_y;// distance pour traverser 1 case en Y le long du rayon
	double	perp_wall_dist;// distance perpendiculaire jusqu'au mur 
	int		map_x;			// case X actuelle du rayon dans la grille
	int		map_y;			// case Y actuelle du rayon dans la grille
	int		step_x;			// direction du pas en X (-1 = gauche, +1 = droite)
	int		step_y;			// direction du pas en Y (-1 = haut, +1 = bas)
	int		hit;			// 1 si un mur est touché, 0 sinon
	int		side;			// 0 = mur vertical, 1 = mur horizontal
	int		line_height;	// hauteur de la ligne murale à dessiner à l'écran
	int		draw_start;		// début (top) de la ligne murale
	int		draw_end;		// fin (bottom) de la ligne murale
}	t_rc;

typedef struct s_weapon
{
	int		damage;
	void	*img_idle;
	void	*img_fire;
	char	*addr_idle;
	char	*addr_fire;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
	int		is_firing;
	int		fire_frame;
}	t_weapon;

typedef struct s_weapon_pos
{
	int	x_right;
	int	x_left;
	int	y;
}	t_weapon_pos;

typedef struct s_weapon_draw
{
	t_weapon	*wp;
	char		*addr;
	int			start_x;
	int			start_y;
}	t_weapon_draw;

typedef struct s_enemy
{
	double	x;
	double	y;
	double	dist;
	int		hp;
	int		is_dead;
}	t_enemy;

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
	t_weapon	*weapon_right;
	t_weapon	*weapon_left;
	int			last_weapon;
	long long	last_fire_time;
	int			fire_rate;
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
	char	*enemy;
	int		width;
	int		height;
	t_color	floor;
	t_color	ceiling;
}	t_textures;

typedef struct s_txt_ptr
{
	t_txt_addr	north;
	t_txt_addr	south;
	t_txt_addr	west;
	t_txt_addr	east;
	t_txt_addr	enemy;
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
	int		enemy_color;
}	t_minimap;

typedef struct s_sprite
{
	double	sprite_x;
	double	sprite_y;
	double	transform_x;
	double	transform_y;
	int		screen_x;
	int		sprite_h;
	int		sprite_w;
	int		draw_start_x;
	int		draw_start_y;
	int		draw_end_x;
	int		draw_end_y;
}	t_sprite;

typedef struct s_sprite_draw
{
	char			*src;
	double			ratio_y;
	int				y;
	int				tex_x;
	int				tex_y;
	int				bypp;
	t_txt_addr		*tex;
	unsigned int	color;
}	t_sprite_draw;

typedef struct s_hit_check
{
	t_hit_ctx		*h;
	t_enemy			*en;
	t_enemy_proj	*p;
	int				index;
}	t_hit_check;

typedef struct s_game
{
	double			*z_buf;
	int				nb_enemy;
	int				hitmarker_timer;
	int				sound_level;
	t_frame			*buffer;
	t_keys			keys;
	t_window		win;
	t_map			map;
	t_txt_ptr		textures;
	t_character		player;
	t_minimap		minimap;
	t_enemy			*enemies;
	pid_t			music_id;
}	t_game;

//		MAIN
int		init_game(t_game *cub, char *map_path);
int		game_loop(t_game *cub);

//		MAP
int		map_init(char *map_name, t_game *cub, t_map_config *data);
void	add_to_queue(t_flood_node **queue, int y, int x);
void	remove_from_queue(t_flood_node **queue);
void	explore_neighbors(t_point p, char **map, t_flood_node **q, t_map *og);
void	fill_dx_dy(int dx[4], int dy[4]);
int		is_map_closed(t_map *map);
char	**copy_map_grid(t_map *og_map);
int		check_cub(char *map_name);
int		read_map(char *map_path, t_map_config *map_data);
int		get_textures(int fd, t_map_config *data);
void	fill_cardinal(char *cardinal[7]);
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
char	get_map_cell(t_game *cub, int x, int y);
char	*trim_leading_spaces(char *line);
char	*read_valid_line(int fd, int *map_started);
int		normalize_map_lines(t_map *map, int y);

//		MINIMAP
void	init_minimap(t_game *cub);
void	draw_minimap(t_game *cub);
void	draw_minimap_player(t_game *cub);
void	draw_minimap_grid(t_game *cub);
void	draw_minimap_tile(t_game *cub, int map_x, int map_y);
void	draw_square(t_game *cub, int x, int y, int color);
void	draw_player_dot(t_game *cub, int center_x, int center_y);
void	put_pixel_safe(t_game *cub, int x, int y, int color);
void	my_mlx_pixel_put(t_frame *buffer, int x, int y, int color);
char	get_map_cell_display(t_game *cub, int x, int y);

//		UTILITIES
double	now_in_seconds(void);
int		is_space(char c);
int		ft_isspace(char *str);
int		is_null_or_space(char **map, t_map *og, int y, int x);
void	assign_directions(char pov, t_character *player);
void	display_fps(t_game *cub, double delta);

//		FREE
void	free_array(char **array);
void	free_win(t_window *win);
void	free_game(t_game *cub);
void	clean_explicit_exit(t_game *cub, int ret, char *msg);
void	free_textures(t_textures *textures);
void	free_texture_images(t_window *win, t_txt_ptr *textures);
void	free_map_data(t_map_config *data);
int		free_map_data_and_fail(t_game *cub, t_map_config *map_data);

//		ERROR

//		WINDOW
int		init_window(t_window *win);
int		render_scene(t_game *cub);
t_frame	*init_buffer(t_game *game, t_map_config *data);
void	render_background(t_frame *buf, unsigned int s_clr, unsigned int f_clr);
void	ultimate_rc(t_game *cub);
void	init_rc(t_rc *rc, t_game *cub, int x);
void	compute_wall_height(t_rc *rc, t_game *cub);
void	draw_crosshair(t_frame *buf, unsigned int color);
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

//		BONUS
int		init_enemies(t_game *cub);
int		compute_enemy_transform(t_game *cub, t_enemy *en, t_sprite *sp);
int		is_transparent(unsigned int color);
int		build_enemy_proj(t_game *cub, t_enemy *en, t_enemy_proj *p);
int		ft_math_random(int min, int max);
int		get_pa_volume(int percent);
void	render_enemies(t_game *cub);
void	compute_sprite_bounds(t_game *cub, t_sprite *sp);
void	update_enemy_distances(t_game *cub);
void	sort_enemies_by_distance(t_game *cub);
void	load_weapon(t_game *game, t_weapon *weapon,
			char *idle_path, char *fire_path);
void	draw_weapon(t_game *game);
void	fire_weapon(t_game *game);
void	init_weapon(t_game *game);
void	start_music(t_game *cub);
void	stop_music(t_game *cub);
void	free_weapon(t_game *game);
void	update_hitmarker(t_game *cub);
void	draw_hitmarker(t_frame *buf, unsigned int color);
void	render_hud(t_game *cub);
void	shoot(t_game *cub);
void	draw_minimap_enemies(t_game *cub);
void	update_score(t_game *cub);
void	display_score(t_game *cub);
char	*get_weapon_addr(t_weapon *weapon);
void	update_weapon_fire(t_weapon *weapon);
void	draw_weapon_image(t_game *game, t_weapon_draw *wd);
void	draw_weapon_row(t_game *game, t_weapon *wp,
			char *row_addr, t_point dst);
void	process_weapon_row(t_game *game, t_weapon_draw *wd, int y);
void	play_random_sound(t_game *cub);

#endif