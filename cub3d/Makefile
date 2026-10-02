# ===================== Project =====================
NAME        := cub3d
NAME_BONUS  := cub3d_bonus
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g
CPPFLAGS    := -Imandatory -Ibonus -I$(LIBFT_DIR) -I$(MLX_DIR)

# ===================== Dirs ========================
SRC_DIR     := mandatory/src
BONUS_DIR   := bonus/src
OBJ_DIR     := obj
OBJ_BONUS   := obj_bonus
LIBFT_DIR   := libft
MLX_DIR     := minilibx-linux

# ===================== Libs ========================
LIBFT       := $(LIBFT_DIR)/libft.a
MLX_LIB     := $(MLX_DIR)/libmlx.a
LDLIBS      := $(LIBFT) $(MLX_LIB) -lX11 -lXext -lm -lz

# ===================== Sources Mandatory ===========
SRCS        := $(SRC_DIR)/main/main.c \
               $(SRC_DIR)/free/exit_game.c \
               $(SRC_DIR)/free/free_array.c \
               $(SRC_DIR)/free/free_textures.c \
               $(SRC_DIR)/init/init.c \
               $(SRC_DIR)/init/init_textures.c \
               $(SRC_DIR)/init/init_txt_calc.c \
               $(SRC_DIR)/keys/handle_keys.c \
               $(SRC_DIR)/keys/mouse.c \
               $(SRC_DIR)/keys/movements.c \
               $(SRC_DIR)/map_parsing/check_textures_helper.c \
               $(SRC_DIR)/map_parsing/flood_fill.c \
               $(SRC_DIR)/map_parsing/flood_fill_utils.c \
               $(SRC_DIR)/map_parsing/map_errors.c \
               $(SRC_DIR)/map_parsing/map_init.c \
               $(SRC_DIR)/map_parsing/parse_element.c \
               $(SRC_DIR)/map_parsing/parsing.c \
               $(SRC_DIR)/map_parsing/parsing_utils.c \
               $(SRC_DIR)/map_parsing/validate_map.c \
               $(SRC_DIR)/map_parsing/flood_walls.c \
               $(SRC_DIR)/map_parsing/parse_rgb.c \
               $(SRC_DIR)/map_parsing/read_valid_line.c \
               $(SRC_DIR)/map_parsing/fill_lines.c \
               $(SRC_DIR)/utilities/assign.c \
               $(SRC_DIR)/utilities/ft_isspace.c \
               $(SRC_DIR)/utilities/map_utils.c \
               $(SRC_DIR)/utilities/time.c \
               $(SRC_DIR)/utilities/null_or_space.c \
               $(SRC_DIR)/window/rc.c \
               $(SRC_DIR)/window/render.c \
               $(SRC_DIR)/window/wall.c \

# ===================== Sources Bonus ===============
SRCS_BONUS  := $(BONUS_DIR)/main_bonus/main_bonus.c \
               $(BONUS_DIR)/enemies_bonus/compute_enemies_bonus.c \
               $(BONUS_DIR)/enemies_bonus/enemies_bonus.c \
               $(BONUS_DIR)/enemies_bonus/fix_cops_bonus.c \
               $(BONUS_DIR)/enemies_bonus/render_enemies_bonus.c \
               $(BONUS_DIR)/free_bonus/exit_game_bonus.c \
               $(BONUS_DIR)/free_bonus/free_array_bonus.c \
               $(BONUS_DIR)/free_bonus/free_textures_bonus.c \
               $(BONUS_DIR)/free_bonus/free_weapon.c \
               $(BONUS_DIR)/init_bonus/init_bonus.c \
               $(BONUS_DIR)/init_bonus/init_textures_bonus.c \
               $(BONUS_DIR)/init_bonus/init_txt_calc_bonus.c \
               $(BONUS_DIR)/init_bonus/init_game_bonus.c \
               $(BONUS_DIR)/keys_bonus/handle_keys_bonus.c \
               $(BONUS_DIR)/keys_bonus/mouse_bonus.c \
               $(BONUS_DIR)/keys_bonus/movements_bonus.c \
               $(BONUS_DIR)/map_parsing_bonus/check_textures_helper_bonus.c \
               $(BONUS_DIR)/map_parsing_bonus/flood_fill_bonus.c \
               $(BONUS_DIR)/map_parsing_bonus/flood_fill_utils_bonus.c \
               $(BONUS_DIR)/map_parsing_bonus/map_errors_bonus.c \
               $(BONUS_DIR)/map_parsing_bonus/map_init_bonus.c \
               $(BONUS_DIR)/map_parsing_bonus/parse_element_bonus.c \
               $(BONUS_DIR)/map_parsing_bonus/parsing_bonus.c \
               $(BONUS_DIR)/map_parsing_bonus/parsing_utils_bonus.c \
               $(BONUS_DIR)/map_parsing_bonus/validate_map_bonus.c \
               $(BONUS_DIR)/map_parsing_bonus/flood_wall_bonus.c \
               $(BONUS_DIR)/map_parsing_bonus/parse_rgb_bonus.c \
               $(BONUS_DIR)/map_parsing_bonus/read_valid_line_bonus.c \
               $(BONUS_DIR)/map_parsing_bonus/fill_lines_bonus.c \
               $(BONUS_DIR)/minimap_bonus/minimap_bonus.c \
               $(BONUS_DIR)/minimap_bonus/minimap_helpers_bonus.c \
               $(BONUS_DIR)/minimap_bonus/draw_enemy_dot.c \
               $(BONUS_DIR)/music_bonus/music_bonus.c \
               $(BONUS_DIR)/music_bonus/fire_sounds_bonus.c \
               $(BONUS_DIR)/shooting_bonus/hitmarker_bonus.c \
               $(BONUS_DIR)/shooting_bonus/shooting_bonus.c \
               $(BONUS_DIR)/shooting_bonus/enemy_bounds_bonus.c \
               $(BONUS_DIR)/utilities_bonus/assign_bonus.c \
               $(BONUS_DIR)/utilities_bonus/ft_isspace_bonus.c \
               $(BONUS_DIR)/utilities_bonus/map_utils_bonus.c \
               $(BONUS_DIR)/utilities_bonus/time_bonus.c \
               $(BONUS_DIR)/utilities_bonus/score_bonus.c \
               $(BONUS_DIR)/utilities_bonus/null_or_space_bonus.c \
               $(BONUS_DIR)/weapon_bonus/weapon_bonus.c \
               $(BONUS_DIR)/weapon_bonus/weapon_txt_bonus.c \
               $(BONUS_DIR)/weapon_bonus/draw_utils_bonus.c \
               $(BONUS_DIR)/weapon_bonus/draw_weapons_bonus.c \
               $(BONUS_DIR)/window_bonus/display_fps_bonus.c \
               $(BONUS_DIR)/window_bonus/draw_crosshair_bonus.c \
               $(BONUS_DIR)/window_bonus/rc_bonus.c \
               $(BONUS_DIR)/window_bonus/render_bonus.c \
               $(BONUS_DIR)/window_bonus/wall_bonus.c


# ===================== Objects =====================
OBJS        := $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRCS:.c=.o))
OBJS        := $(patsubst $(LIBFT_DIR)/%, $(OBJ_DIR)/libft_%, $(OBJS))
OBJS_BONUS  := $(patsubst $(BONUS_DIR)/%, $(OBJ_BONUS)/%, $(SRCS_BONUS:.c=.o))
MAKEFLAGS   += --no-print-directory

# ===================== Progress Bar ================
TOTAL_SRCS  := $(words $(SRCS))
TOTAL_BONUS := $(words $(SRCS_BONUS))
COMPILED    := 0
PERCENT     := 0

define progress_bar
    $(eval COMPILED=$(shell echo $$(($(COMPILED)+1))))
    $(eval PERCENT=$(shell echo $$(($(COMPILED)*100/$(TOTAL_SRCS)))))
    $(eval BARS=$(shell echo $$(($(PERCENT)/2))))
    @printf "\r\033[K[🔨 \033[32m"
    @printf "%0.s█" $$(seq 1 $(BARS))
    @printf "%0.s " $$(seq 1 $$((50-$(BARS))))
    @printf "\033[0m] $(PERCENT)%% ($(COMPILED)/$(TOTAL_SRCS))"
endef

define progress_bar_bonus
    $(eval COMPILED=$(shell echo $$(($(COMPILED)+1))))
    $(eval PERCENT=$(shell echo $$(($(COMPILED)*100/$(TOTAL_BONUS)))))
    $(eval BARS=$(shell echo $$(($(PERCENT)/2))))
	@printf "\r\033[K[👮 \033[32m"
    @printf "%0.s💵" $$(seq 1 $(BARS))
    @printf "%0.s " $$(seq 1 $$((50-$(BARS))))
    @printf "\033[0m] $(PERCENT)%% ($(COMPILED)/$(TOTAL_BONUS))"
endef

# ===================== Rules =======================
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@printf "\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) -o $@
	@echo "✅ $(NAME) compiled successfully!"

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(MLX_LIB)
	@printf "\n"
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LDLIBS) -o $@
	@echo "✅ $(NAME_BONUS) compiled successfully!"

# Objects for mandatory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(call progress_bar)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Objects for libft sources
$(OBJ_DIR)/libft_%.o: $(LIBFT_DIR)/%.c
	@mkdir -p $(dir $@)
	$(call progress_bar)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Objects for bonus
$(OBJ_BONUS)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(call progress_bar_bonus)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Catch-all pattern for any bonus file in any subdirectory
$(OBJ_BONUS)/%.o: $(BONUS_DIR)/**/%.c
	@mkdir -p $(dir $@)
	$(call progress_bar_bonus)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Libs
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1 || true

# Cleaning
clean:
	@rm -rf $(OBJ_DIR) $(OBJ_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory > /dev/null 2>&1 || true
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null 2>&1 || true

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory > /dev/null 2>&1 || true

re: fclean all

.PHONY: all bonus clean fclean re
